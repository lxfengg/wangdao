#include "func.h"

void sendfd(int sockfdw,int fd)
{
    struct msghdr msg;
    struct cmsghdr *cmsg;//cmsg是变长结构体
    memset(&msg,0,sizeof(msg));//一定要清零
    char buf1[10]="xiong";
    char buf2[10]="er";
    struct iovec iov[2];
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    iov[1].iov_base=buf2;
    iov[1].iov_len=2;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    int len=CMSG_LEN(sizeof(int));//计算结构体长度
    cmsg=(struct cmsghdr *)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg)=fd;//要传递的描述符,通过该函数
    msg.msg_control=cmsg;//(接上)获得最后一个成员的起始地址
    msg.msg_controllen=len;
    int ret;
    ret=sendmsg(sockfdw,&msg,0);
    if(-1==ret)
    {
        perror("sendmsg");
        return;
    }
}
void recvfd(int sockfdr,int *fd)
{
    struct msghdr msg;
    struct cmsghdr *cmsg;//cmsg是变长结构体
    memset(&msg,0,sizeof(msg));//一定要清零
    char buf1[10]={0};
    char buf2[10]={0};
    struct iovec iov[2];
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    iov[1].iov_base=buf2;
    iov[1].iov_len=2;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    int len=CMSG_LEN(sizeof(int));//计算结构体长度
    cmsg=(struct cmsghdr *)calloc(1,len);//初始化结构体指针
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret;
    ret=recvmsg(sockfdr,&msg,0);
    if(-1==ret)
    {
        perror("sendmsg");
        return;
    }
    *fd=*(int*)CMSG_DATA(cmsg);//接收传递过来的描述符的控制信息
}
