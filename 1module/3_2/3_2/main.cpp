

// Дан массив целых чисел А[0..n­1].
//Известно, что на интервале [0, m] значения массива строго возрастают,
//а на интервале [m, n­1] строго убывают. Найти m за O(log m).
//n ≤ 10000.

#include <iostream>
#include <stdio.h>
#include "math.h"

void read_arr(size_t *size, long** arr);

long find_number(const size_t* arr_size, const long* arr);

long binary_search(size_t r, size_t l, const long* arr, char flag);

int main(int argc, const char * argv[]) {
    
    size_t arr_size = 0;
    long *arr = NULL;
    
    read_arr(&arr_size, &arr);
    
    std::cout <<  find_number(&arr_size, arr);
    
    free(arr);
    
    return 0;
}

/*------------------------------------------------------------------------------------------------*/

void read_arr(size_t *size, long** arr) {
    
    fflush(stdin);
    
    std::cin >> *size;
    
    *arr = (long*)malloc(sizeof(long) * *size);
    
    for (int i = 0; i < *size; i++) {
        std::cin >> (*arr)[i];
    }
    
}

/*------------------------------------------------------------------------------------------------*/

long find_number(const size_t* arr_size, const long* arr) {
    size_t left  = 1;
    size_t right = 2;
    char flag    = 0;
    long answer  = 0;
    
    while (arr[right] > arr[right - 1]) {
        left  = right;
        right *= 2;
        if (right > *arr_size) {flag = 1; right = *(arr_size) - 1; break;}
    }
    
    answer = binary_search(left, right, arr, flag);
    
    return answer;
}

/*------------------------------------------------------------------------------------------------*/

long binary_search(size_t left, size_t right, const long* arr, char flag) {
    size_t mid = 0;

    while (left <= right) {
        
        if((left - 1) == 0 && arr[left - 1] > arr[left]) {
            return ( left - 1);
        }
        
        if (flag == 1) {
            if (arr[right] > arr[right - 1]) return right;
        }
        
//        mid = left + (right - left) / 2;
        mid = (left + right) / 2;
        
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
            return mid;
            
        } else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1] )
            right = mid - 1;
        
        else
            left = mid + 1;
        
    }
    
    return -1;
}

/*------------------------------------------------------------------------------------------------*/














