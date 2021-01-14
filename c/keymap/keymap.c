# include <bios.h>
# include <stdlib.h>
# include <stdio.h>
# define Esc 0x11b
int  main(void)
{
	int key;
    while(!kbhit())/*kbhit()表示有键盘按下*/
	{
		key=bioskey(0);/*接收键盘*/
		printf("0x%x\n",key);/*输出扫描码的十六进制形式*/
		if(key==Esc)
			break;
	}
	getch();
	return 0;
}
