//
//  main.cpp
//  3_3
//
//3_3. Закраска прямой 1.
//На числовой прямой окрасили  N  отрезков.
//Известны координаты левого и правого концов каждого отрезка (Li  и Ri).
//Найти длину окрашенной части числовой прямой.
//  Created by Дмитрий  Загребаев on 22.04.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>

using namespace std;


template<class T> struct elemHeap {
    T left;
    T right;
    int32_t index;
};

bool operator < (const struct elemHeap<int32_t>& left, const struct elemHeap<int32_t>& right)
{
    return left.left < right.left;
}

bool operator <= (const struct elemHeap<int32_t>& left, const struct elemHeap<int32_t>& right)
{
    return left.left <= right.left;
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
    
    inline ~Heap() { if(size > 0) delete this->heap;}
    
public:
    T getMax() {
        T result = heap[0];
            heap[0] = heap[heapSize - 1];
            this->heapSize--;
            if(this->heapSize > 0) {
                siftDown(0);
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
            if(right < this->heapSize && this->heap[right] < this->heap[left]) {
                j = right;
            }
            if(this->heap[i] <= this->heap[j]) break;
            std::swap(this->heap[i], this->heap[j]);
            i = j;
        }
        
    }
    
    void siftUp(int32_t i) {
        while (this->heap[i] < this->heap[(i - 1) / 2]) { // <
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

    int32_t arraySize = 0;
    
    cin >> arraySize;
    
    Heap< struct elemHeap<int32_t> > *heap = new Heap< struct elemHeap<int32_t> >(arraySize);
    
    struct elemHeap<int32_t> bufRead;
    
    for(int32_t i = 0; i < arraySize; i++) {
        cin >> bufRead.left;
        cin >> bufRead.right;
        heap->add(bufRead);
    }
    
    int32_t result        = 0;
    int32_t prevResult    = 0;
    struct elemHeap<int32_t> buffer;
    int32_t i = 0;
    int32_t flag = 0;
    
    while(!heap->isEmpty()) {
        flag = 0;
        bufRead = heap->getMax();
        if(i == 0) {
            buffer.left = bufRead.left;
            buffer.right = bufRead.right;
            result = bufRead.right - bufRead.left;
            prevResult = result;
        } else {
            
            if(bufRead.right > buffer.right && bufRead.left <= buffer.right) {
                buffer.right = bufRead.right;
                result -= prevResult;
                prevResult = buffer.right - buffer.left;
                result += prevResult;
                i++;
                continue;
            }
            
            if(bufRead.left > buffer.right) {
                buffer.left = bufRead.left;
                buffer.right = bufRead.right;
                prevResult = buffer.right - buffer.left;
                result += prevResult;
                continue;
            }
        }
        
        i++;
    }
    
    cout << result;
    
    delete heap;
    
    return 0;
}































