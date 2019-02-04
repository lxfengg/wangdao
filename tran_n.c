#include <fun.h>

int send_n(int sfd,char *ptran,int len)
{//循环发送
    int total=0;//总共发送了多少数据
    int ret=0;//记录一次发送多少数据
    while(total<len)
    {//当发送总量小于总长度时,继续发送
        ret=send(sfd,ptran+total,len-total,0);
        total+=ret;
    }
    return 0;
}

int recv_n(int sfd,char *ptran,int len)
{
    int total=0;//总共接收了多少数据
    int ret=0;
    while(total<len)
    {
        ret=recv(sfd,ptran+total,len-total,0);
        total+=ret;
    }
    return 0;
}
