#include <iostream>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

using namespace std;

typedef struct tagMsg
{
    long type;
    char szBuf[1024];
}Msg_S;

void TestKey()
{
    key_t key=ftok("a.txt",1);
    cout<<"[1]Key:"<<key<<endl;
    key_t key1=ftok("a.txt",2);
    cout<<"[2]Key:"<<key1<<endl;
    key_t key2=ftok("a.txt",1);
    cout<<"[3]Key:"<<key2<<endl;
    return;
}

void TestMsgget()
{
    key_t key=ftok("a.txt",1);
    int msgid=msgget(key,IPC_CREAT|0660);
    cout<<"msgid: "<<msgid<<endl;
}

void TestMsgRS()
{
    key_t key=ftok("a.txt",1);
    if(key==-1)
    {
        perror("ftok failed");
        return;
    }
    cout<<"Key:"<<key<<endl;
    int msgid=msgget(key,IPC_CREAT|0666);
    if(msgid==-1)
    {
        perror("msgget failed");
        return;
    }
    cout<<"Msgid:"<<msgid<<endl;

    char rs;
    Msg_S msg;
    write(STDERR_FILENO,"Select Send/Recv [s/r]",strlen("Select Send/Recv [s/r]"));
    rs=getchar();
    if('r'==rs)
    {
        while(true)
        {
            memset(&msg,0,sizeof(msg));
            write(STDERR_FILENO,"Recv type:",strlen("Recv type:"));
            int type;
            cin>>type;
            int iRet=msgrcv(msgid,&msg,1024,type,0);
            //msgrcv(msgid,&msg,strlen(msg.szBuf),type,IPC_NOWAIT);非阻塞
            //msgrcv(msgid,&msg,strlen(msg.szBuf),type,MSG_EXCEPT);接收除type之外的所有消息
            if(iRet<0)
            {
                perror("rcv failed");
                break;
            }
            cout<<msg.szBuf<<endl;
        }
    }
    if('s'==rs)
    {
        while(true)
        {
            write(STDERR_FILENO,"Send:",strlen("Send:"));
            memset(&msg,0,sizeof(msg));
            //scanf("%ld%s",&(msg.type),msg.szBuf);
            cin>>msg.type;
            cin>>msg.szBuf;
            int iRet=msgsnd(msgid,&msg,strlen(msg.szBuf),0);
            if(iRet!=0)
            {
                perror("msgsnd failed");
                break;
            }
        }
    }
}

void TestMsgCtl()
{
    key_t key=ftok("a.txt",1);
    if(key==-1)
    {
        perror("ftok failed");
        return;
    }
    cout<<"Key:"<<key<<endl;
    int msgid=msgget(key,IPC_CREAT|0666);
    if(msgid==-1)
    {
        perror("msgget failed");
        return;
    }
    cout<<"Msgid:"<<msgid<<endl;
    struct msqid_ds md;
    msgctl(msgid,IPC_STAT,&md);
    //msgctl(msgid,IPC_RMID,&md); 移除消息队列

    //msgctl(msgid,MSG_INFO,&md);
    //struct msginfo info=(struct msginfo)md;  获取消息队列信息
    cout<<md.msg_perm.__key<<endl;
}

int main()
{
    //TestKey();
    //TestMsgget();
    TestMsgRS();
    return 0;
}

