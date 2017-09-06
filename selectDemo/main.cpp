#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<sys/select.h>
#include<sys/time.h>

using namespace std;

#define SRV_PORT 0xabcd
#define MAX_CONN 3

void RcvMsg(int fds[], int index, int *pnConn)
{
    char szBuf[1024] = {0};
    int iRet;

    iRet = read(fds[index], szBuf, 1024);
    if (iRet < 0)
    {
        perror("Fail to read!");
    }
    else if (iRet == 0)
    {
        //disconnect.  remove fd from fds
        printf("\r[%d]Disconnect...\n", fds[index]);
        close(fds[index]);

        int j;
        for (j=index; j < *pnConn - 1; j++)
        {
            fds[j] = fds[j+1];
        }
        (*pnConn)--;
    }
    else
    {
        printf("\r[%d]Recv:%s\n", fds[index], szBuf);
    }

    return;
}

void TcpServer()
{
    int fd;
    int iRet;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("\rFail to socket!");
        return;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SRV_PORT);

    iRet = bind(fd, (struct sockaddr*)&addr, addrlen);
    if (iRet)
    {
        perror("\rFail to bind!");
        close(fd);
        return;
    }

    iRet = listen(fd, 100);
    if (iRet)
    {
        perror("\rFail to listen!");
        close(fd);
        return;
    }

    fd_set fdset;
    int maxfd = fd;
    int fds[MAX_CONN]; //client fd;
    int nConn = 0;         //client fd num.
    int i;
    int clientfd;
    struct sockaddr_in srcaddr;
    char szMsg[100];

    while(1)
    {
        FD_ZERO(&fdset);
        FD_SET(fd, &fdset);
        FD_SET(STDIN_FILENO,&fdset);

        for (i=0; i<nConn; i++)
        {
            FD_SET(fds[i], &fdset);//add client fd to fdset for monitor
        }

        fprintf(stderr, "Send:");

        iRet = select(maxfd+1, &fdset, NULL, NULL, NULL);
        if (iRet < 0)
        {
            perror("\rFail to select!");
            break;
        }
        else if (iRet == 0)
        {
            //timeout
        }
        else
        {
            if(FD_ISSET(STDIN_FILENO,&fdset))
            {
                cin>>szMsg;
                for(int i=0;i<nConn;++i)
                {
                    write(fds[i],szMsg,strlen(szMsg));
                }
            }
            if (FD_ISSET(fd, &fdset))
            {
                clientfd = accept(fd, (struct sockaddr*)&srcaddr, &addrlen);
                if (clientfd < 0)
                {
                    perror("\rFail to accept!");
                    break;
                }
                if (nConn == MAX_CONN)
                {
                    char szTip[] = "Over connect, please wait...";
                    write(clientfd, szTip, sizeof(szTip));
                    printf("\rConnect over!\n");
                    close(clientfd);
                }
                else
                {
                    char szTip[] = "Welcome!";
                    write(clientfd, szTip, sizeof(szTip));

                    printf("\r[%d]New connection form %s:%d\n", clientfd,
                        inet_ntoa(srcaddr.sin_addr), ntohs(srcaddr.sin_port));

                    fds[nConn] = clientfd;
                    nConn++;

                    if (clientfd > maxfd)
                    {
                        maxfd = clientfd;
                    }
                }
            }

            for (i=0; i<nConn; i++)
            {
                if (FD_ISSET(fds[i], &fdset))
                {
                    RcvMsg(fds, i, &nConn);
                }
            }


        }
    }

    close(fd);
}

int main()
{
    TcpServer();

    return 0;
}
