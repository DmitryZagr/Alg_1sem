//4_2. Реализовать дек с динамическим зацикленным буфером.
//  main.cpp
//  4_2
//
//  Created by Дмитрий  Загребаев on 13.03.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>
#include <string.h>

#define YES ("YES")
#define NO ("NO")
#define INIT_SIZE (8)
#define SCALE (2)

class Deque {
    
private:
    int *arrNumbers;
    int countOfelems;
    int arrSize;
    int firstIndex;
    int lastIndex;
    
public:
    Deque();
    ~Deque();
    
public:
    Deque *pushBack(int num);
    int popBack();
    
    Deque *pushFront(int num);
    int popFront();
    
public:
    inline bool isEmpty();
    
private:
    Deque *Resize();
};

bool getStatus(Deque *deque);

int main(int argc, const char * argv[]) {
    
    Deque *deque = new Deque();
    
    if (getStatus(deque)) {
        std::cout << YES;
    } else std:: cout << NO;
    
    delete deque;
    
    return 0;
}

/*------------------------------------------------------------------------------------------------*/

Deque::Deque() {
    this->arrNumbers = (int*)malloc(sizeof(int) * INIT_SIZE);
    memset(this->arrNumbers, 0, sizeof(int) * INIT_SIZE);
    this->arrSize      = INIT_SIZE;
    this->countOfelems = 0;
    this->firstIndex   = 0;
    this->lastIndex    = 0;
}

/*------------------------------------------------------------------------------------------------*/

Deque::~Deque() {
    free(this->arrNumbers);
}

/*------------------------------------------------------------------------------------------------*/

Deque* Deque::Resize() {
    
    int *tmpBuffer = (int*)malloc(sizeof(int) * this->arrSize * SCALE);
    
    int j = 0;
    
    for (int i = this->firstIndex; i < this->arrSize; i++) {
        tmpBuffer[j] = *(this->arrNumbers + i);
        j++;
    }
    
    for (int i = 0; i < this->lastIndex; i++) {
        tmpBuffer[j] = *(this->arrNumbers + i);
        j++;
    }
    
    free(this->arrNumbers);
    this->arrNumbers = tmpBuffer;
    this->arrSize    *= SCALE;
    this->firstIndex = 0;
    this->lastIndex  = this->countOfelems + 1;
    
    return this;
}


/*------------------------------------------------------------------------------------------------*/

inline bool Deque::isEmpty() {
    return countOfelems == 0 ? true : false;
}

/*------------------------------------------------------------------------------------------------*/

Deque* Deque::pushFront(int num) {
    
//    std::cout << "pushFront\n";
    
    this->firstIndex--;
    
    if (this->firstIndex < 0) this->firstIndex = this->arrSize - 1;
    
    if (this->firstIndex == this->lastIndex) this->Resize();
    
    *(this->arrNumbers + this->firstIndex) = num;
    
    this->countOfelems++;
    
//    std::cout << "pushFront " << firstIndex << " " << lastIndex << " " <<countOfelems << "\n";
    
    return this;
}

/*------------------------------------------------------------------------------------------------*/

int Deque::popFront() {
    
//    std::cout << "popFront\n";
    
    if (this->isEmpty()) {
        return -1;
    }

    int result   = 0;
    
    result = *(this->arrNumbers + this->firstIndex++);
    
    if (this->firstIndex == this->arrSize) {
        this->firstIndex = 0;
    }
    
    this->countOfelems--;
    
//    std::cout << "popFront " << firstIndex << " " << lastIndex << " " <<countOfelems << "\n";

    return result;
}

/*------------------------------------------------------------------------------------------------*/

Deque* Deque::pushBack(int num) {
    
//    std::cout << "pushBack\n";
    
    *(this->arrNumbers + this->lastIndex++) = num;
    
    if (this->lastIndex == this->arrSize) {
        this->lastIndex = 0;
    }
    
    if (this->lastIndex == this->firstIndex) {
        this->Resize();
    }
    
    this->countOfelems++;
    
//    std::cout << "pushBack " << firstIndex << " " << lastIndex << " " <<countOfelems << "\n";

    return this;
}

int Deque::popBack() {
    
//    std::cout << "popBack\n";
    
    if (this->isEmpty()) {
        return -1;
    }
    
    this->lastIndex--;
    
    if (this->lastIndex < 0) {
        this->lastIndex = this->arrSize - 1;
    }
    
    int result = *(this->arrNumbers + this->lastIndex);
    
    this->countOfelems--;
    
//    std::cout << "popBack " << firstIndex << " " << lastIndex << " " <<countOfelems << "\n";

    return result;
}

/*------------------------------------------------------------------------------------------------*/

bool getStatus( Deque *deque) {
    size_t countOfComands = 0;
    int exp = 0;
    int comand = 0;
    
    std::cin >> countOfComands;
    
    for (size_t i = 0; i < countOfComands; i++) {
        std::cin >> comand >> exp;
        switch (comand) {
            case 1:
                deque->Deque::pushFront(exp);
                break;
                
            case 2:
                if(deque->Deque::popFront() != exp)
                    return false;
                break;
                
            case 3:
                deque->pushBack(exp);
                break;
                
            case 4:
                if (deque->popBack() != exp)
                    return false;
                break;
                
            default:
                break;
        }
    }
    
    return true;
}

/*------------------------------------------------------------------------------------------------*/



























































