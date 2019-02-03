#include "func.h"

int main(int argc,char **argv)
{
    args_check(4);
    proData *proManage;//管理子进程管道的对端
    int socketfd;//服务器描述符
    char *ip,*port;//接收传进来的IP地址和端口号
    ip=(char*)argv[1];
    port=(char*)argv[2];
    tcp_init(&socketfd,ip,port);//服务器描述符从创建到listen状态
    int createNum=atoi(argv[4]);
    proManage=(proData*)calloc(createNum,sizeof(proData)*createNum);
    createChild(proManage,createNum);//创建子进程
    int epfd;//监控可读描述符句柄
    struct epoll_event event,evs[createNum+1];
    memset(&event,0,sizeof(struct epoll_event));//将监控集合清零
    epfd=epoll_create(1);//创建句柄
    event.events=EPOLLIN;//赋值
    event.data.fd=socketfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketfd,&event);//添加监控对象
    int readyNum;//可读描述符的个数
    int i;
    int j;
    char flag;//子进程反馈闲置时,接收传进来的字符
    int new_fd;//新连接的客户端
    for(i=0;i<createNum;i++)//将所有子进程的管道对端监控起来
    {
        event.data.fd=proManage[i].fds;
        epoll_ctl(epfd,EPOLL_CTL_ADD,proManage[i].fds,&event);
    }
    while(1)
    {
        memset(evs,0,sizeof(struct epoll_event));
        readyNum=epoll_wait(epfd,evs,createNum,-1);//得到可读
        for(i=0;i<readyNum;i++)      //描述符个数,并写入集合
        {
            if(socketfd==evs[i].data.fd)//判断是否有新客户端连接
            {
                new_fd=accept(socketfd,NULL,NULL);
                for(j=0;j<createNum;j++)//查找闲置子进程
                {
                    if(0==proManage[j].busy)//将新客户端信息
                    {                    //发送给闲置子进程
                        sendfd(proManage[j].fds,new_fd);
                        printf("%d is busy\n",proManage[j].fds);
                        close(new_fd);
                        break;
                    }
                }      
            }
            for(j=0;j<createNum;j++)//判断可读描述符是否为子进程
            {
                if(proManage[j].fds==evs[i].data.fd)
                {
                    read(proManage[j].fds,&flag,1);
                    proManage[j].busy=0;//子进程可读代表任务完成
                    printf("%d is not busy\n",proManage->fds);
                    break;
                }
            }
        }
    }
    return 0;
}
