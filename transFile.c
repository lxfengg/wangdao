#include "func.h"

int transFile(int new_fd)
{
    train t;
    t.Datalen=strlen(DOWNFILE);
    strcpy(t.buf,"DOWNFILE");
    send(new_fd,&t,4+t.Datalen,0);
    int fd=open(DOWNFILE,O_RDONLY);
    while(t.Datalen=read(fd,t.buf,sizeof(t.buf)))
    {
        send(new_fd,&t,4+t.Datalen,0);
    }
    send(new_fd,&t,4+t.Datalen,0);
    close(new_fd);
    return 0;
}
