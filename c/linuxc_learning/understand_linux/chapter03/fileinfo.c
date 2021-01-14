# include <stdio.h>

# include <sys/stat.h>


/*
 *   int stat(char *filename, struct stat *)
 *
 *
 */

void show_stat_info(char *filename, struct stat *buf)
{
	printf("     name: %s\n",filename);
	printf("     mode: %o\n",buf->st_mode);   // 文件权限可以用八进制读取
	printf("    links: %d\n",buf->st_nlink);  // 提醒：一开始全用%s，发生段错误
	printf("     user: %d\n",buf->st_uid);
	printf("    group: %d\n",buf->st_gid);
	printf("     size: %d\n",buf->st_size);
	printf(" moditime: %d\n",buf->st_mtime);

}

int main(int argc, char * argv[])
{
	struct stat info ;

	if ( argc >1 )
		if ( stat(*(++argv), &info) != -1 ){
			show_stat_info(*argv,&info);
			
			return 0;
		}
		else
			perror(*argv);
	return 1;
}
