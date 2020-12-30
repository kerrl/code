# include <stdio.h>
int is_leap_year(int year);


int main(void)   
{
	int year = 400 ;
	if (is_leap_year(year))
		printf("%d  is leap year.\n",year) ;
	else
	    printf("%d  is NOT leap year.\n",year) ;
	return 0;
}

int is_leap_year(int year)
{
	if ((year % 4 == 0) && (year % 100 != 0))
		return 1;
	else if (year % 400 == 0)
	 	return 1 ;
	else
		return 0 ;



}
