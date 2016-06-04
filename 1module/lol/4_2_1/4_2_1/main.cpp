//
//  main.cpp
//  4_2_1
//
//  Created by Дмитрий  Загребаев on 25.03.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>
using namespace std;

class Deque {
    
private:
    int* buffer;
    int bufferSize;
    int head;
    int tail;
    
public:
    Deque(int _bufferSize);
    ~Deque();
    void PushFront(int a);
    int PopFront();
    void PushBack(int a);
    int PopBack();
    void Resize();
    bool IsEmpty();

};


//3
//1 44
//3 50
//2 44


Deque::Deque(int _bufferSize) :
bufferSize(_bufferSize),
tail(0),
head(0)
{
    buffer = new int[bufferSize];
}

Deque::~Deque() {
    delete[] buffer;
}

void Deque::PushBack(int value) {
    buffer[tail] = value;
    if (++tail == bufferSize)
        tail = 0;
    if (head == tail) {
        Resize();
    }
}

int Deque::PopBack() {
    if (--tail < 0)
        tail = bufferSize - 1;
    int ret = buffer[tail];
    return ret;
}

void Deque::PushFront(int value) {
    if (--head < 0)
        head = bufferSize - 1;
    buffer[head] = value;
    if (head == tail)
        Resize();
}

int Deque::PopFront() {
    int h1 = head;
    if (++head == bufferSize)
        head = 0;
    return buffer[h1];
}

bool Deque::IsEmpty() {
    return head == tail;
}

void Deque::Resize() {
    int* temp_buffer = new int[bufferSize * 2];
    int j = 0;
    for (int i = head; i < bufferSize; i++) {
        temp_buffer[j] = buffer[i];
        j++;
    }
    for (int i = 0; i < tail; i++) {
        temp_buffer[j] = buffer[i];
        j++;
    }
    delete [] buffer;
    buffer = temp_buffer;
    bufferSize *= 2;
    head = 0;
    tail = bufferSize / 2;
}



int main() {
    int countOfElements, numberOfInstruction, element, size_deque = 1;
    bool correct = true;
    std::cin >> countOfElements;
    Deque A = Deque(size_deque);
    for (int i = 0; i < countOfElements; i++) {
        std::cin >> numberOfInstruction;
        std::cin >> element;
        switch (numberOfInstruction) {
            case 1:
            {
                A.PushFront(element);
                break;
            }
            case 2:
            {
                if (!A.IsEmpty()) {
                    if (A.PopFront() != element)
                        correct = false;
                }
                else if (element != -1)
                    correct = false;
                break;
            }
            case 3:
            {
                A.PushBack(element);
                break;
            }
            case 4:
            {
                if (!A.IsEmpty()) {
                    if (A.PopBack() != element)
                        correct = false;
                }
                else if (element != -1)
                    correct = false;
                break;
            }
            default:
                cout << "-1" << endl;
        }
    }
    if (correct)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    
}
