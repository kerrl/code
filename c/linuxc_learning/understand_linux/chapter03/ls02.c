# include <stdio.h>
# include <stdlib.h>   //malloc()
# include <time.h>     //ctime()
# include <dirent.h> 
# include <string.h>   // strcpy()
# include <sys/stat.h>

# include <pwd.h> //getpwuid()
# include <grp.h> //getgrgid()

/*     DIR *opendir(char *a) ;
 *     struct dirent *readdir(DIR *);
 *     int closedir(DIR * )

  
*/  
#define MAXNAMELEN 500

void do_ls(char []);
void show_file_info(char *, struct stat *);
void show_file_mode(int, char str[]);
char * getuid_to_name(unsigned int);
char * getgid_to_name(unsigned int);

void show_file_info(char * fname, struct stat * buf)
{

	char modestr[11];                       //用于显示文件读写属性
	show_file_mode(buf->st_mode,modestr);   // 获得文件属性转换后的字符属性

	printf("%s ",modestr);   // 文件权限可以用八进制读取
	printf("%4d ",buf->st_nlink);  // 提醒：一开始全用%s，发生段错误
	printf("%-8s ",getuid_to_name(buf->st_uid));
	printf("%-8s ",getgid_to_name(buf->st_gid));
	printf("%8ld ",buf->st_size);
	printf("%.12s ",4+ctime(&buf->st_mtime));
	printf("%s\n",fname);
}

/*
 *  struct passwd {
 *  	char *pw_name ;
 *  	char *pw_passwd;
 *  	_uid_t pw_uid;
 *  	_gid_t pw_gid;
 *  	char *pw_dir;
 *  	char *pw_shell;
 *
 *
 */ 

char *getuid_to_name(unsigned int uid )
{
	struct passwd *pwd_str;
	static char tmp_uid[10];
	if ( (pwd_str = getpwuid(uid)) == NULL)   //uid有可能无法返回一个用户id（被删除）
		sprintf(tmp_uid,"%d",uid);            // 如果娶不到用户id，直接返回字符类型的编号
	else
		return pwd_str->pw_name ;
}

char *getgid_to_name(unsigned int gid)
{
	struct group *grp_str;
	static char tmp_grp[10];

	if ( (grp_str = getgrgid(gid)) == NULL)   //uid有可能无法返回一个用户groupid（被删除）
		sprintf(tmp_grp,"%d",gid);            // 如果娶不到用户groupid，直接返回字符类型的群编号
	else
		return grp_str->gr_name ;

}

void show_file_mode(int mode, char str[])
{
	strcpy(str,"----------"); //文件的10位属性
	if ( S_ISDIR(mode)) 
		str[0] = 'd';
	if (S_ISCHR(mode)) 
		str[0] = 'c';
	if (S_ISBLK(mode)) 
		str[0] = 'b';

	if (mode & S_IRUSR) 
		str[1] = 'r';
	if (mode & S_IWUSR) 
		str[2] = 'w';
	if (mode & S_IXUSR) 
		str[3] = 'x';
	
	if (mode & S_IRGRP) 
		str[4] = 'r';
	if (mode & S_IWGRP) 
		str[5] = 'w';
	if (mode & S_IXGRP) 
		str[6] = 'x';
	if (mode & S_IROTH) 
		str[7] = 'r';
	if (mode & S_IWOTH) 
		str[8] = 'w';
	if (mode & S_IXOTH) 
		str[9] = 'x';

}

int main(int argc,char *argv[])
{
	if (argc == 1)
		do_ls(".");
	else
		while (--argc){
			//printf("%s:\n", *(++argv));
			do_ls(*(++argv));

		}
	return 0;


}

void do_ls(char dirname[])
{
	DIR *dir_ptr;
	struct dirent *direntp;
	struct stat finfo ;
	static char *fullname = NULL;              //全路径
	if ( (dir_ptr = opendir(dirname)) == NULL )  // 应该增加判断是否目录，再决定是否用opendir()
		if (stat(dirname,&finfo) != -1){
					
			show_file_info(dirname,&finfo);
		}
		else 
			printf("ls01: cannot open %s\n",dirname);
	else 
		while ((direntp = readdir(dir_ptr)) != NULL ) {
			//printf("%s\n",direntp->d_name);
			fullname = (char *)malloc(strlen(dirname)+MAXNAMELEN+1);
			if (fullname ==NULL)
				perror("Out of memory.");
			sprintf(fullname,"%s/%s",dirname,direntp->d_name);
			if (stat(fullname, &finfo)== -1 )
				perror(fullname);
			else
				show_file_info(direntp->d_name,&finfo);
		}
		if (fullname != NULL)  //释放malloc分配的内存，本程序中可以不用，程序退出后自动释放
			free(fullname);
		closedir(dir_ptr);

}



