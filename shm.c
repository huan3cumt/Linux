/*
 * 定义buf出现问题，error: storage size of ‘buf’ isn’t known  struct semid_ds buf;
 * 在编译这个C时，发现g++无法编译，gcc和g++并不是通用的，gcc适用C，g++适用C++
 * /
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<string.h>
#define pid_t int

int main(void)
{
	key_t key;
	int semid,shmid;
	char i,*shms,*shmc;//信号量，共享内存
	struct semid_ds buf;
	int value = 0;
	char buffer[80];
	pid_t p;

	key = ftok("/ipc/sem",'a');//生成键值
	shmid = shmget(key,1024,IPC_CREAT | 0604);
	//获得共享内存，大小为1024个字节
	semid = CreateSem(key,0);//建立信号量

	p = fork();//分叉进程
	if(p>0) //父进程
	{
		shms = (char *)shmat(shmid,0,0);
	//挂接共享内存
		memcpy(shms,msg,strlen(msg)+1);
	//复制内容
		sleep(10);
		Sem_P(semid);
	//获得共享内存的信号量
		shmdt(shms);
	//摘除共享内存
		DestroySem(semid);
	//销毁信号量
	}
	else if(p == 0)//子进程
	{
		shmc = (char *)shmat(shmid,0,0);
	//挂接共享内存
		Sem_V(semid);
	//减小信号量
		printf("共享内存的值为：%s\n",shmc);
	//打印信息
		shmdt(shmc);
	//摘除共享内存
	}
	return 0;
	
};

