#include <iostream>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<cstdio>
#include<sys/types.h>
#include<sys/stat.h>

using namespace std;

void TestPipe()
{
    int fds[2];
    int iRet=pipe(fds);
    if(0!=iRet)
    {
        perror("Pipe Failed");
        return;
    }

    pid_t pid=fork();
    if(pid==0)
    {
        close(fds[1]);
        cout<<"Child pid:"<<getpid()<<endl;
        char szBuf[100]={0};
        while(true)
        {
            memset(szBuf,0,100);
            read(fds[0],szBuf,100);
            cout<<"Child Receive:"<<szBuf<<endl;
        }
        close(fds[0]);
        return;
    }
    else
    {
        close(fds[0]);
        char szBuf[100]={0};
        while(true)
        {
            usleep(100*1000);
            write(STDERR_FILENO,"Send:",5);
            read(STDIN_FILENO,szBuf,100);
            write(fds[1],szBuf,strlen(szBuf));
        }
        close(fds[1]);
    }
}

void TestTwoPipe()
{
    int fds1[2];
    int fds2[2];
    int iRet=pipe(fds1);
    if(0!=iRet)
    {
        perror("Faild to Pipe1");
        return;
    }
    iRet=pipe(fds2);
    if(0!=iRet)
    {
        perror("Failed to pipe2");
        close(fds1[0]);
        close(fds1[1]);
        return;
    }
    cout<<"My pid:"<<getpid()<<endl;

    pid_t pid=fork();
    if(pid==0)
    {
       char szBuf[100]={0};
       close(fds1[1]);
       close(fds2[0]);
       cout<<"Child pid:"<<getpid()<<endl;
       while(true)
       {
           read(fds1[0],szBuf,100);
           for(size_t i=0;i!=strlen(szBuf);++i)
           {
               szBuf[i]=toupper(szBuf[i]);
           }
           write(fds2[1],szBuf,strlen(szBuf));
       }
       close(fds1[0]);
       close(fds2[1]);
       return;
    }
    else
    {
        char szBuf[100]={0};
        close(fds1[0]);
        close(fds2[1]);
        while(true)
        {
            usleep(100*1000);
            write(STDERR_FILENO,"Send:",5);
            memset(szBuf,0,100);
            read(STDIN_FILENO,szBuf,100);
            write(fds1[1],szBuf,strlen(szBuf));

            read(fds2[0],szBuf,100);
            cout<<"Upper:"<<szBuf<<endl;
        }
        close(fds1[1]);
        close(fds2[0]);
        return;
    }
}

void TestDupForPipe()
{
    int fds[2];
    int iRet=pipe(fds);
    if(iRet)
    {
        perror("pipe to failed");
        return;
    }

    pid_t pid=fork();
    if(pid==0)
    {
        close(fds[1]);
        dup2(fds[0],STDIN_FILENO);
        execl("/bin/grep","grep","pts",NULL);
        close(fds[0]);
    }
    else
    {
       close(fds[0]);
       char szLine[100];
       int fd=open("a.txt",O_RDONLY);
       if(fd<0)
       {
           perror("open to failed");
           return;
       }
       while(true)
       {
           int iRet=read(fd,szLine,100);
           if(iRet<0)
           {
               perror("read to failed");
               break;
           }
           else if(iRet==0)
           {
               break;
           }
           else
           {
               write(fds[1],szLine,100);
           }
       }
       wait(NULL);
       close(fds[1]);
    }
}

void TestPopen()
{
    int arr[]={2,6,9,7,8,3,6,9,10,11,1,5};
    FILE* pFile=popen("sort -n","w");
    if(pFile==NULL)
    {
        perror("popen to failed");
        return;
    }
    for(size_t i=0;i<sizeof(arr)/sizeof(arr[0]);++i)
    {
        fprintf(pFile,"%d\n",arr[i]);
    }
    pclose(pFile);  //关闭并输出结果
}

void TestEx()
{
    FILE* pFile1=popen("ps -ef","r");
    FILE* pFile2=popen("grep pts","w");
    char szLine[100]={0};
    while(true)
    {
       int iRet=fread(szLine,100,1,pFile1);
       if(iRet==0)
       {
           break;
       }
       fwrite(szLine,strlen(szLine),1,pFile2);
    }
    pclose(pFile1);
    pclose(pFile2);
}

void TestFifo()
{
    char cMode;
    char pnode[100]="pnode";
    char szBuf[1024]={0};
    int fd;
    struct stat info;
    if(stat(pnode,&info)!=0)
    {
        mkfifo(pnode,0664);
    }
    else if(!S_ISFIFO(info.st_mode))
    {
        return;
    }

    write(STDERR_FILENO,"select mode [r/w]:",strlen("select mode [r/w]:"));
    cMode=getchar();
    if('r'==cMode)
    {
        fd=open(pnode,O_RDONLY);
        if(fd<0)
        {
            perror("open failed open");
            return;
        }
        while(true)
        {
            memset(szBuf,0,1024);
            int len=read(fd,szBuf,1024);
            if(len<0)
            {
                break;
            }
            else if(len==0)
            {
                continue;
            }
            else
            {
              cout<<"Recive :"<<szBuf;
            }
        }

        close(fd);
    }
    if('w'==cMode)
    {
        fd=open(pnode,O_WRONLY);
        if(fd<0)
        {
            perror("open failed open");
            return;
        }
        while(true)
        {
            memset(szBuf,0,1024);
            write(STDERR_FILENO,"Send:",5);
            read(STDIN_FILENO,szBuf,1024);
            write(fd,szBuf,1024);
        }

        close(fd);
    }

}

int main()
{
    //TestPipe();
    //TestTwoPipe();
    //TestDupForPipe();
    //TestPopen();
    //TestEx();
    TestFifo();
    return 0;
}
