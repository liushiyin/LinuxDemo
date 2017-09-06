#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<poll.h>
#include<signal.h>

using namespace std;

#define SRV_PORT 0xabcd
#define MAX_CONN 10000

typedef struct pollfd pollfd_s;

pollfd_s *npfds=new pollfd_s[MAX_CONN];
int curPfdNums=0;

void closeFd()
{
    for(int i=1;i<curPfdNums;++i)
    {
        close(npfds[i].fd);
    }
}

void pollProcess()
{
    char szBuf[1024]={0};
    sockaddr_in addr;
    socklen_t addrlen=sizeof(addr);
    write(STDERR_FILENO,"Send:",5);
    while(true)
    {
        int iRet=poll(npfds,curPfdNums,-1);
        if(iRet<0)
        {
            perror("poll failed");
            closeFd();
            break;
        }
        if(iRet==0)
        {
            continue;
        }
        if(npfds[0].revents&POLLIN)
        {
            memset(szBuf,0,1024);
            cin>>szBuf;
            for(int i=2;i<curPfdNums;++i)
            {
                iRet=write(npfds[i].fd,szBuf,strlen(szBuf));
                if(iRet<0)
                {
                    perror("write failed");
                    break;
                }
            }
            write(STDERR_FILENO,"Send:",5);
        }
        if(npfds[1].revents&POLLIN)
        {
            int clientfd=accept(npfds[1].fd,(sockaddr*)&addr,&addrlen);
            if(clientfd<0)
            {
                perror("accept failed");
                return;
            }
            cout<<endl<<"["<<clientfd<<"]client ip:"<<inet_ntoa(addr.sin_addr)<<" port:"<<ntohs(addr.sin_port)<<" connected"<<endl;
            npfds[curPfdNums].fd=clientfd;
            npfds[curPfdNums].events=POLLIN;
            curPfdNums++;
            write(STDERR_FILENO,"Send:",5);
        }
        for(int i=2;i<curPfdNums;++i)
        {
            if(npfds[i].revents&POLLIN)
            {
                read(npfds[i].fd,szBuf,1024);
                cout<<endl<<"Recv["<<npfds[i].fd<<"]:"<<szBuf<<endl;
                write(STDERR_FILENO,"Send:",5);
            }
        }
    }
}

void PollServer()
{
    cout<<"Start Server Ok"<<endl;
    int serverfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
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

    int iRet=bind(serverfd,(sockaddr*)&addr,addrlen);
    if(iRet)
    {
        perror("bind failed");
        close(serverfd);
        return;
    }

    iRet=listen(serverfd,10);
    if(iRet)
    {
        perror("listen failed");
        close(serverfd);
        return;
    }

    npfds[0].fd=STDIN_FILENO;
    npfds[0].events=POLLIN;
    curPfdNums++;
    npfds[1].fd=serverfd;
    npfds[1].events=POLLIN;
    curPfdNums++;

    pollProcess();

}

int main()
{
    PollServer();
    return 0;
}

