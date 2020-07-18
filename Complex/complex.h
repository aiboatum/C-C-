/*------------------------------
        created: 2020/7/17
        侯捷：C++面向对象高级编程 学习
--------------------------------*/



// 防卫式声明 guard：防止多次重复编译
#ifndef __COMPLEX
#define __COMPLEX

/***************************
 *      1.引入的头文件
 *      2. 一些前置声明：类、函数和模板的纯粹的声明，没有伴随定义，此时是incompleted type。
 **************************/
#include <iostream>
using namespace std;

class Complex;


Complex & __doapl(Complex *,const Complex &rhs);

Complex & __doami(Complex *,const Complex &rhs);

Complex & __doaml(Complex *,const Complex &rhs);


ostream & operator<<(ostream &os,const Complex &rhs);


/***************************
 * 类声明
 **************************/

class Complex{
public:
    Complex(const double& r=0,const double &i=0):
        re(r),im(i)
        {}

    Complex &operator+=(const Complex &);
    Complex &operator-=(const Complex &);
    Complex &operator*=(const Complex &);
    Complex &operator/=(const Complex &);

    double real()const{return re;}
    double imag()const{return im;}
private:
    double re;
    double im;

        // friend声明
    friend Complex & __doapl(Complex *,const Complex &rhs);
    friend Complex & __doami(Complex *,const Complex &rhs);
    friend Complex & __doaml(Complex *,const Complex &rhs);
    friend ostream &operator<<(ostream &os,const Complex &rhs);
};

/**********************************
 * 
 *      1. 类外定义的成员函数
 *      2. 全局函数
 * 
 **********************************/

inline double imag(const Complex &x){
    return x.imag();
}

inline double real(const Complex &x){
    return x.real();
}

// do assignment plus

inline Complex &__doapl(Complex *ths,const Complex &rhs){
    ths->re+=rhs.re;
    ths->im+=rhs.im;
    return *ths;
}

inline Complex &Complex::operator+=(const Complex &rhs){
    return __doapl(this,rhs);
}

// do assignment minus

inline Complex &__doami(Complex *ths,const Complex &rhs){
    ths->re-=rhs.re;
    ths->im-=rhs.im;
    return *ths;
}

inline Complex &Complex::operator-=(const Complex &rhs){
    return __doami(this,rhs);
}

// do assignment multiply

inline Complex &__doaml(Complex *ths,const Complex &rhs){
    ths->re*=rhs.re;
    ths->im*=rhs.im;
    return *ths;
}
inline Complex &Complex::operator*=(const Complex &rhs){
    return __doaml(this,rhs);
}


inline Complex &Complex::operator/=(const Complex &rhs){
    this->re=(this->re*rhs.re+this->im*rhs.im)/(rhs.re*rhs.re+rhs.im*rhs.im);

    this->im=(this->im*rhs.re-this->re*rhs.im)/(rhs.re*rhs.re+rhs.im*rhs.im);

    return *this;
}

ostream & operator<<(ostream &os,const Complex &rhs){
    return os<<'('<<rhs.real()<<','
            <<rhs.imag()<<')';
}

inline Complex
operator + (const Complex& x, const Complex& y)
{
  return Complex (real (x) + real (y), imag (x) + imag (y));
}

inline Complex
operator + (const Complex& x, double y)
{
  return Complex (real (x) + y, imag (x));
}

inline Complex
operator + (double x, const Complex& y)
{
  return Complex (x + real (y), imag (y));
}

inline Complex
operator - (const Complex& x, const Complex& y)
{
  return Complex (real (x) - real (y), imag (x) - imag (y));
}

inline Complex
operator - (const Complex& x, double y)
{
  return Complex (real (x) - y, imag (x));
}

inline Complex
operator - (double x, const Complex& y)
{
  return Complex (x - real (y), - imag (y));
}

inline Complex
operator * (const Complex& x, const Complex& y)
{
  return Complex (real (x) * real (y) - imag (x) * imag (y),
			   real (x) * imag (y) + imag (x) * real (y));
}

inline Complex
operator * (const Complex& x, double y)
{
  return Complex (real (x) * y, imag (x) * y);
}

inline Complex
operator * (double x, const Complex& y)
{
  return Complex (x * real (y), x * imag (y));
}

Complex
operator / (const Complex& x, double y)
{
  return Complex (real (x) / y, imag (x) / y);
}

inline Complex
operator + (const Complex& x)
{
  return x;
}

inline Complex
operator - (const Complex& x)
{
  return Complex (-real (x), -imag (x));
}

inline bool
operator == (const Complex& x, const Complex& y)
{
  return real (x) == real (y) && imag (x) == imag (y);
}

inline bool
operator == (const Complex& x, double y)
{
  return real (x) == y && imag (x) == 0;
}

inline bool
operator == (double x, const Complex& y)
{
  return x == real (y) && imag (y) == 0;
}

inline bool
operator != (const Complex& x, const Complex& y)
{
  return real (x) != real (y) || imag (x) != imag (y);
}

inline bool
operator != (const Complex& x, double y)
{
  return real (x) != y || imag (x) != 0;
}

inline bool
operator != (double x, const Complex& y)
{
  return x != real (y) || imag (y) != 0;
}

#include <cmath>    // 三角函数

inline Complex
polar (double r, double t)
{
  return Complex (r * cos (t), r * sin (t));
}

inline Complex
conj (const Complex& x) 
{
  return Complex (real (x), -imag (x));
}

inline double
norm (const Complex& x)
{
  return real (x) * real (x) + imag (x) * imag (x);
}


#endif 