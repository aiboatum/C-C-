#ifndef __MYSTRING__
#define __MYSTRING__

#include <cstring>  // strcpy

class String{
public:
    String(const char *cstr = 0);
    String(const String &str);
    String &operator=(const String &rhs);

    char *get_c_char()const{return m_data;}
    ~String();
private:
    char * m_data;
};


inline String::String(const char *cstr){
    if(cstr){
        // 利用C库函数实现
        m_data=new char[strlen(cstr)+1];
        strcpy(m_data,cstr);
    }
    else{
        m_data=new char[1];
        *m_data='\0';
    }
}

inline String::~String(){
    // 切记不可写成delete m_data;
    delete [] m_data;
}

inline String::String(const String &str){
    m_data=new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
}

inline String& String::operator=(const String &str){
    if(this==&str)return *this; // self assignment

    delete[] m_data;
    m_data=new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
    return *this;
}

#include <iostream>
using namespace std;
inline ostream &operator<<(ostream &os,const String &str){
    os<<str.get_c_char();
    return os;
}

#endif