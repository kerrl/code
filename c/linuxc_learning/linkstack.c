# include <stdio.h>
# include <stdlib.h>

# define STACKSIZE 10
# define INCREASEMENT 2
# define OK 1
# define ERROR 0

typedef int selemType ;

/*-------------------------------------------

      用两个结构体来使用链栈

	   1、用linkStack结构体后，操作链表的元素被限制只能通过pTop去指向；
	    2、p管理*pTop，而*pTop管理Node中的data，*next；



--------------------------------------------*/


typedef struct stackNode {
	selemType data ;
	struct stackNode *next;
			    
			    
} stackNode ;


typedef struct linkStack {
	stackNode *pTop ;     // 指向栈顶的指针（必须有)
	stackNode *pBottom ;        //  指向栈底的指针（二选一）
//	int count;               // 栈内节点数量（二选一）
    int stacksize;        // 记录栈的总容量
				    
} linkStack ;             

/*------------- 初始化链栈 -------------------------------*/
int initStack(linkStack *p)
{
	if (p != NULL){
		printf("初始化链栈目标有数据存在，初始化自动终止。\n");
		return ERROR;
	}
		    
	p->pTop = (stackNode *)malloc( sizeof(stackNode ) * STACKSIZE);
	if (p->pTop == NULL) {
		printf("Out of memory. \n") ;
		return ERROR ;
	}
				    
	p->pTop->next = NULL ; 
	p->pBottom = p->pTop ;  
	p->stacksize = STACKSIZE ;
	    
	return OK;
								    
								    
}



/*------------- push 链式栈 -------------------------------*/

int push_linkStack(linkStack *p, selemType e)
{
	    
	if ((p->pTop - p->pBottom) >= p->stacksize) {
	     
		p->pTop = (stackNode *)realloc( p->pTop,sizeof(stackNode ) * (p->stacksize+INCREASEMENT) );
		if (p->pTop == NULL) {
		    printf("链栈扩充内存失败 \n");
		    return ERROR;
		}
		p->stacksize += INCREASEMENT ;
	}
	p->pTop->data = e ;
	p->pTop->next = p->pTop ;  //新数据的next指向原先的top
	++(p->pTop)  ;       //栈的top指针指向新数据的地址
					    
	return OK;
}





/*------------ pop 链式栈 ---------------------------------*/

int pop_linkStack(linkStack *p, selemType *e)
{
	if (p->pTop == p->pBottom ) {
		printf("链栈已空，没有数据可以弹出。\n") ;
		return ERROR ;
	}
	stackNode *n_tmp = NULL ;
	n_tmp = p->pTop ;
	*e = (--p->pTop)->data ;
	if (p->pTop - p->pBottom > STACKSIZE) {
	    free(n_tmp);           
		 n_tmp = NULL ; 
	    p->stacksize -= 1;      // 栈容量记录-1
	}
					    
	return OK;
}

void print_linkStack(linkStack *p)
{
	    
	    
}

int main(void)
{
	return 0 ;
}
