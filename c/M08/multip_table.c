# include <stdio.h>
# define START 1
# define END 9

void print_multip_table(int start ,int end)
{
	for ( int i = start ; i<= end ; i++  ){
		for ( int j = start ; j<=i ; j++ ) {
			printf("%d*%d = %2d  ",j,i,j*i) ;
			if (j == i)
				printf("\n") ;
		}



	}

}

int main(void)
{
   print_multip_table(START ,END ) ;

   return 0 ;
}
