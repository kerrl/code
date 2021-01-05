# include <stdio.h>
/*
 *
 *计算斐波那契数列计算
 * f(0) =1, f(1)=1 ,f(n) = f(n-1) +f(n-2)
 * f(46)已经接近int类型的极限了
 *- 且递归的速度在f(30)后越来越慢，应该运算的复杂度为指数级上升
 *- 递归不合适用来进行计算密集型的运算
 */
int get_fibonacci(int n)
{
	if (n==0||n==1) {
		return 1 ;
	}
	else {
		return get_fibonacci(n-1) + get_fibonacci(n-2) ;

	}

}
/*
 * 这个函数的速度要快很多，
 *
 */

int get_fibonacci2(int n)
{
 	int tmp1 = 1;
	int tmp2 = 1;

	for  (int i =0 ; i< n-2;i++ ) {
		tmp1 = tmp1 + tmp2 ;
		tmp2 = tmp1 - tmp2 ;


	}

	return tmp1;
		

}

int main(void)
{
	int i = 0 ;
	int max = 50 ;

	printf("Print Fibonacci :\n") ;
	
	for (i ; i<max;i++) {


		printf("%d  ",get_fibonacci2(i));

	}

	printf("\n End...\n") ;

//	printf("The %d fibonacci is %d. \n",max,get_fibonacci(max));

}
