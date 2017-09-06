#ifndef CCOUNTER_H
#define CCOUNTER_H
#include<mutex>

class cCounter
{
public:

    cCounter(int id, int nums);
    ~cCounter();

    void operator() () const;
private:
    int m_Id;
    int m_nums;
    static std::timed_mutex m_timeMutex;
    //static std::mutex m_mutex;  //互斥体
};

#endif // CCOUNTER_H
