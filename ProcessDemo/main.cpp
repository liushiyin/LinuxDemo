#include <iostream>
#include<unistd.h>
#include<stdlib.h>

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

int main()
{
    //TestPid();
    //TestVFork();
    TestExec();
    return 0;
}

