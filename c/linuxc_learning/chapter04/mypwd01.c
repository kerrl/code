# include <stdio.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>

unsigned int get_inode(char *);
char * inode_to_name(unsigned int );
void print_full_path(unsigned int) ;


int main(void)
{
	if (argc>1)
		perror("Usage: mypwd without argements.");
	else
		print_full_path( get_inode(".") );
	printf("\n");
	exit(0);
}

/*
 *     输入文件名，得到对应的inode
 *
 */
unsigned int get_inode(char *fname)
{
	struct stat finfo ;

	if ( stat(fname,&finfo) == -1 )
		perror("Cannot stat ",fname);
	else
		return finfo.st_ino ;
}

char * inode_to_name(unsigned int inode)
{
	DIR * dir_ptr ;
	static struct dirent *dirent_ptr;
	static char fname[100] ;

	if ( (dir_ptr = opendir(".")) == NULL) {
		perror(".");
		exit(1);

	}
	while (dirent_ptr = readdir(dir_ptr) != NULL ) {

		if (dirent_ptr->d_ino == inode) {
			strncpy(fname, dirent_ptr->d_name,100-1);
			fname[100-1] = '\0' ;
			closedir(dir_ptr);
			return fname ;

		}
		
		fprintf(stderr,"Error looking for inode %d\n",inode);
		exit(1);	

	}


}

