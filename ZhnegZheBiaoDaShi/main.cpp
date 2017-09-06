#include <iostream>
#include<regex>
#include<string>
#include<vector>
#include<list>
using namespace std;

int main()
{
    regex r("(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])");
    string str("1996/12/03");
    smatch m;
    cout<<str<<":";
    if(regex_match(str,m,r))
    {
        cout<<"valid date year="<<m[1]<<" month="<<m[2]<<" day="<<m[3]<<endl;
    }
    else
    {
        cout<<"not valid date"<<endl;
    }
    str.assign("1996/12:30");
    cout<<str<<":";
    if(regex_match(str,r))
    {
        cout<<"valid date"<<endl;
    }
    else
    {
        cout<<"not valid date"<<endl;
    }

    regex r1("//\\s*(.+)$");
    str.assign("sdasbdhsa //  out llll");
    if(regex_search(str,m,r1))
    {
        cout<<m[1]<<endl;
    }

    //找单词
    regex r2("[\\w]+");
    str.assign("i am a good men");
    const sregex_iterator end;
    for(sregex_iterator iter(str.cbegin(),str.cend(),r2);iter!=end;++iter)
    {
        cout<<"\""<<(*iter)[0]<<"\""<<endl;
    }

    //找单词
    str.assign("i am a bad men");
    const sregex_token_iterator tend;
    for(sregex_token_iterator iter(str.cbegin(),str.cend(),r2);iter!=tend;++iter)
    {
        cout<<"\""<<*iter<<"\""<<endl;
    }

     regex r3("^(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])$");
     str.assign("2013/6/20");
     vector<int> vec{1,3};
     const sregex_token_iterator aend;
     for(sregex_token_iterator iter(str.cbegin(),str.cend(),r3,vec);iter!=aend;++iter)
     {
         cout<<"\""<<*iter<<"\""<<endl;
     }

     //切割字符串
     regex r4(("\\s*[,;]\\s*"));
     str.assign("this ,is a; dog");
     const sregex_token_iterator send;
     for(sregex_token_iterator iter(str.cbegin(),str.cend(),r4,-1);iter!=send;++iter)
     {
         cout<<*iter<<endl;
     }

     //替换
     str.assign("<body><p>sadasdnkasf</p><p>sadasdnkasf</p></body>");
     regex r5("(sadasdnkasf)");
     string result=regex_replace(str,r5,"p=sadasfsa",regex_constants::format_default);
     cout<<"old:"<<str<<endl;
     cout<<"new:"<<result<<endl;
    return 0;
}

