/*使用mmap对文件进行操作*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#define FILELENGTH 80
int main(void)
{
	int fd = -1;
	char buf[]="这里是要写入的字符串！";
	char *ptr = NULL;
	/*打开文件mmap.txt,并将文件长度缩小为0，
	如果文件不存在则创建它，权限为可读写执行*/
	fd = open ("mmap.txt",O_RDWR/*可读写*/|O_CREAT/*不存在，创建*/|O_TRUNC/*缩小为0*/,S_IRWXU);
	if( -1 == fd){
		return -1;}
	/*下面的代码将文件的长度扩大为80*/
	/*向后偏移文件的偏移量到79*/
	lseek(fd,FILELENGTH-1,SEEK_SET);
	write(fd,"a",1); //随意写入一个字符串，此时文件的长度为80
	/*将文件mmap.txt中的数据映射到内存，对文件的操作立刻显示在文件上，可读写*/
	ptr = (char*)mmap(NULL,FILELENGTH, PROT_READ| PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1 == ptr){
		printf("mmap failure \n");
		close(fd);
		return -1;
	}
	
	memcpy(ptr+16,buf,strlen(buf));
	/*将buf中的字符串复制到映射区域中，起始地址为ptr偏移16*/
	munmap(ptr,FILELENGTH); /*取消文件映射关系*/
	close(fd);
	return 0;
}
/*
$gcc -o mmap mmap.c
$./mmap
$ls -l mmap.txt
-rwx------ 1 miracle miracle 80 4月  24 18:38 mmap.txt
$od -c mmap.txt
0000000  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000020 350 277 231 351 207 214 346 230 257 350 246 201 345 206 231 345
0000040 205 245 347 232 204 345 255 227 347 254 246 344 270 262 357 274
0000060 201  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000100  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0   a
0000120
*/
	
	
	
	
	
	
	
			  
	