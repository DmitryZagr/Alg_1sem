//2_3. Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
//Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
//n, m ≤ 100000.
//

#include <iostream>
#include <cstring>
#include <stdlib.h>

size_t calculate(int* arrA, int* arrB, size_t sizeA, size_t sizeB, size_t k);
void readInputData(int** arrA, int** arrB, size_t *sizeA, size_t *sizeB, size_t *k);

int main(int argc, const char * argv[]) {
    
    size_t sizeA = 0, sizeB = 0, k = 0;
    int* arrA;
    int* arrB;
    
    readInputData(&arrA, &arrB, &sizeA, &sizeB, &k);
    
    if (sizeA >= sizeB) {
        std::cout << calculate(arrA, arrB, sizeA, sizeB, k);
    } else {
        std::cout << calculate(arrB, arrA, sizeB, sizeA, k);
    }
    
    free(arrA);
    free(arrB);
    
    return 0;
}


void readInputData(int** arrA, int** arrB, size_t *sizeA, size_t *sizeB, size_t *k) {
    
    std::cin >> *sizeA;
    
    *arrA = (int*)malloc(sizeof(int) * *sizeA);
    
    for (int i = 0; i < *sizeA; i++) {
        std::cin >> *(*arrA + i);
    }
    
    std::cin >> *sizeB;
    
    *arrB = (int*)malloc(sizeof(int) * *sizeB);
    
    for (int i = 0; i < *sizeB; i++) {
        std::cin >> *(*arrB + i);
    }
    
    std::cin >> *k;
}


size_t calculate(int* arrA, int* arrB, size_t sizeA, size_t sizeB, size_t k) {
    
    size_t result = 0;
    
    size_t iterB = 0;
    
    for (long iterA = sizeA - 1; iterA >= 0; iterA--) {
        
        if (arrA[iterA] + arrB[iterB] == k) {
            result++;
            iterB++;
        } else {
            if (arrA[iterA] + arrB[iterB] < k) {
                if (iterB < sizeB) {
                    iterB++;
                }
            }
        }
    }
    
    if (iterB < sizeB ) {
        for ( ; iterB < sizeB; iterB++) {
            if (arrB[iterB] + arrA[0] == k) {
                result++;
            }
        }
    }
    
    return result;
}





























