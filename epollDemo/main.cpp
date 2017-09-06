#include <iostream>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<map>

using namespace std;

#define SRV_PORT 0xabcd

int eplid;

void epollServer()
{
    int iRet;
    int serverfd=socket(PF_INET,SOCK_STREAM,0);
    if(serverfd<0)
    {
        perror("socket failed");
        return;
    }

    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(SRV_PORT);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    socklen_t addrlen=sizeof(addr);

    iRet=bind(serverfd,(sockaddr*)&addr,addrlen);
    if(iRet)
    {
        perror("bind failed");
        return;
    }

    iRet=listen(serverfd,10);
    if(iRet)
    {
        perror("listen failed");
        return;
    }

    eplid=epoll_create(1);


}

int main()
{

    return 0;
}

