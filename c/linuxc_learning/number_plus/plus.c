 # include <stdio.h>
 # include "linklist.h"
 
int init_element(sqList **p)
	{
		sqList *q = NULL;
		if (*p != NULL) {
		
			printf("The stack you want initial have data,fault ...\n");
			exit(1);
		}
		q = (sqList *)malloc( sizeof(sqList));           
		assert( q != NULL && "Out of memory. ");
		 
		
		q->data[0] = 0 ;
		q->top = 0 ;
		*p = q ;
		
		return OK;
		
	}
	
	int empty_element(sqList *p)
	{
		p->top = 0 ;
		return OK;
	}
	
	
	int pop_element(sqList *p,elemType *e)
	{
		if (p->top == 0) 
			return ERROR ;
		
		*e = p->data[--(p->top)] ;
		
		return OK;
	}
	
	int push_element(sqList *p,elemType e)
	{
		if (p->top == MAXNUM)
			return ERROR;
		
		p->data[p->top++] = e ;
		//++p->top;
		
		return OK;
	}
	
	elemType querytop_element(sqList *p)
	{
		
		elemType tmp;
		tmp = p->data[p->top-1];    // 注意： 一开始错误的设置 p->data[--p->top],导致运行时将top指针下移一位 top=top-1 
		return tmp ;
	}

	int isEmply_element(sqList *p)
		{
			if (p->top == 0)
				return TRUE;
			else
				return FALSE ;
		}	
	
	void display_element(sqList *p) 
	{
		int i = p->top -1 ;
		printf("linkList ={ ");
		for (i ; i>=0; i--)
			printf("%d ", p->data[i]);
		printf(" }\n");
		
		
	}

/*

>     输入逆波兰表达式 
>
>	  返回结果 
>
>

*/	

	char* suffix_expression(char *pstr)    //将中缀表达式转换为后缀表达式（逆波兰表达式） 
	{
		char  e;
		double d1;
		static char temp_str[LENGTHSIZE] ={0};   //  为了返回字符串，申请静态局部变量 static
		int i=0,j = 0 ;
		
		sqList *p = NULL;
		init_element(&p);
		if( p == NULL ) {
			printf("Out of memeory in suffix_expression() function...\n");
			exit(1);
		}
				
		e = pstr[i];
		
		while (e != '\0') {
			while ( isdigit(e) || e =='.' ) { 
			/*
			 *
			 *    每个数字和操作符均有空格间隔，方便后续计算
			 *    1、每当数字后面遇到空格和操作符时，就在数字后面添加空格 
			 *	  2、在添加空格前面做个判断，如果前面已经有空格，就不再添加 
			 */
				
				temp_str[j] = e ;
				++j;
				e = pstr[++i];
			}
			if (e ==' '){
				if (temp_str[j-1] != ' '){
					temp_str[j] = ' ';
				j++;
				}
				e = pstr[++i];
				continue;
			}
			if (e == '('){
				push_element(p,(double)e) ;  // char 转double 
				e = pstr[++i];
				if (temp_str[j-1] != ' ')
					temp_str[j++] = ' ';

				continue; 
			}
			if (e == ')'){
				
				pop_element(p,&d1);
				while ( d1 != '(') { 
					if (temp_str[j-1] !=' ')
						temp_str[j++] = ' ';
					temp_str[j++] = (char)d1;
					temp_str[j++] = ' ';
					pop_element(p,&d1);
				}
				
				
				e = pstr[++i];
				continue;
				
			}
			if (e =='+'||e=='-'||e=='*'||e=='/') {
				if (isEmply_element(p) || get_priority(querytop_element(p))<get_priority(e)) {   //当前栈顶的操作符优先级别 <  当前的操作符优先级：  压入操作符 
					push_element(p,(double)e);
									
				}
				else {
					while (!isEmply_element(p) && get_priority(querytop_element(p))>=get_priority(e)) { // 当前栈顶的操作符优先级 >= 当前的操作符 ： 弹出栈顶操作符，再比较 
						pop_element(p,&d1);
						if (temp_str[j-1] !=' ')
							temp_str[j++] = ' ';
						temp_str[j++] = (char)d1; // double转char 
						temp_str[j++] = ' ';
					} 
					push_element(p,e);    // 栈里优先级别高的出栈后，将当前操作符入栈 
				}
				e = pstr[++i];
				if (temp_str[j-1] != ' ')
					temp_str[j++] = ' ';
			}
			
		}		
		while (! isEmply_element(p) ) {
			pop_element(p,&d1);
			if (temp_str[j-1] != ' ')
				temp_str[j++] = ' ';
			temp_str[j++] = (char)d1;
			temp_str[j++] = ' ';
		}
		temp_str[j] = '\0' ;  //  最后，对字符数组最后有效位后添加结尾标记'\0' 
		
		free(p) ;  // 释放堆栈内存 
		
		return temp_str;
	}
	
	int  get_priority(char op1)
	{
		switch (op1) {
			case '(':    
			case ')': 	return 1 ;
			
			case '-':
			case '+':	return 2 ;
			
			case '*':
			case '/':	return 3 ;
			
			default :   return 0 ;
		}
		
	}
	
	

	
	double reverse_Polish(char *a)             // 逆波兰表达式算式计算，输入逆波兰表达式，输出计算double结果   
	{
		int i = 0,j=0;
		char c,number[LENGTHSIZE] ;
		double d1= 0 ,d2 = 0 ,vaule = 0, result = 0;
		
		sqList *compex = NULL ;
		init_element(&compex);
		if (compex == NULL) {
		
			printf("init stack falut in reverse_polish() function...\n");
			exit(1);
		}	
		
		//while ( (a[i] >='0' &&  a[i]<='9') || (a[i] =='.' ) )  {		// 如果是数值 
		c = a[i++] ;
		while (c != '\0') {
			while (isdigit(c) || c == '.') {
			
				number[j++] = c ;
				c = a[i++] ;
				
				if (c == ' ') {
					number[j] = '\0' ;			//一开始用number[++j] = '\0'，导致错误 ;
					d1 = atof(number) ;          // 转化为浮点数
					push_element(compex,d1) ;
					j = 0;
					break ;
				
				} 
		
			}
			switch (c) {
				case '+' :
					pop_element(compex,&d1);
					pop_element(compex,&d2);
					push_element(compex,d2+d1);
					break;
				case '-' :
					pop_element(compex,&d1);
					pop_element(compex,&d2);
					push_element(compex,d2-d1);
					break;
				case '*' :
					pop_element(compex,&d1);
					pop_element(compex,&d2);
					push_element(compex,d2*d1);
					break;	
				case '/' :
					pop_element(compex,&d1);
					pop_element(compex,&d2);
					if (d2 == 0) {
					
						printf("Couldn't divide zero...\n");
						return -1;
					}
					else {
						push_element(compex,d2/d1);
						break;
					}
				default:
					break;
				
			}
			c = a[i++];
		}
		
		pop_element(compex,&result);
		free(compex) ;
		return result ; 
	}
 
	


int main(void)
{
	
	double result = 0.0 ;
	char *str = "9 + (13-11)*3+10/3" ;
	char *str1 = NULL ;
	
	
//	char *str = "9 3 1 - 3 * + 10 2 / +";
	
	str1 = suffix_expression(str);
	result = reverse_Polish(str1);
	
	printf("str = %s\n",str);
	printf("reverse_Polish = %s\n",str1);
	printf("%s = %.2f \n",str,result);
	
	return 0 ;
}

