//字符串转换数字

#include<iostream>
using namespace  std;

enum Status{kValue=0,kInValue};
int g_status=kValue;


long long StrToIntCore(const char* str,bool flag){
    long long num=0;
    while(*str!='\0')
    {
        if(*str>='0' && *str<='9')
        {
            int  minus = flag?-1:1;
            num = num*10+minus*(*str-'0');

            if((!flag&&num>0x7FFFFFFF) || (flag&&num<(signed int)0x80000000))
            {
                num = 0;
                break;
            } 
        }
        else
        {
            num=0;
            g_status=kInValue;
            break;
        }
        str++;
        
    }

    if(*str=='\0') g_status=kValue;

    return num;
}

int StrToInt(const char* str)
{
    long long  num=0;
    bool  flag = false;
    g_status=kInValue;
    if(str!=nullptr || *str!='\0')
    {
        if(*str=='+')
        {
            str++;
        }
        else if(*str=='-'){
            str++;
            flag = true;
        }
        
        if(*str!='\0') num = StrToIntCore(str,flag);
    }

    return (int)num;
}

int main()
{
    char *str="-123";

    int n = StrToInt(str);
    cout<<n<<endl;
    return 0;
}