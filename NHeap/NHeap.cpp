
#include"NHeap.h"

template<typename T>
NHeap<T>::NHeap()
{
    //printf("Constructing Heap\n");
    heap = (struct node<T>*) malloc(INITIALSIZE*sizeof(struct node<T>));
    occupation=0;
    capacity = INITIALSIZE;
}
template<typename T>
NHeap<T>::~NHeap()
{
    //printf("Destroying Heap\n");
    free(heap);
}

template<typename T>
void NHeap<T>::print()
{
    printf("Heap (%d/%d):",occupation,capacity);
    unsigned i;
    for(i = 0; i < occupation; i++)
    {
        printf(" %d,",heap[i].key);
        std::cout << heap[i].element;
    }
    printf("\n");
}
template<typename T>
void NHeap<T>::insert(T t,unsigned key)
{
    //printf("Inserting %d\n",key);
    if(occupation<capacity)
    {
        heap[occupation].key = key;               
        heap[occupation].element = t;               
        heapifyup(occupation++);
    } 
    else 
    {
        if(resize(2*capacity) == 0)
        {
            heap[occupation].key = key;               
            heap[occupation].element = t;               
            heapifyup(occupation++);
        }
        else
        {
            printf("N-Heap memory allocation error\n");
        }
    }
}
template<typename T>
unsigned NHeap<T>::resize(unsigned newCapacity)
{
    //printf("Resize\n");
    heap = (struct node<T> *) realloc(heap,newCapacity*sizeof(struct node<T>));
    capacity = newCapacity;

    if(heap==NULL)
        return 1;

    return 0;
}
template<typename T>
void NHeap<T>::heapifyup(unsigned p)
{
    while((p > 0) && (p < occupation) && (heap[FATHER(p)].key > heap[p].key))
    {
        swap(heap[FATHER(p)],heap[p]);
        p = FATHER(p);
    }
}
template<typename T>
void NHeap<T>::heapifydown(unsigned p)
{
    unsigned smallestSon;
    unsigned smallestValue;
    unsigned i,j;
    while(FIRSTSON(p) < occupation)
    {
        for(j = FIRSTSON(p), i = 0, smallestSon = j, smallestValue = heap[j].key; (i < N) && ((i + j) < occupation); i++)
        {
            if(heap[(i + j)].key < smallestValue)
            {
                smallestSon = i + j;
                smallestValue = heap[(i + j)].key;
            }
        }
        if(smallestValue < heap[p].key)
        {
            swap(heap[p],heap[smallestSon]);
            p=smallestSon;
        }    
        else
        {
            return;
        }
    }
}
template<typename T>
T NHeap<T>::getMin()
{
    return heap[0].element;
}
template<typename T>
unsigned NHeap<T>::getMinValue()
{
    return heap[0].key;
}
template<typename T>
void NHeap<T>::deleteMin()
{
    if(occupation>0)
    {
        heap[0] = heap[--occupation];
        if((INITIALSIZE < occupation) && (occupation < capacity/2))
            resize(capacity/2);
        heapifydown(0);
    }
}
template<typename T>
void NHeap<T>::update(T t,unsigned newKey)//newKey < key!
{
    for(unsigned i = 0; i < occupation; i++)
    {
        if(heap[i].element == t)
        {
            heap[i].key = newKey;
            heapifyup(i);
            break;
        }
    }
}
template<typename T>
void swap(struct node<T> &a, struct node<T> &b)
{
    struct node<T> c = a;
    a = b;
    b = c;
}


template class NHeap<char>;
template class NHeap<unsigned>;
