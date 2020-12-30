# include <stdio.h>
# include <stdlib.h> 
# include <assert.h>
# include <ctype.h>     // isdigit() 


/*
	线性表 - 顺序表程序演示 

*/

	# define LENGTHSIZE 100    //表达式数组长度 
	# define MAXNUM 10         // 堆栈容量 
	# define ERROR  0
	# define FALSE  0 
	# define TRUE   1
	# define OK     1
	
	

	typedef double elemType ;

	typedef struct {
		
		elemType data[MAXNUM] ;  // 静态线性表 
		int      top ; 
		
	} sqList;
	
	
	
	int init_element(sqList **) ;   			// 初始化栈 
	int empty_element(sqList *) ;				// 清空栈 
	int pop_element(sqList *,elemType *); 	// pop 出栈 
	int push_element(sqList *,elemType ) ;	// push 压栈 
	int isEmply_element(sqList *) ;			// 栈是否为空? 
	elemType querytop_element(sqList *); // 查询栈顶的值 
	void display_element(sqList *) ;            // 打印栈值（调试用） 
	int  get_priority(char );
	
	
	
	/*
	


	int get_element(SqList L , int n , elemType* e) 		 // 从线性表的指定n位置取一个data元素 
	{
		
		if (L.top == 0 || n <1 || n > L.top) {        // 条件判断，线性表为空 或  n为越界 ，报错返回 0 
			return ERROR ;
		} 
		*e = L.data[n -1] ;                                // 利用指针返回值，结果返回0或1 
		
		return OK ; 
	}


	int insert_element(SqList* p, int n , elemType e)		 // 从线性表的指定n位置前，插入一个data元素
	{
		if ( p->top == MAXNUM || n < 1 || n > L.top )  {  // 条件判断，线性表已满 或  n为越界 ，报错返回 0 
			return ERROR ;
		}
		if ( n < p->top ) {
			for (int j = p->top -1; j>= n -1 ; j-- ) {
				p->data[ j+1 ]  = p ->data[ j ]  ;
			}
			 
		}
		p->data[ n-1 ] = e ;
		p->top++ ；
		
		return OK ; 
		
	}
	
	

	int delete_element( SqList* p, int n , elemType* e)       // 从线性表的指定n位置，删除一个data元素
	{
		if (p->top == 0 ||  n < 1 || n > L.top )  {
			return ERROR ;
		}
		*e = p->data[ n -1 ] ;
		if ( n <= p->top ) {
			
			for (int j = n-1; j < p->top  ; j++ ) {
				p->data[ j ]  = p ->data[ j +1]  ;
			}
		}
		p->top-- ;
		
		return OK ;
		 
	} 
	*/
	
	/*
	 >
	 >        数组简陋堆栈，用来测试20位以内多项式运算 
	 >        2
	 >
	
	
	*/
	
	







