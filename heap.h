#ifndef HEAP_H
#define	HEAP_H

#include <iostream>

using namespace std;

template <class T>
class Heap {
private:
    T *data;
    Heap *parent;
};

#endif	/* HEAP_H */

