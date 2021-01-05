# include <stdio.h>
# include <stdlib.h>

# define LIST_COUNTER  20 //定义生成的随机数数量
# define UPPER_NUM  10    //定义模为10，生成0-9数字
/*
 *0-9的数字统计，并根据数量绘出柱状图
 *
 */
int number[LIST_COUNTER] ;//生成0-9随机数的数组
int count[UPPER_NUM] ;//放置0-9，用于统计数量

// 生成随机数数组
void get_rand_number( int n  )
{
	for (int i = 0 ; i <= LIST_COUNTER ; i++ ){
		number[i] = rand() % n ;// rand()每次生成的是相同的伪随机数，srand(time())

	}
	
}

// 生成随机数的统计数
void get_number_count(void)
{
	for ( int i = 0 ; i<=LIST_COUNTER ; i++ )
		count[number[i]]++ ;

}

// 得到随机数统计数的最大值
int get_count_max(void)
{
	int count_max = 0 ;
	for (int i = 0 ; i < UPPER_NUM ; i++){
		if  ( count_max <count[i])
			count_max = count[i] ;
		

	}
	return count_max ;
}

void print_top(void)
{
	for (int i = 0 ; i<UPPER_NUM;i++){
		printf("%d\t", i) ;
		if ( i == 9)
			printf("\n") ;
	}
}

void print_count_bar(int row,int *p)
{
	for (int i = 1 ; i<= row ; i++) {
		for (int j = 0 ;j < UPPER_NUM ; j++ ) {
			if (*(p+j) >= i )
				printf("*\t") ;
			else
				printf(" \t") ;
			if (j == 9)
				printf("\n") ;
		}	

	}

}

void print_count(int *p)
{
	for (int i = 0 ; i<UPPER_NUM ;i++) {
		printf("%d\t",*(p +i));
		if (i == 9)
			printf("\n") ;

	}
}

int main(void)
{
	int count_max = 0 ;
	get_rand_number(UPPER_NUM) ;
	get_number_count();
 	count_max = get_count_max() ;
	print_top();
	print_count_bar(count_max,count);
	print_count(count);

	return 0 ;
}


