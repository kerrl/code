# include <stdio.h>
# include <stdlib.h>

# define MAX_ROW 5
# define MAX_COL 5

typedef struct  {
    int row ;
    int col ;

} point ;

point stack[512] ;
int top = 0 ;

int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
} ;



void push(point p) 
{
    if (top==512){
		printf("stack is fulled.\n");
		exit(1);
	}
	stack[top++] = p ;
}

point pop(void)
{
    
    if (top<0){
		printf("stack is Empty.\n");
		exit(1);
	}
	return stack[--top] ;
}

int is_empty(void)
{
    return top == 0 ;
}

void print_maze(void)
{
    int i ,j ;
    for ( i=0;i<MAX_ROW;i++) {
        for (j = 0 ;j<MAX_COL;j++ ) {
            printf("%d ",maze[i][j]);
        }
        putchar('\n');
        

    }
    printf("****************\n");
}
/*
void maze_copy(void)
{
	int maze_temp[MAX_ROW][MAX_COL]  ;
	for (int i=0;i<MAX_ROW;i++) {
		for (int j=0;j<MAX_COL;j++)
			maze_temp[i][j] = maze[i][j] ;
	}
}
*/

point predecessor[MAX_ROW][MAX_COL] = {
    { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
    { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
    { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
    { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
    { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
};

void visit(int t_row, int t_col, point pre)
{
    point visit_point = { t_row,t_col } ;
    maze[t_row][t_col] = 8 ;
    predecessor[t_row][t_col] = pre ;
    push(visit_point);
}

int main(void)
{
    point p = {0,0} ;
    maze[p.row][p.col] = 8 ;
    push(p) ;

    while (!is_empty()) {
        p = pop();
        if ( (p.row ==MAX_ROW-1) && (p.col == MAX_COL-1))        // if (End) exit
            break;

        if ( (p.col+1 < MAX_COL) && (maze[p.row][p.col+1]==0))   // if[row,col+1]==0  move ->right
            visit(p.row, p.col+1, p);

        if ( (p.row+1 < MAX_ROW) && (maze[p.row+1][p.col]==0))  //  if[row+1,col]==0 move ->down
            visit(p.row+1, p.col, p);

        if ( (p.col-1 >=0) && (maze[p.row][p.col-1]==0) )       // if [row,col-1]==0 move ->left
            visit(p.row, p.col-1, p);  

        if ( (p.row-1 >=0) && (maze[p.row-1][p.col]==0) )       // if [row+1,col]==0 move->Up
            visit(p.row-1, p.col, p);   
        
        print_maze();
    }

    if (p.row == MAX_ROW-1 && p.col == MAX_COL-1) {
        printf("(%d, %d)\n", p.row, p.col);
        while (predecessor[p.row][p.col].row != -1) {
            p = predecessor[p.row][p.col] ;
            printf("(%d, %d)\n", p.row, p.col);
        }
    }
    else
        printf("No path!\n");

    return 0 ;
}
