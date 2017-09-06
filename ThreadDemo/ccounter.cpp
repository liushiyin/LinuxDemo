#include "ccounter.h"
#include<iostream>
#include<chrono>

using namespace std;

//mutex cCounter::m_mutex;
timed_mutex cCounter::m_timeMutex;

cCounter::cCounter(int id, int nums):
    m_Id(id),m_nums(nums)
{
}

cCounter::~cCounter()
{
}

void cCounter::operator() () const
{
    for (int i = 0; i < m_nums; ++i)
    {
        /*
        //锁定只有当前线程使用cout
        std::lock_guard<std::mutex> lock(m_mutex);
        cout << "Counter " << m_Id << " i" << endl;*/

        //定时锁用于在200ms后获得锁
        unique_lock<timed_mutex> lock(m_timeMutex,chrono::milliseconds(200));
        if (lock)
        {
            cout << "Counter " << m_Id << " "<<i<< endl;
        }
        else
        {
            cout << "Lock not acquire in 200ms" << endl;
        }
    }
}

