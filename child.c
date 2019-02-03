#include "func.h"

void createChild(proData *pManage,int num)
{
    int fds[2];
    int i;
    pid_t pid;
    for(i=0;i<num;i++)
    {
        socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//创建管道
        pid=fork();//进程ID
        if(!pid)//子进程
        {
            close(fds[1]);//关闭子进程管道读端
            childHandle(fds[0]);//子进程所进行的操作
        }
        close(fds[0]);//关闭写端
        pManage[i].pid=pid;//子进程ID
        pManage[i].fds=fds[1];//子进程管道对端
    }
    return;
}

void childHandle(int fds)
{
    char flag=1;//为了触发父进程读取子进程内容,即得知子进程完成任务
    int new_fd;
    while(1)
    {
        recvfd(fds,&new_fd);//给客户端发文件
        printf("I am child,get task,send file start\n");
        close(new_fd);//发完文件之后关闭客户端连接
        write(fds,&flag,sizeof(char));//通知父进程完成任务
    }
}
