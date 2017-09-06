#include <iostream>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

using namespace std;

void* ThreadFun(void*)
{
    cout<<"pthread id:"<<pthread_self()<<endl;
    for(int i=0;i<10;++i)
    {
        cout<<"Thread->:"<<i<<endl;
        usleep(1000);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int iRet=pthread_create(&tid,NULL,ThreadFun,NULL);
    if(iRet)
    {
        perror("");
        return -1;
    }

    for(int i=0;i<5;++i)
    {
        cout<<"main->:"<<i<<endl;
        usleep(1000);
    }
    pthread_join(tid,NULL);
    sleep(1);
    return 0;
}

