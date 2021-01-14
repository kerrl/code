/**********************
 *   my_more01.c
 *
 * *********************/
# include <stdio.h>
# include <stdlib.h>  //exit(1)

# define PAGEROWS 24
# define LINELEN 512

void do_more(FILE *) ;

int see_more(void) ;

int main(int argc,char *argv[])			//char *argv[] argv为指针的指针
{
	FILE *fp ;
	if (argc == 1) {
		do_more(stdin);

	}
	else
		while (--argc) {
			if ( (fp = fopen(*(++argv),"r"))   ) {
				do_more(fp) ;
				fclose(fp) ;
			}
			else
				exit(1);
		}

	return 0 ;
}

void do_more(FILE *fp)
{
	char line[LINELEN] ;
	int line_nums = 0 ;
	int reply ;

	while ( fgets(line, LINELEN,fp) ) { // 每次读取一行
		if (line_nums == PAGEROWS) {
			reply = see_more();
			if (reply == 0 ) {
				break;
			}
			line_nums -= reply ;
		}
//		if (fputs(line, stdout) == EOF) { // 在屏幕上输出一行，fputs()原函数可以看出，不会输出数组最后的'\0'
//			exit(1);
//		}
		printf("%s",line);
		line_nums++ ;
	}

}

int see_more(void)
{
	int c ;
	printf("\033[7m more? \033[m");
	while ((c = getchar()) != EOF ) {
		if (c =='q'  ) {
			return 0 ;
		}
		if (c == ' '  ) {
			return PAGEROWS ; 
		}
		if (c == '\n'  ) {
			return 1 ;

		}
	}
	return 0 ;

}

