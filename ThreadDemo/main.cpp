#include <iostream>
#include"ccounter.h"
#include<future>
#include<thread>
using namespace std;

int calculate()
{
    return 123366;
}

int main()
{
    cCounter counter(2,3);
    counter();
    cout<<"------------"<<endl;
    future<int> fut=async(calculate);
    cout<<fut.get()<<endl;
    cout << "Hello World!" << endl;
    return 0;
}

