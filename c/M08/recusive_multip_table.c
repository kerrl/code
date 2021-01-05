# include <stdio.h>
# define START 1
# define END 9
/*
 *
 *
 * 利用递归来打印9 -9乘法表
 *
 *
 */
void recusive_multip_table(int q)
{
	if (q == 1)
		printf("1*%d = %2d  \n",q,1*q) ;
	else {
		
		recusive_multip_table(q-1) ;
		
		for (int i = 1 ; i <= q ; i ++ ) {
			printf("%d*%d = %2d  ",i,q,i*q);
			if (i == q)
				printf("\n") ;
		}
		
	}
}

int main(void)
{
	recusive_multip_table(END) ;

	return 0;

}
