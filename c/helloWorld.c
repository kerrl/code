# include <stdio.h>

/* 
 *   Learning C in  example One
 *    edit by Qu 2020.4.5
 */
void print_mod(int i)
{
	int ten_bit = i/10 ;
	int bit     = i%10 ;
	printf("input number is %d\n",i) ;
	printf("10 bit = %d, bit = %d\n",ten_bit,bit) ;

}

int main()
{
	
	int a = 12,b = 99 ;
	print_mod(a) ;
	print_mod(b) ;
		//printf("Outer i = %d, j=%d\n",i,j) ;


}
