#pragma once
#include <memory>
#include "DataStructure.h"
#include <string>
template<typename T>
class Vector : public DataStructure<T>
{
private:
	std::unique_ptr<T[]> _list;
	size_t _size;
	size_t _capacity;

	void resize();
	void copyFrom(const Vector& other);
	void moveFrom(Vector&& other);
	bool search(const T* begin,const T* end, const T& item)const;
public:

	//defualt construtor
	Vector();
	//parameterized constructor
	Vector(size_t capacity);
	// initializer_list constructor
	Vector(std::initializer_list<T> initList);
	// copy constructor
	Vector(const Vector& other);
	// move constructor
	Vector(Vector&& other);

	//assignment operator
	Vector& operator= (const Vector& other);
	// move assignment operator
	Vector& operator= (Vector&& other);


	Vector(const std::string& );
	//destructor
	~Vector();

	void add(const T& item)override;
	void remove()override;
	void print()const;
	size_t size()const override;
	bool isEmpty()const override;

	bool findSync(const T& item)const override;
	bool findAsync(const T& item)const override;

	T& operator[](const size_t& index);

	const T* begin()const;
	const T* end()const;
};

#include "Vector.cpp"

