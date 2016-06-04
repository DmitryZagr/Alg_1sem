//
//  main.cpp
//  2_4
//
/*
Дан массив натуральных чисел A[0..n), n не превосходит 10^8.
Так же задан размер некотрого окна (последовательно расположенных элементов массива) 
 в этом массиве k, k<=n.
Требуется для каждого положения окна (от 0 и до n­k) вывести значение максимума в окне. 
 Скорость работы O(n log n)
Формат входных данных. Вначале вводится n ­ количество элементов массива.
Затем вводится n строк со значением каждого элемента. Затем вводится k ­ размер окна.
Формат выходных данных. 
 Разделенные пробелом значения максимумов для каждого положения окна.
*/
//  Created by Дмитрий  Загребаев on 20.04.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

template<class T> struct elemHeap {w
    T elem;
    int32_t index;
};

bool operator > (const struct elemHeap<int32_t>& left, const struct elemHeap<int32_t>& right)
{
    return left.elem > right.elem;
}

bool operator >= (const struct elemHeap<int32_t>& left, const struct elemHeap<int32_t>& right)
{
    return left.elem >= right.elem;
}


template <class T = int32_t>
class Heap {
    
private:
    int32_t size;
    int32_t heapSize;
    T *heap;
    
public:
    inline Heap(int32_t size) {
        this->size = size;
        this->heap = new T[size];
        this->heapSize = 0;
    }
    
    inline ~Heap() { if(size > 0) delete [] this->heap;}
    
public:
    T getMax() {
        T result = heap[0];
        if(heapSize > 1) {
            heap[0] = heap[heapSize - 1];
            this->heapSize--;
            if(this->heapSize > 0) {
                siftDown(0);
            }
        }
        return result;
    }
    
private:
    void siftDown(int32_t i)
    {
        int32_t left  = 0;
        int32_t right = 0;
        int32_t j = 0;
        
        while(2 * i + 1 < this->heapSize) {
            left = 2 * i + 1 ;            // left — левый сын
            right = 2 * i + 2;
            j = left;
            if(right < this->heapSize && this->heap[right] > this->heap[left]) {
                j = right;
            }
            if(this->heap[i] >= this->heap[j]) break;
            std::swap(this->heap[i], this->heap[j]);
            i = j;
        }
        
    }
    
    void siftUp(int32_t i) {
        while (this->heap[i] > this->heap[(i - 1) / 2]) { // <
            std::swap(this->heap[i], this->heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

public:
    void add( T element)
    {
        this->heapSize++;
        this->heap[this->heapSize - 1] = element;
        if(this->heapSize > 1)
            this->siftUp(this->heapSize - 1);
    }
    
    inline bool isEmpty() {return (this->heapSize == 0 ? true : false);}
    inline T  readMax() const {return heap[0];}
    
};

int main(int argc, const char * argv[]) {
    
    int32_t arrSize = 0;
    std::cin >> arrSize;
    assert(arrSize > 0);
    
    struct elemHeap<int32_t> *elemH = new struct elemHeap<int32_t>[arrSize];
    Heap<struct elemHeap<int32_t> > *heap = new Heap<struct elemHeap<int32_t> >(arrSize);
    
    for (int32_t i = 0; i < arrSize; i++) {
        cin >> elemH[i].elem;
        elemH[i].index = i;
    }
    int32_t window = 0;
    std::cin >> window;
    
    for(int32_t i = 0; i < window; i++) {
        heap->add(elemH[i]);
    }
    
    int32_t numberRead = 0;
    numberRead = window;
    
    struct elemHeap<int32_t> elemBuf;
    
    while (numberRead <= arrSize) {
        elemBuf = heap->readMax();
        if (elemBuf.index >= numberRead - window && elemBuf.index <= numberRead) {
            std::cout << elemBuf.elem << " ";
            heap->add(elemH[numberRead]);
            numberRead++;
        } else {
            heap->getMax();
        }
    }
    
    delete [] elemH;
    delete heap;
    
    return 0;
}
