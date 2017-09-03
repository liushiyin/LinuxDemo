#include <iostream>
#include<cstdio>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<sys/wait.h>

using namespace std;

void TestTime()
{
    time_t stTime;
    tm* pTmNow=NULL;
    char szTime[40]={0};

    time(&stTime);
    stTime=time(NULL);

    pTmNow=localtime(&stTime);

    cout<<pTmNow->tm_year+1900<<"/"<<pTmNow->tm_mon+1<<"/"<<pTmNow->tm_mday<<" week "<<pTmNow->tm_wday<<endl;

    strftime(szTime,40,"Time:%Y/%m/%d week:%w",pTmNow);

    cout<<szTime<<endl;

    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv,&tz);

    cout<<tv.tv_usec<<endl;
    cout<<tz.tz_minuteswest<<" "<<tz.tz_dsttime<<endl;
}

void func(int sig)
{
    cout<<strsignal(sig)<<" "<<sig<<endl;

    signal(SIGINT,SIG_DFL);  //还原信号处理函数
    return;
}

void TestSignal()
{
    cout<<"......Do something"<<endl;
    signal(SIGINT,func);

    while(1);
}

void WaitFun(int sig)
{
    cout<<strsignal(sig)<<endl;
    wait(NULL);
}

void TestIgnoreSignal()
{
    cout<<"My Pid:"<<getpid()<<endl;
    pid_t pid=fork();
    if(pid==0)
    {
        cout<<"Child Pid:"<<getpid()<<endl;
        _exit(0);
    }
    else
    {
       //signal(SIGCHLD,SIG_IGN);
        signal(SIGCHLD,WaitFun);
       cout<<"Parent loop"<<endl;
       while(true);
    }
}

void SimplaFun(int sig)
{
    cout<<"Simple "<<strsignal(sig)<<endl;
}

void ComplexFun(int sig,siginfo_t *pInfo,void *ex)
{
    sleep(5);
    cout<<"Complex "<<strsignal(sig)<<endl;
    cout<<"pid "<<pInfo->si_pid<<endl;
    cout<<"uid "<<pInfo->si_uid<<endl;
    cout<<"Extra "<<pInfo->si_value.sival_int<<endl;
}

void TestSigaction()
{
    cout<<"My Pid:"<<getpid()<<endl;
    struct sigaction act,old;
    //act.sa_handler=SimplaFun;
    act.sa_sigaction=ComplexFun;
    act.sa_flags|=SA_SIGINFO;
    act.sa_flags|=SA_NODEFER;
    //act.sa_flags|=SA_RESETHAND;//只处理一次
    sigaddset(&act.sa_mask,SIGINT);  //处理SIGUSER2时暂时不处理SIGINT

    //sigaction(SIGUSR1,&act,&old);
    sigaction(SIGUSR2,&act,&old);

    sigval_t sigv;
    sigv.sival_int=25000;
    sigqueue(getpid(),SIGUSR2,sigv);

   while(1);
}

void AlarmFun(int sig)
{
    cout<<"do...."<<sig<<endl;

    alarm(1);
}

void TestAlarm()
{
    alarm(1);

    signal(SIGALRM,AlarmFun);

    while(true);
}

void MicroFun(int sig)
{
    switch (sig)
    {
    case SIGALRM:
        cout<<"ITIMER_REAL..."<<endl; break;
    case SIGVTALRM:
        cout<<"ITIMER_VITUAL..."<<endl; break;
    case SIGPROF:
        cout<<"ITIMER_PROF..."<<endl; break;
    default:
        break;
    }
}

void TestMicroTimer()
{
    struct itimerval itv,itv1;
    itv.it_interval.tv_sec=1;
    itv.it_interval.tv_usec=500*1000;
    itv.it_value.tv_sec=1;
    itv.it_value.tv_usec=500*1000;
    setitimer(ITIMER_REAL,&itv,&itv1);
    setitimer(ITIMER_PROF,&itv,&itv1);
    setitimer(ITIMER_VIRTUAL,&itv,&itv1);

    signal(SIGALRM,MicroFun);
    signal(SIGVTALRM,MicroFun);
    signal(SIGPROF,MicroFun);

    while(1);
}

void AlarmSleepFun(int sig)
{
    write(STDERR_FILENO,".",1);
    alarm(1);
}

void TestAlarmSleep()
{
    alarm(1);

    signal(SIGALRM,AlarmSleepFun);

    while(true)
    {
        sleep(10);  //接受到信号立刻退出sleep状态
        write(STDERR_FILENO,"@",1);
    }
}

int main()
{
    //TestTime();
    //TestSignal();
    //TestIgnoreSignal();
    //TestSigaction();
    //TestAlarm();

    //TestMicroTimer();
    TestAlarmSleep();
    return 0;
}

