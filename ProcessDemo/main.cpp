#include <iostream>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

void TestPid()
{
    cout<<"My Pid:"<<getpid()<<endl;
    cout<<"My parent pid:"<<getppid()<<endl;
    cout<<"My Group:"<<getpgrp()<<endl;

    cout<<endl;
    cout<<"uid:"<<getuid()<<endl;
    cout<<"euid:"<<geteuid()<<endl;
    cout<<"gid:"<<getgid()<<endl;
    cout<<"egid:"<<getegid()<<endl;
}

void TestFork()
{
    cout<<"My pid:"<<getpid()<<endl;
    int pid=fork();
    if(pid<0)
    {
        perror("Fork Failed");
    }

    cout<<"hello world ["<<getpid()<<"]"<<endl;

    if(pid==0)
    {
        cout<<"This is child:"<<getpid()<<endl;
    }
    else
    {
        cout<<"This is parent:"<<getpid()<<endl;
    }

    while(1);
}


void TestVFork()
{
    int x=10;
    cout<<"My pid:"<<getpid()<<endl;
    int pid=vfork();
    if(pid<0)
    {
        perror("Fork Failed");
    }

    cout<<"hello world ["<<getpid()<<"]"<<endl;

    if(pid==0)
    {
        x=20;
        cout<<"This is child:"<<getpid()<<endl;
        cout<<"This is x:"<<x<<"["<<getpid()<<"]"<<endl;
        sleep(5);
    }
    else
    {
        cout<<"This is parent:"<<getpid()<<endl;
         cout<<"This is x:"<<x<<"["<<getpid()<<"]"<<endl;
    }

    _exit(0);
}

void TestExec()
{
    pid_t pid=fork();
    if(pid==0)
    {
        cout<<"I am child ["<<getpid()<<"]"<<endl;
        execl("/usr/bin/firefox","firefox","www.baidu.com",NULL);
    }
    else
    {
       cout<<"I am parent ["<<getpid()<<"]"<<endl;
    }
}

void TestEnv()
{
    cout<<"PATH="<<getenv("PATH")<<endl;
    putenv((char*)"AAA=LOOP");
    pid_t pid=fork();
    if(pid==0)
    {
        cout<<"Child AAA="<<getenv("AAA")<<endl;
    }
    else
    {
        cout<<"Parent AAA="<<getenv("AAA")<<endl;
    }

    putenv((char*)"AAA");
}

void TestWait()
{
    pid_t pid1,pid2;
    cout<<"Parent:"<<getpid()<<endl;
    pid1=fork();

    if(pid1==0)
    {
        cout<<"[1] Child:"<<getpid()<<endl;
    }
    else
    {
        int iState=0;
        pid_t pid=wait(&iState);
        cout<<"Pid="<<(int)pid<<" SIG="<<(int)(iState&0xff)<<" ExitCode="<<(int)((iState>>8)&0xff)<<endl;
    }
    pid2=fork();
    if(pid2==0)
    {
        cout<<"[2] Child:"<<getpid()<<endl;
        exit(3);
    }
    else
    {
        int iState=0;
        pid_t pid=wait(&iState);
        cout<<"Pid="<<(int)pid<<" SIG="<<(int)(iState&0xff)<<" ExitCode="<<(int)((iState>>8)&0xff)<<endl;
    }
}

void TestKill()
{
    pid_t pid1,pid2;
    cout<<"My Pid:"<<getpid()<<endl;
    pid1=fork();
    if(pid1==0)
    {
        cout<<"Child pid:"<<getpid()<<endl;
        pid2=fork();
        if(pid2==0)
        {
            cout<<"SubChild pid:"<<getpid()<<endl;
            cout<<"["<<getpid()<<"]"<<"SubChild Kill ["<<getppid()<<"]"<<endl;
            kill(getppid(),9);
            exit(0);
        }
        else
        {
            sleep(1);
        }
        cout<<"........"<<endl;
    }

    int iState=0;
    pid_t pid=wait(&iState);
    cout<<"Pid="<<(int)pid<<" SIG="<<(int)(iState&0xff)<<" ExitCode="<<(int)((iState>>8)&0xff)<<endl;
}

void TestDeamon()
{
    pid_t pid=fork();
    if(pid>0)
    {
        exit(0);
    }

    cout<<"My Parent Pid:"<<getppid()<<endl;
    pid_t pRet=setsid();  //设置依赖进程为?
    if(pRet<0)
    {
        perror("setsid failed");
        return;
    }

    chdir("/home/liushiyin");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    pid_t pid1=fork();
    if(pid1==0)
    {
        execl("/usr/bin/gedit","gedit","test.txt",NULL);
    }

    while(true)
    {
        wait(NULL);

        pid_t pid1=fork();
        if(pid1==0)
        {
            execl("/usr/bin/gedit","gedit","test.txt",NULL);
        }
    }
}

int main()
{
    //TestPid();
    //TestVFork();
    //TestExec();
    //TestEnv();
    //TestWait();
    //TestKill();
    TestDeamon();
    return 0;
}
