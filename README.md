# CPPND: Capstone Vector Repo

This is my own version of Vector of STL with

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Vector`.

## Project Description

This is my own implementation of Vector from STL
we have 3 main files
1. DataStructure.h
	* this is an abstract class for all datastructure as we can add more of STL like Stack, dqueue and more
2. Vector.h
	* it's the vector class inherited from DataStructure class and implements its methods
3. Vector.cpp
	* the implementation of Vector class

you can use the Vector class to create Vector of your own choice of type
you can init the vector using initializer list or read data from file.

## rubric points 
1. Loops, Functions, I/O
	*The project demonstrates an understanding of C++ functions and control structures.
	*The project reads data from a file and process the data, or the program writes data to a file.	
		* in Vector.cpp line 21 Vector<T>::Vector(const std::string& fileName) this constructor read data from file 'numbers.txt' and add it to list
	*The project accepts user input and processes the input.
		* in main line 9 we init vector from user input
2. Object Oriented Programming
	*The project uses Object Oriented Programming techniques.
		* there is DataStructure class and Vector Class wich inherited from it.
	*Classes use appropriate access specifiers for class members.
	*Class constructors utilize member initialization lists. in vector.cpp from line 9
	*Classes abstract implementation details from their interfaces.
	*Classes encapsulate behavior.
	*Classes follow an appropriate inheritance hierarchy.
		* see DataStructure.h class 
	*Overloaded functions allow the same function to operate on different parameters.
		* there is operator overloading in Vector.h line 49 T& operator[](const size_t& index)
	*Derived class functions override virtual base class functions.
		* there are many function line add, remove, size, isEmpty, findSync and findAsync in Vector.h 
	*Templates generalize functions in the project.
		* Class Vector is using Templates
4. Memory Management
	*The project makes use of references in function declarations.
		* you will find passing by references in most of methods in Vector.h line 14,26,31,40 etc
	*The project follows the Rule of 5.
		* there is an implementation of constructor, copy consturcor, move constructor, assignment operator , move assignment operator and destructor in vector.h from line 20 to line 38
	*The project uses move semantics to move data, instead of copying it, where possible.
		* in line 31,57,75 
	*The project uses smart pointers instead of raw pointers.
		* in Vector.h line 9 I used unique_ptr
3. Concurrency
	*A promise and future is used in the project.
		* in Vector.cpp line 144 bool Vector<T>::findAsync(const T& item)const
		* this methods uses divide the list into chunks and makse async task for each chunk to search in it and wait the result for all threads
