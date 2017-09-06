#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

#define RAM_PORT 0x9900

//Ip头结构体
typedef struct tagIpHeader
{
    unsigned char ucHeadLen:4;
    unsigned char ucVer:4;

    unsigned char ucTos;
    unsigned short usLen;
    unsigned short usIdent;

    unsigned short usOffset:13;
    unsigned short usFlag:3;

    unsigned char ucTTL;
    unsigned char ucProtocol;

    unsigned short usChkSum;

    unsigned int uiSrcIp;
    unsigned int uiDstIp;

    char data[0];
}IPHEAD_S;

typedef struct tagTcpHeader
{
    unsigned short srcPort;
    unsigned short dstPort;
    unsigned int   uiSeq;
    unsigned int   uiSeqQ;
    unsigned short fin:1;
    unsigned short syn:1;
    unsigned short rst:1;
    unsigned short psh:1;
    unsigned short ack:1;
    unsigned short urg:1;
    unsigned short res:6;
    unsigned short usHeadLen:4;
    unsigned short usWinLen;
    unsigned short usChkSum;
    unsigned short usUrgPtr;
    unsigned char  data[0];
}TCPHEAD_S;

void printIpHeader(IPHEAD_S* pHead)
{
    cout<<"---------------- IP HEAD ---------------"<<endl;
    cout<<"version   :"<<(int)pHead->ucVer<<endl;
    cout<<"headLen   :"<<(int)pHead->ucHeadLen<<endl;
    cout<<"Tos       :"<<(int)pHead->ucTos<<endl;
    cout<<"usLen     :"<<ntohs(pHead->usLen)<<endl;
    cout<<"usIdentify:"<<ntohs(pHead->usIdent)<<endl;
    cout<<"usOffset  :"<<(int)pHead->usOffset<<endl;
    cout<<"usFalg    :"<<(int)pHead->usFlag<<endl;
    cout<<"ucTTL     :"<<(int)pHead->ucTTL<<endl;
    cout<<"ucPtl     :"<<(int)pHead->ucProtocol<<endl;
    cout<<"chkSum    :"<<ntohs(pHead->usChkSum)<<endl;

    sockaddr_in addr;
    addr.sin_addr.s_addr=pHead->uiSrcIp;
    cout<<"srcIP     :"<<inet_ntoa(addr.sin_addr)<<endl;
    addr.sin_addr.s_addr=pHead->uiDstIp;
    cout<<"dstIP     :"<<inet_ntoa(addr.sin_addr)<<endl;
    cout<<"----------------------------------------"<<endl;
}

void printTcpHeader(TCPHEAD_S* pHead)
{
    cout<<"--------------- TCP Head ---------------"<<endl;
    cout<<"SrcPort    :"<<ntohs(pHead->srcPort)<<endl;
    cout<<"DstPort    :"<<ntohs(pHead->dstPort)<<endl;
    cout<<"uiSep      :"<<ntohs(pHead->uiSeq)<<endl;
    cout<<"uiSepQ     :"<<ntohs(pHead->uiSeqQ)<<endl;
    cout<<"Fin        :"<<pHead->fin<<endl;
    cout<<"Syn        :"<<pHead->syn<<endl;
    cout<<"Rst        :"<<pHead->rst<<endl;
    cout<<"Psh        :"<<pHead->psh<<endl;
    cout<<"Ack        :"<<pHead->ack<<endl;
    cout<<"Urg        :"<<pHead->urg<<endl;
    cout<<"Res        :"<<pHead->res<<endl;
    cout<<"UsHeadLen  :"<<pHead->usHeadLen<<endl;
    cout<<"UsWinLen   :"<<ntohs(pHead->usWinLen)<<endl;
    cout<<"UsChkSum   :"<<ntohs(pHead->usChkSum)<<endl;
    cout<<"UsUrgPtr   :"<<ntohs(pHead->usUrgPtr)<<endl;
    cout<<"----------------------------------------"<<endl;
}

void captureData()
{
    sockaddr_in addr;
    socklen_t addlen=sizeof(addr);
    int sockfd=socket(PF_INET,SOCK_RAW,IPPROTO_TCP);
    //int sockfd=socket(PF_INET,SOCK_RAW,IPPROTO_ICMP);抓取ping包
    if(sockfd<0)
    {
        perror("socket faield");
        return;
    }

    addr.sin_family=AF_INET;
    addr.sin_port=(RAM_PORT);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);

    int iRet=bind(sockfd,(sockaddr*)&addr,addlen);
    if(iRet)
    {
        perror("bind failed");
        close(sockfd);
        return;
    }

    char szbuf[2000]={};
    while(true)
    {
        memset(szbuf,0,sizeof(szbuf));
        int iRet=read(sockfd,szbuf,2000);
        if(iRet<0)
        {
            perror("read fialed");
            break;
        }
        //printf("%s",szbuf);
        IPHEAD_S *pHead=(IPHEAD_S*)szbuf;
        printIpHeader(pHead);
        TCPHEAD_S *pTcpHead;
        pTcpHead=(TCPHEAD_S*)pHead->data;
        printTcpHeader(pTcpHead);
        cout<<"Data:"<<pTcpHead->data<<endl;
    }
    close(sockfd);
}

int main()
{
    captureData();
    return 0;
}

