#pragma once
#include<iostream>
using namespace std;


template<typename T>
class Vector{
    T* buff;
    unsigned int  _capacity;
    unsigned int current;

    public:
    typedef T *iterator;
    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T& initial);
    Vector(const Vector<T>& v);
    ~Vector();

    int size() const;
    int capacity() const;
    bool empty() const;

    iterator begin();
    iterator end();

    T& front();
    T& back();

    void push_back(const T& value);
    void pop_back();

    void reserve(int capacity); 
    void resize(int size);

    T& operator[](int index);
    Vector<T>& operator=(const Vector<T>& v);

    void clear();
};


template<typename T>
Vector<T>::Vector(){
    _capacity = 0;
    current = 0;
    buff = NULL;
}

template<typename T>   
Vector<T>::Vector(unsigned int size){
    _capacity = size;
    current = size;
    buff = new T[size];
}

template<typename T>
Vector<T>::Vector(unsigned int size, const T& initial){
    _capacity = size;
    current = size;
    buff = new T[size];
    for(int i=0; i<size; i++){
        buff[i] = initial;
    }
}

template<typename T>
Vector<T>::Vector(const Vector<T>& v){
    _capacity =v.capacity();
    current = v.current;
    buff = new T[_capacity];
    for(int i=0; i<current; i++){
        buff[i] = v.buff[i];
    }
}


template<typename T>
Vector<T>::~Vector(){
    delete[] buff;
}

template<typename T>
int Vector<T>::size() const{
    return current;
}   

template<typename T>
int Vector<T>::capacity() const{
    return _capacity;
}

template<typename T>
bool Vector<T>::empty() const{
    return current == 0;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin(){
    return buff;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end(){
    return buff + current;
}

template<typename T>
T& Vector<T>::front(){
    return buff[0];
}

template<typename T>
T& Vector<T>::back(){
    return buff[current-1];
}

template<typename T>
void Vector<T>::push_back(const T& value){
    if(current == _capacity){
        reserve(_capacity+5);
    }
    buff[current] = value;
    current++;
}

template<typename T>
void Vector<T>::pop_back(){
    current--;
}

template<typename T>
void Vector<T>::reserve(int capacity){
    T* new_buff = new T[capacity];
    for(int i=0; i<current; i++){
        new_buff[i] = buff[i];
    }
    delete[] buff;
    buff = new_buff;
    this->_capacity = capacity;
}

template<typename T>
void Vector<T>::resize(int size){
    reserve(size);
    current = size;
}

template<typename T>
T& Vector<T>::operator[](int index){
    return buff[index];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v){
    delete[] buff;
    _capacity = v._capacity;
    current = v.current;
    buff = new T[_capacity];
    for(int i=0; i<current; i++){
        buff[i] = v.buff[i];
    }
    return *this;
}

template<typename T>
void Vector<T>::clear(){
    current = 0;
}
