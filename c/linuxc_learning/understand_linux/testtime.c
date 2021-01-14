# include <stdio.h>
# include <time.h>

int main(void)
{
	time_t rawtime;
	struct tm *tinfo;
	char strtime[20];

	time(&rawtime);    // 得到time_t 累计秒数
	tinfo = localtime(&rawtime); // 转换成struct tm结构体
	strftime(strtime,20,"%Y-%m-%d %H:%M:%S",tinfo); //格式化输出，并存入数组
	printf("This time is %20.20s \n", strtime);

	return 0;
}
