#include<stdio.h>
#include<stdlib.h>
#ifndef VECTOR_Timox
#define VECTOR_Timox
template<typename T>
class vector
{
public:
    using iterator=T*;
    using size_type=size_t;
    using value_type=T;
    using difference_type=ptrdiff_t;
    using reference=T&;
    using const_reference=const T&;
    using pointer=T*;
    using const_pointer=const T*;
    using const_iterator=const T*;
    class reverse_iterator
    {
    private:
        pointer t;
    public:
        reverse_iterator(pointer W = nullptr) : t(W) {}
        value_type operator *(){    return *t;}
        bool operator !=(const reverse_iterator & it) const{    return t != it.t;}
        bool operator ==(const reverse_iterator & it) const{    return t == it.t;}
        reverse_iterator operator +=(size_type it){    return t-=it;}
        reverse_iterator operator -=(size_type it){    return t+=it;}
        reverse_iterator operator +(size_type it){    return t-it;}
        reverse_iterator operator -(size_type it){    return t+it;}
        reverse_iterator operator ++(){    return --t;}
        reverse_iterator operator --(){    return ++t;}
        void operator ++(int)
        {
            pointer tmp = t;
            --t;
            return tmp;
        }
        void operator --(int)
        {
            pointer tmp = t;
            ++t;
            return tmp;
        }
    };
private:
    size_type length;
    size_type capacity_;
    pointer data_;
public:
    size_type size(){    return length; }
    size_type capacity(){    return capacity_;}
    bool empty(){    return length==0;}
    value_type operator [] (size_type pos){return data_[pos];}
    vector & operator = (vector tmp)
    {
        vector n;
        for(auto i=tmp.begin();i!=tmp.end();i++)
            n.push_back(tmp);
        return n;
    }
    vector()
    {
        length=0;
        capacity_=1;
        data_=new value_type[capacity_];
    }
    explicit vector(size_type nums)
    {
        length=nums;
        capacity_=2*nums;
        data_=new value_type[capacity_];
    }
    vector(size_type nums,value_type t)
    {
        length=nums;
        capacity_=2*nums;
        data_=new value_type[capacity_];
        for(size_type i=0;i<nums;i++)
            data_[i]=t;
    }
    vector(const vector &v)
    {
        length=v.length;
        capacity_=v.capacity_;
        data_=new value_type[capacity_];
        for(size_type i=0;i<capacity_;i++)
            data_[i]=v.data_[i];
    }
    vector(iterator a,iterator b)
    {
        length=0;
        capacity_=1;
        data_=new value_type[capacity_];
        while(a!=b)
        {
            push_back(a);
            a++;
        }
    }
    ~vector()
    {
        delete[] data_;
    }
    void reserve(size_type num)
    {
        if(num<=lenth)
            return ;
        size_type r=capacity_;
        capacity_=num;
        pointer fr=data_;
        pointer ndata_=new value_type[capacity_];
        for(size_type i=0;i<r;i++)
            ndata_[i]=data_[i];
        data_=ndata_;
        delete fr;
    }
    void resize(size_type num)
    {
        if(num<=length)
        {
            length=num;
            reserve(2*num);
            return;
        }
        reserve(2*num);
        length=num;
    }
    void resize(size_type num,value_type value)
    {
        if(num<=length)
        {
            length=num;
            reserve(2*num);
            return;
        }
        reserve(2*num);
        for(size_type i=length;i<num;i++)
            data_[i]=value;
        length=num;
    }
    reference front(){   return *begin();}
    reference back()
    {
        iterator endIt = end();
        return *(--endIt);
    }
    const_reference back() const{    return *(--end());}
    reference at(size_type pos)
    {
        if(pos<0||pos>length)
            exit(1);
        return data_[pos];
    }
    iterator begin(){    return data_;}
    const_iterator begin() const{    return data_;}
    const_iterator cbegin() const noexcept{    return data_;}

    iterator end(){    return data_+length;}
    const_iterator end() const{    return data_+length;}
    const_iterator cend() const noexcept{    return data_+length;}

    reverse_iterator rbegin(){    return data_+length-1;}
    const reverse_iterator rbegin() const{    return data_+length-1;}
    const reverse_iterator crbegin() const noexcept{    return data_+length-1;}

    reverse_iterator rend(){    return data_-1;}
    const reverse_iterator rend() const{    return data_-1;}
    const reverse_iterator crend() const noexcept{    return data_-1;}

    void push_back(const iterator A)
    {
        data_[length++] = *A;
        if(length == capacity_)
        {
            capacity_ *= 2;
            pointer fr = data_;
            pointer data_2 = new value_type[capacity_];
            for(size_type i = 0; i < capacity_ / 2; i ++)
                data_2[i]=data_[i];
            data_=data_2;
            delete fr;
        }
    }   
    void push_back(const value_type a)
    {
        data_[length++]=a;
        if(length==capacity_)
        {
            capacity_*=2;
            pointer fr=data_;
            pointer data_2=new value_type[capacity_];
            for(size_type i=0;i<capacity_/2;i++)
                data_2[i]=data_[i];
            data_=data_2;
            delete fr;
        }
    }
    void pop_back()
    {
        if(length==0)
            exit(1);
        length--;
    }
    iterator erase(iterator iter)
    {
        if(length==0)
            exit(1);
        length--;
        for(auto i=iter;i!=end();i++)
            *i=*(i+1);
        return iter;
    }
    iterator erase(size_type pos)
    {
        if(length==0)
            exit(1);
        length--;
        for(size_type i=pos;i<length;i++)
            data_[i]=data_[i+1];
        return begin()+pos;
    }
    void swap(vector & s)
    {
        pointer tmpdata_=data_;
        data_=s.data_;
        s.data_=tmpdata_;
        size_type tmplength=length;
        length=s.length;
        s.length=tmplength;
        size_type tmpcapacity_=capacity_;
        capacity_=s.capacity_;
        s.capacity_=tmpcapacity_;
    }
    void assign(size_type num,const_reference value )
    {
        if(length<num)
        {
            size_type i=0;
            for(;i<length;i++)
                data_[i]=value;
            for(;i<num;i++)
                push_back(value);
        }else
        {
            length=num;
            for(size_type i=0;i<length;i++)
                data_[i]=value;
        }
    }
    pointer data()
    {
        return data_;
    }
    void shrink_to_fit()
    {
        capacity_=length+1;
        pointer tmp=data_;
        pointer ndata_=new value_type[capacity_];
        for(size_type i=0;i<length;i++)
            ndata_[i]=data_[i];
        data_=ndata_;
        delete[] tmp;
    }
    void clear()
    {
        while(length)
        {
            pop_back();
        }
    }
    iterator insert(iterator pos,const_reference value)
    {
        length++;
        if(length==capacity_)
        {
            capacity_*=2;
            pointer tmp=data_;
            pointer ndata_=new value_type[capacity_];
            for(size_type i=0;i<length;i++)
                ndata_[i]=data_[i];
            data_=ndata_;
            delete[] tmp;
        }
        for(auto i=end()-1;i!=pos;i--)
            *i=*(i-1);
        *pos=value;
        return pos;
    }    
};
#endif