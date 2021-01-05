# include <stdio.h>
/*
 *
 * 用递归来求一个数组的全排列
 *  n个数字全排列的组数 = n！ 
 *
 */
void swap(int arr[] ,int e_0, int e_n)

{
	int tmp   = arr[e_0] ;
	arr[e_0] = arr[e_n] ;
	arr[e_n] = tmp ;

}

void print_arr(int arr[], int length) 
{
	for ( int j = 0 ; j<=length ; j++  )
		printf("%d ", arr[j]) ;
	printf("\n") ;

}

void perm(int arr1[] ,int p, int q) 
{
	if (p == q)  {
		print_arr(arr1, q) ;
	

	}
	else {
		for ( int i = p ; i <= q ; i ++ )  {
			swap(arr1, p , i);
			
			perm(arr1,p+1 ,q ) ;
			
			swap(arr1,p , i ) ;

		}

	}

} 

int main(void) 
{

    int array[] = {1,2,3};
	perm(array ,0 , 2 ) ;

	return 0 ;

}
