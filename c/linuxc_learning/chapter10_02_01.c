# include <stdio.h>
# include <string.h>

int main(void)
{
	int i ;
	char str[6] = "hello";
	char reverse_str[6] = "" ;

	printf("str[6] = %s \n",str);
	int n = strlen(str)-1;
	
	for (i = 0;i<=n;i++  ) {
		reverse_str[n-i] = str[i] ;
	}
	printf("reverse_str    = %s\n",reverse_str);

	for (i = 0 ; i<6; i++){
		printf("reverse_str[%d] = %d(%c) \n",i,reverse_str[i],reverse_str[i]);

	}
	putchar('\n');
	return 0 ;

}
