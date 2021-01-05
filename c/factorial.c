# include <stdio.h>

/*
 * 递归程序(Recursive)
 *
 * 阶乘设计
 */

int  factorial(int n)
{

 //*  算法1: 递归
		if ( n == 0) {
		return 1 ;

	}
	else {

		return n*factorial(n-1) ;

	}
}


// 算法2:循环控制
//
/*
	int result = 1 ;
	for (int i=1 ;i<=n ;i++   ) {
    	
		result = result * i ;

	}
	return result ;

}
*/

int main(void) 
{
	int a = 10 ;

	printf("Factorial %d! = %d .\n",a,factorial(a)) ;

	return 0 ;




}
