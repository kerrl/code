# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h> 
# include <strings.h> 
# include <stdlib.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <unistd.h>

# define PORT 7777
# define SERV_ADDRESS "192.168.1.88"
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
		//设置非阻塞listen_fd
		int opt = 1;
		setsockopt(listen_FD,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

		//绑定套接字
		bzero(&serv_addr,sizeof(serv_addr));
		bzero(&clie_addr,sizeof(clie_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);
		serv_addr.sin_addr.s_addr =inet_addr(SERV_ADDRESS);

		ret = bind(	listen_FD,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
		if (ret <0 ) {
				perror("bind error.");
				exit(1);
		}

		listen(listen_FD,128 );
		printf("Start listing[%s]...\n",inet_ntoa(serv_addr.sin_addr));
		
		/*
		 *
		 *
		 * select()新增fd_set 位图，每一个监听fd对应fd_set上的一位.
		 * select(maxFD+1, &RD_SET,&WR_SET,&ERR,timeout);
		 * fd_set rfds;
		 * FD_ZERO(&rfds);
		 * FD_SET(fd,&rfds);
		 * FD_CLR(fd,&rfds);
		 * FD_ISSET(fd,&rfds);
		 *
		 *
		 */
		fd_set rfds;
		int conn_fds[1024];//设置链接套接字存储数组
		int maxfd,retfd_count,indexfd=0;
		//将链接套接字数组全部初始化为-1
		memset(conn_fds,-1,sizeof(conn_fds));

		// 用while循环来实现轮询
		while (1) {

				FD_ZERO(&rfds);//每次循环开始，清零
				FD_SET( listen_FD,&rfds);
				maxfd = listen_FD;
				for (int i = 0 ;i<=indexfd;i++) {
						if (conn_fds[i] != -1) {
								FD_SET(conn_fds[i],&rfds);
								if (maxfd < conn_fds[i])
										maxfd = conn_fds[i];
						}
				}
				if ( (retfd_count = select(maxfd+1,&rfds,NULL,NULL,NULL))<= 0 ){
						perror("select error.");
						continue;
				}
				// 轮询retfd的返回值，如果有多个连接，将对应的conn_FD加入连接数组
				//错误用法:for (int i=0 ; i<retfd_count ; i++ ) {
				// 首先判断监听的套接字是否活动（有无客户端链接请求）
				if (FD_ISSET(listen_FD,&rfds)) {
						conn_FD = accept(listen_FD,(struct sockaddr*)&clie_addr,&clie_addr_len);
						if (conn_FD <= 0) {
								perror("accept error.");
								close(conn_FD);
								continue;

						} else {
								//有链接请求，将对应的链接套接字存储起来
								printf("connect from %s...\n",inet_ntoa(clie_addr.sin_addr));
								for (int i=0 ;i<=indexfd;i++) {
										if (conn_fds[i] ==-1) {
												conn_fds[i] = conn_FD;
												indexfd++;
												break;
										}


								}
						}
						if (indexfd ==1024){
								printf("The array of conn_FD is FULL.\n");
								exit(1);

						}


				} 
				else {
						for (int i = 0 ; i <=indexfd ;i++) {
								if ( (conn_fds[i] >0)  && FD_ISSET(conn_fds[i],&rfds)) {

										char buff[1024] = {};
										// 当读取内容大于buff缓冲区时，程序依靠while循环再次读取
										// 通过设置sleep可以观察
										int count = read(conn_fds[i],buff,sizeof(buff));
										if (count >0) {
												printf("Input: %s",buff);

												for (int j = 0 ;j<count ; j++) {
														buff[j] = toupper(buff[j]);

												}
												/*用send(,,,MSG_NOSIGNAL)可以防止客户端意外终止导致服务器
												 * 	向一个无效的conn_sock发送数据导致的服务器进程退出
												 * 	write(conn_fsd[i],buff,count);*/
												send(conn_fds[i],buff,count,MSG_NOSIGNAL); 

												//设置sleep可以观察当读取内容大于缓冲区时，程序再次循环读取
												//sleep(1);
												continue;
										} else if (count==0) {
												close(conn_fds[i]);
												conn_fds[i] = -1;
												continue;

										} else {
												perror("read error");
												close(conn_fds[i]);
												continue;

										}
								}
						}
				}
				//	}


		}

		/*
		 * for (int i = 0 ; i<=indexfd;i++)
		 if (conn_fds[i]>0)
		 close(conn_fds[i]);

		 close(listen_FD);
		 */
		return 0 ;
}

