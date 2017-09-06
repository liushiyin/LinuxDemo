#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define SEM_NUM 5

void TestPV(int semid)
{
    /*
    struct sembuf sops;
    sops.sem_num = 0; //operator semphore-index-0
    //sops.sem_op  = -2; //P - operation
    sops.sem_op  = 2;  //V - operation
    sops.sem_flg = 0;

    semop(semid, &sops, 1);
    */
    struct sembuf semArr[SEM_NUM];
    int i;
    int val;
    int iRet;
    while(1)
    {
        fprintf(stderr, "Input %d num for PV:", SEM_NUM);
        for (i=0; i<SEM_NUM; i++)
        {
            scanf("%d", &val);

            semArr[i].sem_num = i;
            semArr[i].sem_op = (short)val;
            //semArr[i].sem_flg = 0;

            if (i==0)
            {
                semArr[i].sem_flg = IPC_NOWAIT;
            }

            semArr[i].sem_flg = SEM_UNDO;
        }

        iRet = semop(semid, semArr, SEM_NUM);
        if (iRet)
        {
            perror("semop failed!");
            continue;
        }
        else
        {
            printf("semop success!\n");
        }
    }

    return ;
}

void PrintSemInfo(struct semid_ds* pstSem)
{
    printf("----------------- SEMID_DS  -----------------\n");
    printf("Key        : %#x\n", pstSem->sem_perm.__key);
    printf("Ownner uid : %d\n",  pstSem->sem_perm.uid);
    printf("Ownner gid : %d\n",  pstSem->sem_perm.gid);
    printf("Creater uid: %d\n",  pstSem->sem_perm.cuid);
    printf("Creater gid: %d\n",  pstSem->sem_perm.cgid);
    printf("Mode       : %#o\n", pstSem->sem_perm.mode);
    printf("Seque      : %d\n",  pstSem->sem_perm.__seq);
    printf("\n");
    printf("Last PV   time :%d\n", (int)pstSem->sem_otime);
    printf("Last Ctrl time :%d\n", (int)pstSem->sem_ctime);
    printf("Sem-Num        :%d\n", (int)pstSem->sem_nsems);
    printf("---------------------------------------------\n");
}

void Usage()
{
    printf("\tsetall : init semphore-set value\n");
    printf("\tgetall : print semphore-set value\n");
    printf("\tipcstat: print semphore-set info\n");
    printf("\tipcset : set mode for semphore-set\n");
    printf("\texit   : exit process\n");
    return;
}

void TestSemCtl(int semid)
{
    Usage();

    struct semid_ds  stSem;
    int i;
    int iRet;
    unsigned short arr[SEM_NUM] = {};
    char szCmd[100] = {};
    while(1)
    {
        fprintf(stderr, "->");
        scanf("%s", szCmd);

        if (!strcmp(szCmd, "setall"))
        {
            int val;
            fprintf(stderr, "Input %d num for init semphore-set:", SEM_NUM);
            for (i=0; i<SEM_NUM; i++)
            {
                scanf("%d", &val);
                if (val < 0 || val > 0xffff)
                {
                    printf("Semphore-value must bigger than 0\n");
                    break;
                }
                arr[i] = (unsigned short)val;
            }
            if (i != SEM_NUM)
            {
                continue;
            }

            iRet = semctl(semid, SEM_NUM, SETALL, arr);
            if (iRet)
            {
                perror("Fail to SETALL!");
                continue;
            }
        }
        else if (!strcmp(szCmd, "getall"))
        {
            iRet = semctl(semid, SEM_NUM, GETALL, arr);
            if (iRet)
            {
                perror("Fail to GETALL!");
                continue;
            }

            printf("Sem-Value: ");
            for (i=0; i<SEM_NUM; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }
        else if (!strcmp(szCmd, "ipcstat"))
        {
            iRet = semctl(semid, SEM_NUM, IPC_STAT, &stSem);
            if (iRet)
            {
                perror("Fail to IPC_STAT!");
                continue;
            }
            PrintSemInfo(&stSem);
        }
        else if (!strcmp(szCmd, "ipcset"))
        {
            int mode;
            iRet = semctl(semid, SEM_NUM, IPC_STAT, &stSem);
            if (iRet)
            {
                printf("Fail to IPC_STAT!");
                continue;
            }

            printf("Current Mode: %#o\n", stSem.sem_perm.mode);
            fprintf(stderr, "New Mode(eg:600):");
            scanf("%o", &mode);
            if (mode < 0 || mode > 0777)
            {
                printf("Mode is invalid(range 0 to 0777).\n");
                continue;
            }

            stSem.sem_perm.mode = mode;
            iRet = semctl(semid, SEM_NUM, IPC_SET, &stSem);
            if (iRet)
            {
                perror("Fail to IPC_SET!");
                continue;
            }

            printf("Set mode success!\n");
        }
        else if (!strcmp(szCmd, "exit"))
        {
            break;
        }
        else if(!strcmp(szCmd,"semInfo"))
        {
            struct seminfo si;
            semctl(semid,SEM_INFO,&ai);

        }
        else
        {
            Usage();
        }
    }

    fprintf(stderr, "Delete Semphore-set [%d]?(y/n):", semid);
    scanf("%s",szCmd);
    if (!strcmp(szCmd, "y"))
    {
        iRet = semctl(semid, SEM_NUM, IPC_RMID, NULL);
        if (iRet)
        {
            perror("Fail to IPC_RMID!");
            return;
        }
        printf("Delete success!\n");
    }

    return;
}

int main(int argc, char ** argv)
{
    if (argc != 2 || (strcmp(argv[1], "pv") && strcmp(argv[1], "c" )))
    {
        printf("Usage: %s [pv | c]\n", argv[0]);
        printf("\t pv: For PV operation\n");
        printf("\t c : For Ctrl semphore-set\n");
        return 0;
    }

    char szFile[] = "a";

    key_t key = ftok(szFile, 1);
    if (key==-1)
    {
        perror("Fail to ftok!");
        return -1;
    }
    printf("KEY: %#x\n", key);

    int semid = semget(key, SEM_NUM, IPC_CREAT | 0660);
    if (semid < 0)
    {
        perror("fail to semget!");
        return -1;
    }
    printf("semid: %d\n", semid);

    /*
    //semid = semget(key, SEM_NUM, IPC_CREAT | 0666);
    //semid = semget(key, SEM_NUM, IPC_CREAT|IPC_EXCL| 0666);
    //semid = semget(key, SEM_NUM - 1, IPC_CREAT | 0666);
    semid = semget(key, SEM_NUM+1, IPC_CREAT | 0666);
    if (semid < 0)
    {
        perror("[2]fail to semget!");
        return -1;
    }
    printf("[2]semid: %d\n", semid);
    //*/


    if (argv[1][0] == 'p')
    {
        TestPV(semid);
    }
    else
    {
        TestSemCtl(semid);
    }
    return 0;
}
