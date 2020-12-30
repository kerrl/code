# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h> 
# include <strings.h> 
# include <stdlib.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
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
		//设置非阻塞socket
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

		//fd_set rfds;
		//int conn_fds[1024];//设置链接套接字存储数组
		//int maxfd,retfd_count,indexfd=0;
		//将链接套接字数组全部初始化为-1
		//memset(conn_fds,-1,sizeof(conn_fds));
		// poll下，初始化数组，并将数组的每个fd设置为-1
		struct pollfd allfds[1024];
		for (int i = 0 ; i<1024; i++)
				allfds[i].fd = -1 ;

		int indexfd=0;
		allfds[0].fd = listen_FD ;
		allfds[0].events = POLLIN ;


		// 用while循环来实现轮询
		while (1) {
				// poll失败返回-1
				if ( poll(allfds,indexfd +1 ,-1)<0 ) {
						perror("poll error:");
						exit(1);

				}


				// allfds[0]始终放的listen_FD
				// 注意：是对allfds.revents事件进行监听，之前误写成.events导致无法监听事件
				if (allfds[0].revents & POLLIN) {
						conn_FD = accept(listen_FD,(struct sockaddr*)&clie_addr,&clie_addr_len);
						if (conn_FD <= 0) {
								perror("accept error.");
								close(conn_FD);
								continue;

						} 
						else {
								//有链接请求，将对应的链接套接字存储起来
								printf("connect from %s...\n",inet_ntoa(clie_addr.sin_addr));
								for (int i=1 ;i<1024;i++) {
										if (allfds[i].fd ==-1) {
												allfds[i].fd = conn_FD;
												//注意一定要同时赋予.events=POLLIN事件
												allfds[i].events = POLLIN;
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
						//由于allfds[0]被listen_FD占用，conn_FD从1开始
						for (int i = 1 ; i <=indexfd ;i++) {
								if (allfds[i].fd <0 )
										continue;
								if ( allfds[i].revents & POLLIN ) {

										char buff[1024] = {};
										// 当读取内容大于缓冲区时，程序依靠while循环再次读取
										// 通过设置sleep可以观察
										int count = read(allfds[i].fd,buff,sizeof(buff));
										if (count >0) {
												printf("Input: %s",buff);

												for (int j = 0 ;j<count ; j++) {
														buff[j] = toupper(buff[j]);

												}
												/*用send(,,,MSG_NOSIGNAL)可以防止客户端意外终止导致服务器
												 * 	向一个无效的conn_sock发送数据导致的服务器进程退出
												 * 	write(conn_fsd[i],buff,count);*/
												send(allfds[i].fd,buff,count,MSG_NOSIGNAL); 

												//设置sleep可以观察但读取内容大于缓冲区时，程序再次循环读取
												//sleep(1);
												continue;
										} else if (count==0) {
												close(allfds[i].fd);
												allfds[i].fd = -1;
												continue;

										} else {
												perror("read error");
												close(allfds[i].fd);
												continue;

										}
								}
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

