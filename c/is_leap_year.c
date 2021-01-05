# include <stdio.h>
/*
 * 用来计算是否闰年
 * 能被4整除，但不能被100整除的是闰年，
 * 另外，能被400整除的是闰年
 *
 */

int is_div_four(int year)
{
	if (year % 400 == 0) {
		return 1 ;
	}
    else if ( year % 4 == 0 && year % 100 != 0 ){
		return 1 ;
	}
	else  {
		return 0 ;
	}
}

void print_leap_year(int year)
{
	if  (is_div_four(year) ) {
		printf("%d is leap year.\n",year);
	}
	else {
		
		printf("%d is NOT leap year.\n",year);
	}

}

int main(void)
{
	int a = 1600,b = 1818,c=1980 ;
	print_leap_year(a) ;
	print_leap_year(b) ;
	print_leap_year(c) ;
	
	return 0 ;
}
