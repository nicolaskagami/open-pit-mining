

#include "NHeap.h"


int main (int argc, char** argv)
{
    printf("N: %d\n",N);
    NHeap<char> h;
    h.insert('a',9);
    h.deleteMin();
    h.deleteMin();
    h.insert('b',7);
    h.insert('c',3);
    h.insert('d',5);
    h.print();
    h.insert('e',2);
    h.print();
    h.update('b',1);
    h.print();
    h.print();

}
