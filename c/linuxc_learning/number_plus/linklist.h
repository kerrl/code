# include <stdio.h>
# include <stdlib.h> 
# include <assert.h>
# include <ctype.h>     // isdigit() 


/*
	���Ա� - ˳��������ʾ 

*/

	# define LENGTHSIZE 100    //���ʽ���鳤�� 
	# define MAXNUM 10         // ��ջ���� 
	# define ERROR  0
	# define FALSE  0 
	# define TRUE   1
	# define OK     1
	
	

	typedef double elemType ;

	typedef struct {
		
		elemType data[MAXNUM] ;  // ��̬���Ա� 
		int      top ; 
		
	} sqList;
	
	
	
	int init_element(sqList **) ;   			// ��ʼ��ջ 
	int empty_element(sqList *) ;				// ���ջ 
	int pop_element(sqList *,elemType *); 	// pop ��ջ 
	int push_element(sqList *,elemType ) ;	// push ѹջ 
	int isEmply_element(sqList *) ;			// ջ�Ƿ�Ϊ��? 
	elemType querytop_element(sqList *); // ��ѯջ����ֵ 
	void display_element(sqList *) ;            // ��ӡջֵ�������ã� 
	int  get_priority(char );
	
	
	
	/*
	


	int get_element(SqList L , int n , elemType* e) 		 // �����Ա��ָ��nλ��ȡһ��dataԪ�� 
	{
		
		if (L.top == 0 || n <1 || n > L.top) {        // �����жϣ����Ա�Ϊ�� ��  nΪԽ�� �������� 0 
			return ERROR ;
		} 
		*e = L.data[n -1] ;                                // ����ָ�뷵��ֵ���������0��1 
		
		return OK ; 
	}


	int insert_element(SqList* p, int n , elemType e)		 // �����Ա��ָ��nλ��ǰ������һ��dataԪ��
	{
		if ( p->top == MAXNUM || n < 1 || n > L.top )  {  // �����жϣ����Ա����� ��  nΪԽ�� �������� 0 
			return ERROR ;
		}
		if ( n < p->top ) {
			for (int j = p->top -1; j>= n -1 ; j-- ) {
				p->data[ j+1 ]  = p ->data[ j ]  ;
			}
			 
		}
		p->data[ n-1 ] = e ;
		p->top++ ��
		
		return OK ; 
		
	}
	
	

	int delete_element( SqList* p, int n , elemType* e)       // �����Ա��ָ��nλ�ã�ɾ��һ��dataԪ��
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
	 >        �����ª��ջ����������20λ���ڶ���ʽ���� 
	 >        2
	 >
	
	
	*/
	
	







