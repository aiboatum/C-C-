#ifndef __VECTOR
#define __VECTOR

template<class T,class Alloc=alloc>
class vector{
public:
    using value_type = T;
    using iterator = value_type *;
    using reference = value_type &;
    using size_type = size_t;

protected:
    iterator start;
    iterator finish;
    iterator end_of_storage;

public:
    iterator begin(){return start;}
    iterator end(){return finish;}
    size_type size()const{return size_type(end()-begin());}
    size_type capacity()const{return size_type(end_of_storage - begin());}

    bool empty()const{return begin()==end();}
    reference operator[](size_type n){return *(begin()+n);}

    reference front(){return *begin();}
    reference back(){return *(end()-1);}


    void push_back(const value_type &x){
        if(finish!=end_of_storage)  // 尚有备用空间
        {
            // 空间配置器申请的是raw 空间
            // 需要在该空间上构造对象
            construct(finish,x);
            ++finish;
        }
        else 
            insert_aux(x);
    }
};


#endif