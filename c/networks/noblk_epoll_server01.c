# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h> 
# include <strings.h> 
# include <stdlib.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/epoll.h> //增加对应的头文件
# include <unistd.h>
# include <fcntl.h>  //增加对套接字设置非阻塞方式
# include <errno.h>

# define PORT 7777
# define SERV_ADDRESS "192.168.1.88"
/*
 *   用epoll的非阻塞来实现服务器多路复用高效率监听V2
 *
 *   read(无阻塞sock)没有返回值错误判断，可以屏蔽掉返回-1的处理，但程序不够强壮
 *
 *     --  Edit by  Qu         2020/11/01
 *
 */

int main(void) 
{
		int listen_FD,conn_FD;//监听套接字
		int ret;
		struct sockaddr_in serv_addr, clie_addr;
		socklen_t clie_addr_len=sizeof(clie_addr) ;
		//创建套接字
		if ((listen_FD = socket(AF_INET,SOCK_STREAM,0)) <= 0 ) {
				perror("socket error:");
				exit(1);
		}
		//设置非阻塞socket
		int opt = 1;
		setsockopt(listen_FD,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

		//绑定套接字
		bzero(&serv_addr,sizeof(serv_addr));
		bzero(&clie_addr,sizeof(clie_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);
		serv_addr.sin_addr.s_addr =htonl(INADDR_ANY);

		ret = bind(	listen_FD,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
		if (ret <0 ) {
				perror("bind error.");
				exit(1);
		}

		listen(listen_FD,128 );
		printf("Start listing[%s]...\n",inet_ntoa(serv_addr.sin_addr));

		/*
		 *  epoll新增struct epoll_event { 
		 *  	uint32_t      events;
		 *  	epoll_data_t  data;
		 *  } evt,evts[1024];
		 *  联合体
		 *  union  epoll_data {
		 *  	void *ptr;
		 *  	int   fd;
		 *  	...
		 *
		 *  } epoll_data_t ;
		 *
		 *
		 *
		 *
		 */
		// epoll程序增设的变量
		struct epoll_event evt,evts[1024];
		int epfd ;
		int ret_count;//epoll_wait返回活跃fd数
		int recv_count;// socket的read到的文本长度
		int flag;  //conn_FD设置非阻塞时调用的标记位
		//创建epoll监听红黑树根
		epfd = epoll_create(1024);
		if (epfd <0)
				perror("epoll create error: ");


		//将listen_FD作为第一个监听红黑树的节点

		evt.events = EPOLLIN ;
		evt.data.fd = listen_FD ;
		ret = epoll_ctl(epfd,EPOLL_CTL_ADD,listen_FD,&evt);
		if (ret <0)
				perror("epoll create error: ");

		// 用while循环来实现轮询
		while (1) {
				// epoll_wait()失败返回-1
				// 参数-1表示阻塞工作方式
				ret_count = epoll_wait(epfd, evts,1024,-1);
				if (ret_count <0)
						perror("epoll create error: ");

				for (int i = 0 ;i<ret_count; i++) {
						// 由于epoll只对活动的fd进行监听，所以先排除非活动fd
						// 注意： epoll的活动为EPOLLIN，误写为POLLIN
						if ( !(evts[i].events & EPOLLIN)) 
								continue;
						if ( evts[i].data.fd == listen_FD ) {

								conn_FD = accept(listen_FD,(struct sockaddr*)&clie_addr,&clie_addr_len);
								if (conn_FD <= 0) {
										perror("accept error.");
										close(conn_FD);
										continue;

								} else {
										//有链接请求，将对应的链接套接字添加到epoll监听红黑树
										printf("connect from %s...\n",inet_ntoa(clie_addr.sin_addr));

										//------->设置非阻塞方式的连接套接字conn_FD
										flag = fcntl(conn_FD,F_GETFL,0);
										flag |= O_NONBLOCK;
										fcntl(conn_FD,F_SETFL,flag);
										//------->设置epoll的ET边沿触发
										evt.events = EPOLLIN|EPOLLET;
										evt.data.fd = conn_FD;
										ret = epoll_ctl(epfd,EPOLL_CTL_ADD,conn_FD,&evt );
										if (ret <0)
												perror("epoll create error: ");
										continue;

								}


						} 	else {
								int conn_sock = evts[i].data.fd ;
								//设置较小的buff来测试非阻塞模式下的多次read()
								char buff[10] = {};
								// 当读取内容大于缓冲区时，程序依靠while循环再次读取
								// 通过设置sleep可以观察
								/*
								 *
								 * 用epollET边沿触发技术主要应用场景针对连接socket（conn_FD）,不要应用在listen_FD上，容易丢失连接需求
								 * 1、设置conn_FD为非阻塞socket：
								 *    int flag = fcntl(conn_FD,F_GETFL,0);
								 *    flag |= O_NONBLOCK;
								 *    fcntl(conn_FD,F_SETFL,flag);
								 * 2、设置事件监听方式为ET：
								 * 		struct epoll_event  evt,evts[1024];
								 * 		evt.events = EPOLLIN|EPOLLET;
								 * 		evt.data.fd = conn_FD;
								 * 3、将非阻塞conn_FD以epollET边沿触发方式监听
								 *		epoll_ctl(epfd,EPOLL_CTL_ADD,conn_FD,&evt);
								 * 4、重要，非阻塞方式IO，需要非阻塞的read（）读取，关键是之前设置非阻塞的socket套接字
								 *    非阻塞read需要放到while（1）{}循环中读取，并需对返回值进行判断
								 *   	
								 *		int ret = read(conn_FD,buff,sizeof(buff));
								 *		返回值ret：
								 *		  > 0 : 正常读取
								 *       ==0  ：客户端断开链接
								 *       <0   : 不同于阻塞式，非阻塞式还需判断errno
								 *       		errno == EAGAIN:   正常，还需再次调用read
								 *				errno == EINTR :   硬件中断，正常，还需调用read
								 *
								 *
								 */
								while ( (recv_count = read(conn_sock,buff,sizeof(buff))) >0 )  {

										printf("Input: %s",buff);

										for (int j = 0 ;j<recv_count ; j++) {
												buff[j] = toupper(buff[j]);

										}
										/*用send(,,,MSG_NOSIGNAL)可以防止客户端意外终止导致服务器
										 * 	向一个无效的conn_sock发送数据导致的服务器进程退出
										 * 	write(conn_fsd[i],buff,count);*/
										send(conn_sock,buff,recv_count,MSG_NOSIGNAL); 

										//设置sleep可以观察但读取内容大于缓冲区时，程序再次循环读取
										sleep(1);
								} /* 去掉错误判别，
								if (recv_count==0) {
										printf("Read from client is finished,disconnect...\n");
										// 先从红黑树节点中删除，再关闭连接
										ret = epoll_ctl(epfd,EPOLL_CTL_DEL,conn_sock,NULL);
										if (ret <0)
												perror("After finish read(), epoll_ctl_del  error: ");
										close(conn_sock);
										// 从epoll监听红黑树上删除对应的conn_FD节点

										continue;
								} else {
										if (errno == EAGAIN||errno == EINTR)
												continue;
										perror("read error");
										ret = epoll_ctl(epfd,EPOLL_CTL_DEL,conn_sock,NULL);
										if (ret <0)
												perror("After read error,epoll_ctl_del  error: ");
										close(conn_sock);
										// 从epoll监听红黑树上删除对应的conn_FD节点
										continue;

								}*/
						}
				}
		}


		/*
		 * for (int i = 1 ; i<=indexfd;i++)
		 if (allfds[i].fd>0)
		 close(allfds[i]);

		 close(listen_FD);
		 */
		return 0 ;
}

