#include<stdio.h>
#ifndef VECTOR_H
#define VECTOR_H

#define  SPACE_CAPACITY 5
namespace stl
{
    template<typename Object>
    class Vector
    {
    private:
        int theSize;
        int theCapacity;
        Object* Objects;
    public:
        explicit Vector(int initsize = 0)
            :theSize(initsize)
            ,theCapacity(initsize + SPACE_CAPACITY)
        {
            Objects = new Object[theCapacity]; 
        }
        Vector(const Vector& V)
            :theSize(0)
            ,theCapacity(0)
            ,Objects(NULL)
        {
            *this = V;
        }
        ~Vector()
        {
            delete[ ] Objects;
        }
        Vector &operator = (const Vector& ths)
        {
            if (this != ths)
            {
                delete [] Objects;
                theSize = ths.theSize;
                theCapacity = ths.theCapacity;
                Objects = new Object[theCapacity];
                for (int i = 0; i < ths.theSize; ++i)
                {
                    Objects[i] = ths.Objects[i];
                }
            }
            return *this;
        }
        void resize(int newSize)
        {
            if (newSize <= theSize)
                return;
            if(newSize > theCapacity)
                reserve(2 * newSize + 1);
            theSize = newSize;
        }
        void reserve(int newCapacity)
        {
            if (newCapacity < theSize)
            {
                return;
            }
            Object * temp = Objects;
            Objects = new Object[newCapacity];
            for (int i = 0;  i < theSize; ++i)
            {
                Objects[i] = temp[i];
            }
            delete[] temp;
        }
        Object& operator[] (int index)
        {
            return Objects[index];
        }

        const Object& operator[] (int index) const
        {
            return Objects[index];
        }

        bool isEmpty() const
        {
            return size() == 0;
        }

        int size() const
        {
            return theSize;
        }

        int capacity() const
        {
            return theCapacity;
        }

        void push_back(Object obj)
        {
            if (theSize == theCapacity)
            {
                reserve(2 * theCapacity + 1);
            }
            Objects[theSize++] = obj;
        }

        void pop_back()
        {
            --theSize; 
        }

        const Object & back() const
        {
            return Objects[size() - 1];
        }

        typedef Object* iterator;
        typedef const Object* const_iterator;

        iterator begin()
        {
            return &Objects[0];
        }

        iterator end()
        {
            return &Objects[size()];
        }

        const_iterator cbegin() const
        {
            return &Objects[0];
        }

        const_iterator cend() const
        {
            return &Objects[size()];
        }


    };
}
#endif



