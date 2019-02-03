#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h> 
#include <pwd.h>
#include <grp.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/msg.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/uio.h>
#define args_check(num) {if(argc!=num) {printf("error args\n");return -1;}}
#define DOWNFILE "file"
typedef struct{
    pid_t pid;//子进程ID
    int fds;//子进程的管道对端
    short busy;//0代表子进程不忙碌，1代表忙碌
}proData;

//应用层协议设计
typedef struct{
    int Datalen;//发送数据的长度
    char buf[1000];//保存发送的信息
}train;
int transFile(int);
void createChild(proData*,int);
void childHandle(int);
int tcp_init(int*,char*,char*);
void sendfd(int , int);
void recvfd(int,int*);
