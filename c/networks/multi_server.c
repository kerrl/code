# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/wait.h>
# include <arpa/inet.h>
# include <ctype.h>
# include <string.h>

# define SERVER_PORT 7777
//轮询回收子进程，释放资源,防止僵尸子进程
/*
 *
 * 利用多进程来实现多客户端连接示例程序
 *
 *
 *      Edit by Qumin    2020/10/04
 *
 * 如果父进程早于子进程终止，子进程会被initd自动回收，
 *
 *如果子进程早于父进程终止，子进程如果不主动回收会变成僵尸进程
 *
 */
void wait_child(int signo) {
		while (waitpid(0,NULL,WNOHANG)>0)// WNOHANG: 非阻塞方式  >0没有仍有子进程未回收
				;


}

int main(void) {
		pid_t  pid;

		int listen_sock ,connect_sock;
		struct sockaddr_in  serv_addr,  clie_addr ;
		socklen_t clie_addr_len;
		char buff[BUFSIZ],clie_ip[BUFSIZ];
		int count,i ;
		//建立监听套接字
		if ( (listen_sock = socket(AF_INET,SOCK_STREAM,0) )<0 ){
				perror("socket error");
				exit(1);
		}

		bzero(&serv_addr,0);
		bzero(&clie_addr,0);
		//建立bind()
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(SERVER_PORT);
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY) ;

		if ( (bind(listen_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))<0 )  {
				perror("bind error");
				exit(1);
		}

		// 建立listen，设立最大同时握手申请链接的数量
		listen(listen_sock,128) ;
		printf("Server is listening ...\n");

		clie_addr_len = sizeof(clie_addr);	
		//轮询，服务器对每一个客户端建立链接后，生成一个新的链接套接字
		while (1) {
				if (( connect_sock = accept(listen_sock,
								(struct sockaddr*)&clie_addr,
												&clie_addr_len )  )< 0 ){
						perror("accept error");
						exit(1);
				}
				// 在服务器上显示对端链接的IP地址和端口号
				printf("Client from ip =  %s,port = %d \n",
								inet_ntop(AF_INET,&clie_addr.sin_addr,
										clie_ip,sizeof(clie_ip)),ntohs(clie_addr.sin_port));
				//生成子进程
				pid = fork();

				if (pid <0) {
						perror("fork error");
						exit(1);
				}
				//在子进程中，用break避免子进程产生子进程
				else if (pid ==0 )
						break;
				//在父进程中,只处理监听套接字，并注册子进程结束信号
				else if (pid >0) {
						close(connect_sock);
						//在父进程中，无阻塞调用waitpid(0,NULL,WNOHANG)
						signal(SIGCHLD,wait_child);
						//	while (wait(NULL) > 0 ) ; 用阻塞方式，新连接的客户端无法再次发送

				}
				//子进程的处理内容，对传递的字母，传回大写后的字母
				if (pid == 0) {
						close(listen_sock);
						while (1) {
								count = read(connect_sock,buff,sizeof(buff)) ;
								if (count <0 )
										perror("read error");
								else if (count == 0) {
										close(connect_sock);
										break;
								}
								else {

										for (i = 0 ; i<count ; i++)
												buff[i] = toupper(buff[i]);
										write(connect_sock,buff,count) ;

								}

						}


				} /*else {


					signal(SIGCHLD,wait_child);

					}*/



				return 0;
		}
