#include <iostream>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<list>

using namespace std;
//120.203.57.239

#define MAX_NUM 3
#define SRV_PORT 0xabcd
std::list<int> g_clientList;

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

    cout<<"Start server ok"<<endl;
    eplid=epoll_create(100);
    if(eplid<0)
    {
        perror("epoll_create failed");
        close(serverfd);
        return;
    }

    epoll_event epv;
    epv.events=EPOLLIN;
    epv.data.fd=STDIN_FILENO;

    epoll_ctl(eplid,EPOLL_CTL_ADD,STDIN_FILENO,&epv);

    epv.events=EPOLLIN;
    epv.data.fd=serverfd;
    epoll_ctl(eplid,EPOLL_CTL_ADD,serverfd,&epv);

    epoll_event epvs[MAX_NUM];
    int nRets;
    sockaddr_in clientaddr;
    socklen_t clientaddrlen=sizeof(clientaddr);
    char szBuf[1024]={0};

    while(true)
    {
        write(STDERR_FILENO,"Send:",5);
        nRets=epoll_wait(eplid,epvs,MAX_NUM,-1);
        if(nRets<0)
        {
            perror("epoll_=wait failed");
            break;
        }
        if(nRets==0)
        {
            continue;
        }

        for(int i=0;i<nRets;++i)
        {
            if(epvs[i].data.fd==STDIN_FILENO)
            {
                memset(szBuf,0,1024);
                read(STDIN_FILENO,szBuf,1024);
                for(auto it:g_clientList)
                {
                    write(it,szBuf,strlen(szBuf));
                }
            }
            else if(epvs[i].data.fd==serverfd)
            {
                int clientfd=accept(serverfd,(sockaddr*)&clientaddr,&clientaddrlen);
                if(clientfd<0)
                {
                    perror("accept fialed");
                    break;
                }
                cout<<"\ncleint addr:"<<inet_ntoa(clientaddr.sin_addr)<<" port:"<<ntohs(clientaddr.sin_port)<<" connected"<<endl;
                epv.events=EPOLLIN;
                epv.data.fd=clientfd;
                epoll_ctl(eplid,EPOLL_CTL_ADD,clientfd,&epv);
                g_clientList.push_back(clientfd);

            }
            else
            {
                memset(szBuf,0,sizeof(szBuf));
                iRet=read(epvs[i].data.fd,szBuf,1024);
                if(iRet<0)
                {
                    perror("read");
                    break;
                }
                else if(iRet==0)
                {
                    cout<<"\nclient ["<<epvs[i].data.fd<<"]"<<" disconnected"<<endl;
                    close(epvs[i].data.fd);
                    g_clientList.remove(epvs[i].data.fd);
                    continue;
                }
                cout<<"\nRecv ["<<epvs[i].data.fd<<"]:"<<szBuf<<endl;
            }
        }
    }

    close(serverfd);
}

int main()
{
    epollServer();
    return 0;
}

