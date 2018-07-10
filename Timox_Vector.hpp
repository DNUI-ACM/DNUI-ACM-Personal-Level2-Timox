#include<cstdio>
#include<cstdlib>
#ifndef Timox_vector
#define Timox_vector
template<typename T>
class vector
{
public:
    class reverse_iterator
    {
    private:
        T* t;
    public:
        reverse_iterator (T* a = nullptr) :t(a) {}
        bool operator != (const reverse_iterator & b){
            return t != b.t;
        }
        bool operator == (const reverse_iterator * b){
            return t == b.t;
        }
        T operator * ( ){
            return *t;
        }
        T* operator ++(){
            return --t;
        }
        T* operator--(){
            return ++t;
        }
        T* operator++(int){
            T* c = t;
            t --;
            return c;
        }
        T* operator--(int){
            T* c = t;
            t ++;
            return c;
        }
        T* operator+(size_t b){
            return t - b;
        }
        T* operator-(size_t b){
            return t + b;
        }
        T* operator+=(size_t b){
            return t -= b;
        }
        T* operator-=(size_t b){
            return t += b;
        }
    };
private:
    size_t length;
    size_t _capacity;
    T * _data;
public:
    vector()
    :length(0)
    , _capacity(1)
    {
        _data = new T [_capacity];
    }

    explicit vector (T n)
    :length(n)
    ,_capacity(n * 2)
    {
        _data = new T [_capacity];
    }

    vector(T n,T a)
    :length(n)
    ,_capacity(n * 2)
    {
        _data = new T [_capacity];
        for(auto i = 0; i < n; i ++)
            _data[i] = a;
    }

    vector(const vector & a)
    :length(a.length)
    ,_capacity(a.capacity)
    {
        for(auto i = 0; i < length; i ++)
            _data[i] = a._data[i];
    }

    ~vector()
    {
        delete [] _data;
    }

	vector & operator =(const vector& b)//???
	{
	    if(*this != b)
	    {
	    	T* r = _data;
	    	length = b.length;
	    	_capacity = b._capacity;
	    	T * ndata = new T [_capacity];
	    	for(auto i = b.begin(); i < b.end(); i++)
	    	    ndata[i]	= b._data[i];
            _data = ndata;
            delete r;
	    }
	    return *this;
	}

    T & at( size_t pos )
    {
        if(pos < 0 || pos > length)
            exit(1);
        return _data[pos];
    }
    const T & at( size_t pos ) const
    {
        if(pos < 0 || pos > length)
            exit(1);
        return _data[pos];
    }

    T & front(){    return *begin();}
    const T & front()const{    return *begin();}

    T & back(){     return --(*end());}
    const T & back()const{     return --(*end());}

    T* data() noexcept{     return _data;}
    const T* data() const noexcept{     return _data;}

    T operator [](const size_t x){
        return _data[x];
    }

    T * begin(){    return _data;}
    // T * begin() noexcept{    return _data;}
     const T * begin() const{    return _data;}
    // const T * cbegin() const noexcept{    return _data;}

    T * end(){  return _data + length;}
    //T * end() noexcept{  return _data + length;}
    const T * end() const{  return _data + length;}
    //const T * cend() const noexcept{  return _data + length;}

    reverse_iterator rbegin(){   return _data + length - 1;}
    // reverse_iterator rbegin() noexcept{   return _data + length - 1;}
    const reverse_iterator rbegin() const{   return _data + length - 1;}
    // const reverse_iterator crbegin() const noexcept{   return _data + length - 1;}

    reverse_iterator rend();
    // reverse_iterator rend() noexcept;
    const reverse_iterator rend() const;
    // const reverse_iterator crend() const noexcept;

    size_t size(){
        return length;
    }

    size_t capacity(){
        return _capacity;
    }

    bool empty(){
        return length == 0;
    }

    // size_t max_size() const
    // {
    //     return _capacity;
    // }

    // size_t max_size() const noexcept
    // {
    //     return _capacity;
    // }

    void reserve( size_t new_cap )
    {
        if(new_cap > length){
            size_t a = length;
            capacity = new_cap;
            T * r = _data;
            T * ndata = new T [capacity];
            for(auto i = 0; i < a; i)
                ndata[i] = _data[i];
            _data = ndata;
            delete [] r;
        }
    }

    void shrink_to_fit()
    {
            T * r = _data;
            _capacity = length;
            T * ndata = new T [_capacity];
            for(auto i = 0; i < length; i ++)
                ndata[i] = _data[i];
            _data = ndata;
            delete [] r;
    }

    void clear()
    {
        length = 0;
    }

    // void clear() noexcept
    // {
    //     length = 0;
    // }

    T * insert( T * pos,const T & n)
    {
        length ++;
        if(length > capacity){
            T * r = _data;
            capacity = capacity * 2;
            T * ndata = new T [capacity];
            for(auto i = 0; i < length; i ++)
                ndata[i] = _data[i];
            _data = ndata;
            delete [] r;
        }
        for(auto i = back(); i != pos; i --)
            * i = * (i - 1);
        *pos = n;
        return pos;
    }

    T* erase( T* pos )
    {
        if(length == 0)
            exit(1);
        length--;
        for(auto i = pos; i < length; i ++)
            *i = * (i + 1);
        return pos;
    }

    void push_back( const T& n )
    {
        length++;
        if(length > capacity){
            T * r = _data;
            capacity = capacity * 2;
            T * ndata = new T [capacity];
            for(size_t i = 0; i < length; i ++)
                ndata[i] = _data[i];
            _data = ndata;
        }
        _data[length] = n;
    }

    void pop_back()
    {
        if(length > 0)
            length--;
    }

    void resize(size_t count)
    {
        if(count < length)
        {
            length = count;
            reserve(count * 2);
        }
        else {
            reserve(count * 2);
            length = count;
        }
    }

    void resize( size_t count, const T & n )
    {
        if(count < length){
            length = count;
            reserve(count * 2);
        }
        else
        {
            reserve(count * 2);
            for(size_t i = length; i < count; i ++)
                _data[i] = n;
            length = count;
        }
    }

    void swap( vector & b )
    {
        T * t1 = _data;
        _data = b._data;
        b._data = t1;
        delete [] t1;
        size_t t2 = length;
        length = b.length;
        b.length = t2;
        size_t t3 = _capacity;
        _capacity = b._capacity;
        b._capacity = t3;
    }
};
#endif