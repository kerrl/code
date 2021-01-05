# include <stdio.h>
# include <string.h>

int main(void)
{
	int sum = 0 ,i = 0;
	char input[5];

	while (1) {
		sum = 0 ;
		printf("Please input digits: ");
		scanf("%s", input);
//		while (strlen(input)>5){
//			printf("only input less 5 digits, please input again:");
//			scanf("%s",input);
//		}
		for ( i = 0 ; input[i] != '\0' ; i++ ) 
			sum = sum * 10 + input[i] -'0';
		
		printf("input = %d\n",sum);
	}
	return 0 ;
}
