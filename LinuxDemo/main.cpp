#include <iostream>
#include<stdio.h>
using namespace std;

struct TestAA
{
    int x;
    int y;
    char buf[20];
};

void TestRW()
{
    FILE *pFile=fopen("aa.txt","w");
    TestAA aa={1,2,{"dasda"}};
    fwrite(&aa,sizeof(TestAA),1,pFile);
    fclose(pFile);
    FILE* pFile1=fopen("aa.txt","r");
    TestAA bb;
    fread(&bb,sizeof(TestAA),1,pFile1);
    cout<<bb.x<<" "<<bb.y<<" "<<bb.buf<<endl;
    fclose(pFile1);
}

int main()
{
    TestRW();
    return 0;
}
