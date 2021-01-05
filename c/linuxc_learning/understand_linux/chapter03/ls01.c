# include <stdio.h>

# include <dirent.h> 
/*     DIR *opendir(char *a) ;
 *     struct dirent *readdir(DIR *);
 *     int closedir(DIR * )

  
*/  
void do_ls(char []);

int main(int argc,char *argv[])
{
	if (argc == 1)
		do_ls(".");
	else
		while (--argc){
			printf("%s:\n", *(++argv));
			do_ls(*argv);

		}

}

void do_ls(char dirname[])
{
	DIR *dir_ptr;
	struct dirent *direntp;

	if ( (dir_ptr = opendir(dirname)) == NULL )  // 应该增加判断是否目录，再决定是否用opendir()
		printf("ls01: cannot open %s\n",dirname);
	else {
		while ((direntp = readdir(dir_ptr)) != NULL ) {
			printf("%s\n",direntp->d_name);
		}
		closedir(dir_ptr);

	}


}
