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
		if (fputs(line, stdout) == EOF) {
			exit(1);
		}
		line_nums++ ;
	}

}

/*
 *
 *  see_more(FILE *fp)的缺点：
 *  从管道读入文件时，由于程序中用getchar()
 *  相当于变成从管道中读取，当碰到空格时，就会
 *  再滚动24行，这样如果从管道过来的有多个空格，
 *  文件就直接显示到结尾了，
 *  修改的程序见more02.c中的see_more(FILE *cmd)
 *
 */
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

