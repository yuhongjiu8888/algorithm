#include<stdio.h>
#include<stdlib.h>
#include<string.h>
class String
{
public:
	String(const char* str=NULL);//普通的构造函数
	String(const String& other); //拷贝构造函数
	~String();
	String& operator = (const String& other);//复制构造
private:
	char* m_data;//用于保存字符串
};
 
String::String(const char* str)
{
	if (str==NULL)
	{
		m_data = new char[1];
		*m_data = '\0';
	}
	else
	{
		int len = strlen(str);
		m_data = new char[len+1];
		strcpy(m_data, str);
	}
}
 
String::~String()
{
	if (m_data!=NULL)
	{
		delete[] m_data;
		m_data = NULL;
	}
}
 
String::String(const String & other)
{
	int len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);
}
 
String& String::operator = (const String & other)
{
	if (this==other)
	{
		return *this;
	}
	delete[] m_data;
	int len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);
	return *this;
}
