/*
单例模式：全局唯一实例
恶汉模式：线程安全
懒汉模式：线程非安全
*/
#include<iostream>
#include <mutex>
using namespace std;


std::mutex mtx;

class Singleton{
public:
    static Singleton* getInstance(){//得到唯一实例接口
        if(m_handle==nullptr){
            //这里使用了两次判断m_handle == NULL，这就是大家所说双检锁机制，因为进行一次加锁和解锁是需要付出对应的代价，而进行两次判断，就可以避免多次加锁和解锁操作，同时也保证了线程安全。
            mtx.lock();
            if(m_handle==nullptr){
                m_handle = new Singleton();
                cout << "唯一创建(访问)实例的方法" << endl;
            }
            
            mtx.unlock();
        }

        return m_handle;
    }

private:
    Singleton(){}; //构造函数设计成私有的

    static Singleton* m_handle; //用类的指针指向唯一的实例

    

    class GC{//资源释放
    public:
        ~GC(){
            if(m_handle){
                delete m_handle;
                m_handle = nullptr;
            }
        }
    };

    static GC gc;

};

Singleton* Singleton::m_handle = NULL;
 
int main(int argc, char*argv[])
{
	Singleton *object = Singleton::getInstance();
 
	return 0;
}

//恶汉模式
class CSingleton
{
public:
	static CSingleton * getSingleton()
	{
		return mInstance;
	}

	
	~CSingleton()
	{
		delete mInstance;
		mInstance = NULL;
		cout << "~CSingleton()" << endl;
	}

	class CDestroy
    {
    public:
        ~CDestroy()
        {
			if(CSingleton::mInstance != NULL)
			{
				delete CSingleton::mInstance;
				mInstance = NULL;
				cout << "~CSingleton()" << endl;
			}   
        }
    };

    static CDestroy mDel;

private:
	static CSingleton * mInstance;

	CSingleton() 
	{
		cout << "CSingleton()" << endl;
	}
};

CSingleton* CSingleton :: mInstance = new CSingleton();
CSingleton::CDestroy mDel;

int main()
{
	cout << "Process Begin" << endl;
	CSingleton *s1 = CSingleton::getSingleton();
	CSingleton *s2 = CSingleton::getSingleton();
	cout << "s1 = " << s1 << endl << "s2 = "<< s2 << endl;  
	return 0;
}
