/*****************
 *  more02.c
 * **************/
# include <stdio.h>
# include <stdlib.h>  //包含了exit(1)

# define PAGEROWS 24
# define LINELEN 512

void do_more(FILE *) ;

int see_more(FILE *) ;

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
	FILE *fp_tty ;

	/*    增加了从文件句柄，/dev/tty键盘和屏幕设备描述文件，
	 *    写相当于屏幕显示，读相当于获取键盘输入 - Qu
	 */
	fp_tty = fopen("/dev/tty","r") ; 
	
	while ( fgets(line, LINELEN,fp) ){ // 每次读取一行
		if (line_nums == PAGEROWS) {
			reply = see_more(fp_tty); // -Qu
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

int see_more(FILE *cmd)  // 从/dev/tty读入或者输出
{
	int c ;
	printf("\033[7m more? \033[m");
	// while ((c = getchar()) != EOF ) {
	while ( (c = getc(cmd)) != EOF ) {
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

