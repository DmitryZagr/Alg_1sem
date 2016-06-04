
//1_5. Вывести квадраты натуральных чисел от 1 до n,
//    используя только O(n) операций сложения и вычитания
//    (умножением пользоваться нельзя).
//n ≤ 1000.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE_OF_INTPUT_STR (512)
#define ERROR_MESSAGE ("[error]")

int read_number();
int* squared(int number);

int main(int argc, const char * argv[]) {
    int num = 0;
    if ((num = read_number()) == -1) {
//        fputs(ERROR_MESSAGE, stdout);
        return 0;
    }
    
    int* result_arr = squared(num);
    
    fflush(stdout);
    for (int i = 1; i < *(result_arr); i++) {
        fprintf(stdout, "%i ", *(result_arr + i));
    }
    
    fprintf(stdout, "%i", *(result_arr + *(result_arr)));
    free(result_arr);
    
    return 0;
}


int read_number() {
    
    char str[MAX_SIZE_OF_INTPUT_STR];
    int num = 0;
    
    memset(str, '\0', sizeof(char) * MAX_SIZE_OF_INTPUT_STR);
    fflush(stdin);
    fgets(str, sizeof(char) * MAX_SIZE_OF_INTPUT_STR, stdin);
    
    int i = 0;
    while (*(str + i)) {
        
        if (*(str + i) == '\n') {
            *(str + i) = '\0';
            break;
        }
        
        if (!isdigit( *(str + i))) {
            return -1;
        }
        i++;
    }
    
    num = atoi(str);

    return num <= 1000 && num > 0 ? num : -1;
}


int* squared(int number)  {
    
    int* result_arr = (int*)malloc(sizeof(int) * (number + 1));
    int prev_num = 0;
    
    if (result_arr == NULL) {
        return NULL;
    }
    
    *result_arr = number;
    *(result_arr + 1) = 1;
    
    for (int i = 2; i <= *result_arr; i++) {
        if (i == 2) {
            *(result_arr + i) = i + i;
            prev_num = *(result_arr + i);
            continue;
        }
    
        *(result_arr + i) = prev_num + (i - 1) + i;
        prev_num = *(result_arr + i );
//        printf("%i ", i*i);
    }
    
    return result_arr;
}


































