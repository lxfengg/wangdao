#include <fun.h>
int recv_n(int,char*,int);

int main(int argc,char** argv)
{
    args_check(3);
    int socketfd;
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socketfd)
    {
        perror("socket");
        return -1;
    }
    int ret;
    struct sockaddr_in ser;//命名为ser是因为要连接的是ser
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    ret=connect(socketfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    if(-1==ret)              //一旦连接，客户端本地会自动随机开启一个端口
    {                   //一旦建立连接成功，端口在主动close后才会主动关闭
        perror("connect");
        return -1;
    }
    int datalen;
    char buf[1000]={0};
    recv_n(socketfd,(char*)&datalen,sizeof(int));
    recv_n(socketfd,buf,datalen);
    int fd;
    fd=open(buf,O_WRONLY|O_CREAT,0666);
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    while(1)
    {
        recv_n(socketfd,(char*)&datalen,sizeof(int));
        if(datalen>0)
        {
            recv_n(socketfd,buf,datalen);
            write(fd,buf,datalen);
        }else{
            close(fd);
            printf("recv success\n");
            break;
        }
    }
    close(socketfd);
}
