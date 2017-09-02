#include <iostream>
#include<unistd.h>
#include<fcntl.h>
#include<termio.h>
#include<string.h>


using namespace std;

void TerioIflag()
{
    termio terOld,terNew;
    char szBuf[100]={0};

    ioctl(STDIN_FILENO,TCGETA,&terOld);

    terNew=terOld;
    terNew.c_iflag|=IUCLC;
    ioctl(STDIN_FILENO,TCSETA,&terNew);
    cin>>szBuf;
    cout<<"szBuf:"<<szBuf<<endl;

    ioctl(STDIN_FILENO,TCSETA,&terOld);
    cin>>szBuf;
    cout<<szBuf<<endl;
}

void TerioOflag()
{
    termio terOld,terNew;
    ioctl(STDOUT_FILENO,TCGETA,&terOld);

    terNew=terOld;
    terNew.c_oflag|=OLCUC;
    ioctl(STDOUT_FILENO,TCSETA,&terNew);
    cout<<"Hello World!"<<endl;

    ioctl(STDOUT_FILENO,TCSETA,&terOld);
    cout<<"Hello Wold!"<<endl;
}

void TestPassWord()
{
    termio terOld,terNew;
    ioctl(STDIN_FILENO,TCGETA,&terOld);

    terNew=terOld;
    terNew.c_lflag&=~ECHO;
    ioctl(STDIN_FILENO,TCSETA,&terNew);

    char szPaswd[100]={0};
    cout<<"PassWorld:";
    cin>>szPaswd;
    cout<<endl<<"Your PassWorld is:"<<szPaswd<<endl;

    ioctl(STDIN_FILENO,TCSETA,&terOld);
}

int main()
{
    //TerioOflag();
    TestPassWord();
    return 0;
}

