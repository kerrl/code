#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
# include <sys/socket.h>
 

void swap(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
 
void printArray(int arr[], int len)
{
	for (int i = 0; i <= len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
}
 
void perm(int arr[], int p, int q)
{
	if (p == q)
	{
		printArray(arr, q  );
	}
	for (int i = p; i <= q; i++)
	{
		swap(arr, p, i);
		perm(arr, p + 1, q);
		swap(arr, p, i);
 		
	}
}
 
int main(void)
{
	int arr[] = { 1,2,3,4,5};
//	perm(arr, 0,4 );
	
	return 0;
}
