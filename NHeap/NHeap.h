
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#ifndef N
#define N 2
#endif
//N is to be defined during compilation: -DN=n
#define FATHER(x) (x-1)/N
#define FIRSTSON(x) (x*N)+1
#define INITIALSIZE 32 

template <typename T>
struct node
{
    unsigned key;
    T element;
};

template <typename T>
class NHeap
{
    public:
       struct node<T> * heap;
       unsigned occupation;
       unsigned capacity;

       NHeap();
       ~NHeap();
       void insert(T t,unsigned key);
       T getMin();
       unsigned getMinValue();
       void deleteMin();
       void update(T t,unsigned newKey);
       void print();
    private:
       unsigned resize(unsigned newCapacity);
       void heapifyup(unsigned p);
       void heapifydown(unsigned p);

};
