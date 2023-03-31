#include "Vector.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>
#include <future>
template<typename T>
Vector<T>::Vector() :_size(0), _capacity(10) {
    std::cout<<"Vector()" <<std::endl;
	_list = std::make_unique<T[]>(_capacity);
}

template<typename T>
Vector<T>::Vector(size_t capacity) :_size(0), _capacity(capacity) {
    std::cout<<"Vector(size_t)" <<std::endl;
	_list = std::make_unique<T[]>(capacity);
}

template<typename T>
Vector<T>::Vector(const std::string& fileName) :_size(0), _capacity(10000) {
    std::cout<<"Vector(const std::string&)" <<std::endl;
	_list = std::make_unique<T[]>(_capacity);
    std::ifstream file(fileName);
    if(file.is_open()){
        std::string line="";
        while(std::getline(file,line)){
            T item;
            std::istringstream iss(line);
            while(iss>> item){
                add(std::move(item));
            }
        }
    }else{
        std::cout << "failed to open file" <<std::endl;
    }

}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> initList):_size(0),_capacity(initList.size()){
    std::cout<<"Vector(std::initializer_list<T>)" <<std::endl;
    _list = std::make_unique<T[]>(_capacity);
    for(auto& i :initList){
        add(i);
    }
}
template<typename T>
Vector<T>::Vector(const Vector& other){
    std::cout<<"Vector(const Vector&)" <<std::endl;
    copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector&& other){
    std::cout<<"Vector(Vector&&)" <<std::endl;
    moveFrom(std::move(other));
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other){
    std::cout<<"operator=(const Vector&)" <<std::endl;
    if(this == &other){
        return *this;
    }
    copyFrom(other);
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other){
    std::cout<<"operator=(Vector&&)" <<std::endl;
    if(this == &other){
        return *this;
    }
    moveFrom(std::move(other));
    return *this;
}

template<typename T>
Vector<T>::~Vector()
{
    std::cout<<"~Vector()" <<std::endl;
}

template<typename T>
void Vector<T>::resize(){
    _capacity*=2;
    auto newList = std::make_unique<T[]>(_capacity);
    for(int i=0;i<_size;i++){
        newList[i] = std::move(_list[i]);
    }
    _list = std::move(newList);
}

template<typename T>
void Vector<T>::add(const T& item) {
	if (_size + 1 > _capacity) {
		resize();
	}
	_list[_size++] = item;
}

template<typename T>
void Vector<T>::remove(){
    if(isEmpty())
        throw std::runtime_error("List is empty!");
    --_size;
}
template<typename T>
void Vector<T>::print() const
{
	// for (int i = 0; i < _size; i++) {
	// 	std::cout << _list[i] << " ";
	// }

    for(auto& i: *this){
        std::cout << i << " ";
    }
	std::cout << std::endl;
}

template<typename T>
size_t Vector<T>::size()const {
    return _size;
}

template<typename T>
bool Vector<T>::isEmpty()const {
    return _size==0;
}

template<typename T>
bool Vector<T>::findSync(const T& item)const {
   std::chrono::time_point<std::chrono::system_clock> t;
   t = std::chrono::system_clock::now();
    bool result= search(begin(),end(),item);
    
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count();
    std::cout << "Search took:" <<timeSinceLastUpdate <<std::endl;
    return result;
}

template<typename T>
bool Vector<T>::findAsync(const T& item)const {

  std::chrono::time_point<std::chrono::system_clock> t;
   t = std::chrono::system_clock::now();
    int numOfThread = std::thread::hardware_concurrency();
     int chunkSize= _size/numOfThread;
     std::unique_ptr<std::future<bool>[]> ftrs = std::make_unique<std::future<bool>[]>(numOfThread);
     for(int i =0;i<numOfThread;i++){
        auto b = begin() + i * chunkSize;
        auto e = (i == numOfThread - 1) ? end() : b + chunkSize;
         ftrs[i]= std::async(std::launch::async,&Vector<T>::search,this,b,e,item);
     }
  
  bool result = false;
   for(int i =0;i<numOfThread;i++){
     if(ftrs[i].get() == true){
       result = true;
   }
  }

  
       long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count();
    std::cout << "Search took:" <<timeSinceLastUpdate <<std::endl;
    return result;
}

template<typename T>
T& Vector<T>::operator[](const size_t& index){
    if(index >=_size){
        throw std::out_of_range("Index is out of range!");
    }
    return _list[index];
}

template<typename T>
const T* Vector<T>::begin()const{
    if(isEmpty()){
        return nullptr;
    }
    return &_list[0];
}

template<typename T>
const T* Vector<T>::end()const{
    if(isEmpty()){
        return nullptr;
    }
    return &_list[_size];
}

template<typename T>
void Vector<T>::copyFrom(const Vector& other){
    _size = other._size;
    _capacity= other._capacity;

	_list = std::make_unique<T[]>(_capacity);
    for (size_t i = 0; i < _size; i++) {
		_list[i] = other._list[i];
	}
}

template<typename T>
void Vector<T>::moveFrom(Vector&& other){
    _size = other._size;
    _capacity= other._capacity;
	_list = std::move(other._list);
    other._size=0;
    other._capacity=10;
}
template<typename T>
bool Vector<T>::search(const T* begin, const T* end, const T& item)const{
    for (auto &i = begin; i!=end ;i++){
        if(*i == item){
            return true;
        }   
    }
    return false;
}