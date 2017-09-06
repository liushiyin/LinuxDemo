#include <iostream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<utility>
#include<ratio>
#include<chrono>
using namespace std;
using namespace chrono;

int func(int a)
{
    cout<<a<<endl;
    return 1;
}

//chrono::minutes operator"" _minl(long d)  //定义minutes字面量
//{
//    minutes min(d);
//    return min;
//}

//chrono::seconds operator"" _secl(long d)
//{
//    seconds sec(d);
//    return sec;
//}

//chrono::hours operator"" _houl(long d)
//{
//    hours hou(10);
//    return hou;
//}

int main()
{
    //函数对象
    function<int(int)> f=func;
    f(100);

    //有理数加减乘除
    cout<<"有理数加减乘除"<<endl;
    typedef ratio<1,30> r1;
    typedef ratio<1,60> r2;
    typedef ratio_add<r1,r2>::type result;
    typedef ratio_subtract<r1,r2>::type result1;
    typedef ratio_multiply<r1,r2>::type result2;
    typedef ratio_divide<r1,r2>::type result3;
    cout<<result::num<<"/"<<result::den<<endl;
    cout<<result1::num<<"/"<<result1::den<<endl;
    cout<<result2::num<<"/"<<result2::den<<endl;
    cout<<result3::num<<"/"<<result3::den<<endl;

    //有理数比较
    cout<<"有理数比较"<<endl;
    typedef ratio_less<r1,r2> res;
    cout<<boolalpha<<res::value<<endl;
    typedef ratio_equal<r1,r2> res1;
    cout<<boolalpha<<res1::value<<endl;
    typedef ratio_greater<r1,r2> res2;
    cout<<boolalpha<<res2::value<<endl;
    typedef ratio_greater_equal<r1,r2> res3;
    cout<<boolalpha<<res3::value<<endl;

    //持续时间
    cout<<"持续时间"<<endl;
    duration<long,ratio<1>> sec(30);  //30秒
    cout<<sec.count()<<"s"<<endl;
    duration<double,ratio<1,1000>> mili(100);  //100毫秒
    cout<<mili.count()<<"mili"<<endl;
    duration<long,ratio<60>> minu(10);  //10分钟
    cout<<minu.count()<<"min"<<endl;
    duration<long,ratio<3600>> hou(2);  //2个小时
    cout<<hou.count()<<"hours"<<endl;
    nanoseconds nanom(100); //100纳秒
    cout<<nanom.count()<<"nam"<<endl;
    microseconds misec(100);  //100微秒
    cout<<misec.count()<<"mis"<<endl;
    seconds secs(100);  //100秒
    cout<<secs.count()<<"s"<<endl;
    minutes minus(100);  //100分钟
    cout<<minus.count()<<"min"<<endl;
    hours hous(100);  //100小时
    cout<<hous.count()<<"hou"<<endl;
//    seconds secd=9_secl;
//    cout<<secd.count()<<"_sec"<<endl;
//    minutes mins=8_minl;
//    cout<<mins.count()<<"_min"<<endl;
//    hours hiu=9_houl;
//    cout<<hiu.count()<<"_hou"<<endl;

    return 0;
}

