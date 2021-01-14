# include <stdio.h>
# include <math.h>
/*
 *利用递归来查找两个整数的最大公约数
 *GDC(greatest common divisor)
 *  如果a 能被b整除，b就是a的最大公约数
 *  否则，最大公约数为b和a%b的最大公约数
 *
 */

int gcd(int a, int b)
{
	int temp = 0 ;
	
		
	if (a<b){
		temp = a ;
		a    = b ;
		b    = temp ;
	}
	if (b == 1) {
		return 1 ;
	}
	else {
		
		if (a%b == 0 ) {
			return b ;
		

		}
		else {
			return gcd(b,a%b) ;

		}

	}
}


int main(void)
{
	int n1 =- 256, n2 = 3200 ;
	printf("%d and %d GDC is %d.\n",n1,n2,gcd(fabs(n1),fabs(n2))) ;
	
	return 0 ;
}
