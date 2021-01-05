# include<stdio.h>

int main(void)
{
	unsigned int a,b,mask = 1U <<6 ;
	a = 0x12345678 ;
	b = a ^ mask ;

	printf("a = %b, mask = %b, a^mask = %b.\n",a,mask,b);

	return 0 ;

}
