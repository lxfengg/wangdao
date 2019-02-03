#include <fun.h>

int tcp_init(int *sfd,char *ip,char *port)
{
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socketfd)
    {
        perror("socketfd");
        return -1;
    }
    printf("socketfd=%d\n",socketfd);
    struct sockaddr_in ser;
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(port));//端口号
    ser.sin_addr.s_addr=inet_addr(ip);//点分制转化为二进制
    int ret;
    ret=bind(socketfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    if(-1==ret)     
    {                               
        perror("bind");
        return -1;
    }
    listen(socketfd,10);
    *sfd=socketfd;//外面要接收socketfd
    return 0;
}

