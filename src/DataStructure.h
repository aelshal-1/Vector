#pragma once

template<typename T>
class DataStructure{
    public:
        virtual void add(const T& item)=0;
        virtual void remove()=0;
        virtual size_t size()const =0;
        virtual bool isEmpty()const =0;
        virtual bool findSync(const T& item)const =0;
        virtual bool findAsync(const T& item)const =0;
};