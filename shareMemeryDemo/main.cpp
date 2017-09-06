#include <iostream>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

using namespace std;

#define FILENAME "a"
#define SHM_SIZE 0x100000

typedef struct tagStudent
{
    char stName[20];
    int age;
    char stTel[16];
}Student;

void WriteShareMemery(int shmid)
{
    Student* pStu;
    pStu=(Student*)shmat(shmid,NULL,0);
    if(pStu==(Student*)-1)
    {
        perror("shmat failed");
        return;
    }
    int index;
    Student stu;
    while(true)
    {
        cout<<"Input the offset:";
        cin>>index;
        if(index<(signed)0||index>(signed)(SHM_SIZE/sizeof(stu)))
        {
            cout<<"over range!"<<endl;
            continue;
        }
        cout<<"Input Student Info(name,age,tel):";
        cin>>stu.stName>>stu.age>>stu.stTel;
        memcpy(pStu+index,&stu,sizeof(stu));
    }
    shmdt(pStu);
}

void ReadShareMemery(int shmid)
{
    Student* pStu;
    pStu=(Student*)shmat(shmid,NULL,0);
    if(pStu==(Student*)-1)
    {
        perror("shmat failed");
        return;
    }

    int index;
    Student stu;
    while(true)
    {
        cout<<"Input the offset:";
        cin>>index;
        if(index< (signed)0||index>(signed)(SHM_SIZE/sizeof(stu)))
        {
            cout<<"over range!"<<endl;
            continue;
        }
        memcpy(&stu,pStu+index,sizeof(stu));
        cout<<"Name:"<<stu.stName<<endl;
        cout<<"age:"<<stu.age<<endl;
        cout<<"Tel:"<<stu.stTel<<endl;
    }
    shmdt(pStu);
}

int main(int argv,char** argc)
{
    if(argv!=2||(strcmp(argc[1],"r")&&strcmp(argc[1],"w")))
    {
        cout<<"[r/w]"<<endl;
        return -1;
    }

    key_t key=ftok(FILENAME,10);
    if(key<0)
    {
        perror("ftok failed key");
        return -1;
    }
    cout<<"Key:"<<key<<endl;

    int shmid=shmget(key,SHM_SIZE,IPC_CREAT|0660);
    if(shmid<0)
    {
        perror("shmget fialed");
        return -1;
    }

    if(!strcmp(argc[1],"w"))
    {
        WriteShareMemery(shmid);
    }
    else
    {
        ReadShareMemery(shmid);
    }

    return 0;
}

