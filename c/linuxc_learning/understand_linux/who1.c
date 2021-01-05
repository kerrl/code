# include <stdio.h>
# include <stdlib.h>
# include <utmp.h>
# include <fcntl.h> //int fd =open(char *name, int how) how = O_RDONLY,O_WRONLY ,O_RDWR ERROR?-1:int
# include <unistd.h> // ssize_t read(int fd, void * buf, size_t qty)  ERROR?= -1:ssize_t
					 // int close(int fd);  ERROR?-1:0
# include <time.h>
# define SHOWHOST

void show_info(struct utmp *p_utbuf) ;

int main(void)
{
	struct utmp current_record ;
	int         utmp_fd ;
	int         record_len = sizeof(current_record) ;

	if ( (utmp_fd = open(UTMP_FILE, O_RDONLY)) == -1 ) { // UTMP_FILE define in <utmp.h>
		perror(UTMP_FILE) ;
		exit(1);
	}
	
	while ( read(utmp_fd,&current_record,record_len)== record_len  )  {
		show_info(&current_record) ;

	}

	close(utmp_fd) ;
	return 0 ;
}

void show_info(struct utmp *p_utbuf)
{
	char time[24];
	printf("% -8.8s", p_utbuf->ut_name) ;
	printf(" ");
	
	printf("% -8.8s", p_utbuf->ut_line) ;
	printf(" ");
	time_t tmp_time;
	tmp_time = p_utbuf->ut_time ;
    strftime(time,24,"%Y-%m-%d %H:%M:%S",localtime(&tmp_time));
	printf("%-20.20s", time) ; //+4是忽略前面表示星期几的四个字符
	printf(" ");
# ifdef SHOWHOST
	if (p_utbuf->ut_host[0] !='\0')	
		printf(" (%s)", p_utbuf->ut_host) ;
#endif
	printf("\n") ;
}
