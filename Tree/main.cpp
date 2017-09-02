#include <iostream>
#include<fcntl.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include<string.h>



using namespace std;

void MyTree(char szPath[],int deep)
{
   DIR* pDir=NULL;
   dirent* pDirent=NULL;
   char szSubDir[PATH_MAX]={0};
   struct stat stInfo;
   pDir=opendir(szPath);

   while(true)
   {
       pDirent=readdir(pDir);
       if(pDirent==NULL)
       {
           break;
       }

       if(!strcmp(pDirent->d_name,".")||!strcmp(pDirent->d_name,".."))
       {
           continue;
       }

       for(int i=0;i!=deep;++i)
       {
           printf("├  ");
       }

       if(pDirent->d_type==DT_DIR)
       {
           printf("├──\033[1;34;40m %s\033[0m\n",pDirent->d_name);
           sprintf(szSubDir,"%s/%s",szPath,pDirent->d_name);
           MyTree(szSubDir,deep+1);
       }
       else
       {
           sprintf(szSubDir,"%s/%s",szPath,pDirent->d_name);
           int iRet=stat(szSubDir,&stInfo);
           if(iRet!=0)
           {
               perror("stat失败");
           }
           if(S_ISREG(stInfo.st_mode))
           {
               if(stInfo.st_mode& 0100)
               {
                    printf("├──\033[1;32;40m %s\033[0m\n",pDirent->d_name);
               }
               else
               {
                    printf("├──\033[1;37;40m %s\033[0m\n",pDirent->d_name);
               }
           }
           else
           {
                printf("├──\033[1;37;40m %s\033[0m\n",pDirent->d_name);
           }
       }
   }
}

int main()
{
    char szPath[PATH_MAX]={0};
    char* str=getcwd(szPath,PATH_MAX);
    if(str==NULL)
    {
        perror("打开目录失败");
        return -1;
    }
    MyTree(szPath,0);

    return 0;
}

