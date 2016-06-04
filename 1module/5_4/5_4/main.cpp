//
//Дано выражение в инфиксной записи.
//Вычислить его, используя перевод выражения в постфиксную запись.
//Выражение не содержит отрицительных чисел.
//Количество операций ≤ 100.
//Формат входных данных. С трока, состоящая их символов “0123456789­+*/()”
//Гарантируется, что входное выражение корректно, нет деления на 0, вычислимо в целых числах.
//Деление целочисленное.
//Формат выходных данных.
//Значение выражения.
//  main.cpp
//  5_4
//
//  Created by Дмитрий  Загребаев on 07.03.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE (2048)
#define CHAR_STACK_MAX_SIZE (1024)

class Calculator {
    
private:
    char* input_str ;
    char* polish_str;
    int answer;
    
public:
    char* reversePolistNotation();
    int calculate(const char* reverse_polish_notation);
    
    
public:
    Calculator(const char* input_str);
    ~Calculator();
    
private:
    char* parsePolishStr();
    int calculate_one_operation(int left_operad, int right_operand, char operation);
    bool isOperation(const char ch);
    char getOperationPriority(const char);
    
};

class StackChar {
    
private:
    int count_of_elems;
    int *elems;
    
public:
    //Добавить (положить) в конец стека новый элемент
    void pop(const int ch);
    //Извлечь из стека элемент
    int push();
    bool isEmpty();
    
public:
    StackChar();
    ~StackChar();
};


/*------------------------------------------------------------------------------------------------*/

char* read_input_str(char** str);

/*------------------------------------------------------------------------------------------------*/

int main(int argc, const char * argv[]) {
    
    char* input_str = NULL;
    read_input_str(&input_str);
    //
    Calculator* calc = new Calculator(input_str);
    
    std::cout << calc->calculate(calc->reversePolistNotation());

    free(input_str);
    
    delete calc;
    
    return 0;
}

/*------------------------------------------------------------------------------------------------*/

char* read_input_str(char** str) {
    
    fflush(stdin);
    fflush(stdout);
    
    if (*str != NULL) {
        free(*str);
    }
    
    *str = (char*)malloc(sizeof(char) * STR_SIZE);
    memset(*str, '\0', sizeof(char) * STR_SIZE);
    
    std::cin >> *str;
    
    return *str;
}

/*------------------------------------------------------------------------------------------------*/

Calculator::Calculator(const char* input_str) {
    this->input_str = (char*)malloc(sizeof(char) * strlen(input_str) + 1);
    strcpy(this->input_str, input_str);
    this->polish_str = (char*)malloc(sizeof(char) * STR_SIZE);
    memset(this->polish_str, '\0', sizeof(char) * STR_SIZE);
}

/*------------------------------------------------------------------------------------------------*/

Calculator::~Calculator() {
    free(this->input_str);
    free(this->polish_str);
}

/*------------------------------------------------------------------------------------------------*/

bool Calculator::isOperation(const char ch) {
    
    switch (ch) {
            
        case '-':
            return true;
            
        case '+':
            return true;
            
        case '*':
            return true;
            
        case '/':
            return true;
            
        default:
            return false;
    }
}

/*------------------------------------------------------------------------------------------------*/

char Calculator::getOperationPriority(const char operation) {
    
    switch (operation) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/' :
            return 3;
            //если символ не является ни одной из приведенных выше операций
        default:
            return -1;
    }
    
}

/*------------------------------------------------------------------------------------------------*/

char* Calculator::reversePolistNotation() {
    
    StackChar* st = new StackChar();
    
    int i = 0, iter_of_polish_str = 0;
    char stack_char = '\0';
    
    while (*(this->input_str + i) != '\0') {
        
        if (isdigit(*(this->input_str + i)) ) {
            *(this->polish_str + iter_of_polish_str) = *(this->input_str + i);
            iter_of_polish_str++;
            i++;
            continue;
        } else {
            *(this->polish_str + iter_of_polish_str) = ' ';
            iter_of_polish_str++;
        }
        
        
        if (this->isOperation(*(this->input_str + i)) ||
            *(this->input_str + i) == '(' || *(this->input_str + i) == ')') {
            
            //если стек пуст, то опеpация из входной стpоки пеpеписывается в стек;
            if (st->isEmpty()) {
                st->pop(*(this->input_str + i));
                i++;
                continue;
            }
            //            опеpация выталкивает из стека все опеpации с большим или
            //            pавным пpиоpитетом в выходную стpоку;
            else {
                
                while (!st->isEmpty()) {
                    
                    stack_char = st->push();
                    
                    if ((this->getOperationPriority(*(input_str + i)) <=
                         this->getOperationPriority(stack_char)) &&
                        this->isOperation(stack_char) &&
                        this->isOperation(*(this->input_str + i))) {
                        *(this->polish_str + iter_of_polish_str) = stack_char;
                        iter_of_polish_str++;
                    } else {
                        //                        если условие не выполнилось,
                        //                        то возвращаем символ в стек и выходим из цикла
                        st->pop(stack_char);
                        break;
                    }
                }
                if (*(this->input_str + i) != ')') {
                    st->pop(*(this->input_str + i));
                    i++;
                    continue;
                }
                
            }
            
            //            закpывающая кpуглая скобка выталкивает все опеpации из стека
            //            до ближайшей откpывающей скобки,
            //            сами скобки в выходную стpоку не пеpеписываются,
            //            а уничтожают дpуг дpуга
            
            if (*(this->input_str + i) == ')') {
                while (1) {
                    
                    stack_char = st->push();
                    
                    if (stack_char == '(') {
                        break;
                    }
                    *(this->polish_str + iter_of_polish_str) = stack_char;
                    iter_of_polish_str++;
                }
            }
        }
        
        i++;
    }
    
    while (!st->isEmpty()) {
        *(this->polish_str + iter_of_polish_str) = st->push();
        iter_of_polish_str++;
    }
    
    *(this->polish_str + iter_of_polish_str) = '\0';
    
    delete st;
    
    return this->polish_str;
    
}

/*------------------------------------------------------------------------------------------------*/

int Calculator::calculate_one_operation(int left_operad, int right_operand, char operation) {
    switch (operation) {
        case '+':
            return left_operad + right_operand;
            
        case '-':
            return left_operad - right_operand;
            
        case '/' :
            return left_operad / right_operand;
            
        case '*':
            return left_operad * right_operand;
            
        default:
            return  0;
    }
    
}

/*------------------------------------------------------------------------------------------------*/

int Calculator::calculate(const char* reverse_polish_notation) {
    
    char buf[STR_SIZE];
    
    memset(buf, '\0', sizeof(char) * STR_SIZE);
    
    StackChar *st = new StackChar();
    
    char operation = 0;
    int i = 0;
    int iter_of_buf_str = 0;
    int result_num = 0;
    int buf_res = 0;
    int left_operand = 0;
    int right_operand = 0;
    
    while (*(reverse_polish_notation + i ) != '\0') {
        if (strlen(buf) != 0 && (*(reverse_polish_notation + i) == ' ' ||
                                 this->isOperation(*(reverse_polish_notation + i))) ) {
            buf[iter_of_buf_str] = '\0';
            st->pop(atoi(buf));
            iter_of_buf_str = 0;
            buf[0] = '\0';
        }
        
        if (isdigit(*(reverse_polish_notation + i))) {
            buf[iter_of_buf_str] = *(reverse_polish_notation + i);
            iter_of_buf_str++;
        }
        
        
        if (this->isOperation(*(reverse_polish_notation + i))) {
            right_operand = st->push();
            left_operand = st->push();
            operation = *(reverse_polish_notation + i);
            buf_res = this->calculate_one_operation(left_operand, right_operand, operation);
            st->pop(buf_res);
            i++;
            continue;
        }
        
        i++;
    }
    
    result_num = buf_res;
    
    delete st;
    
    return result_num;
    
}

/*------------------------------------------------------------------------------------------------*/

StackChar::StackChar() {
    this->count_of_elems = 0;
    this->elems = (int*)malloc(sizeof(int) * CHAR_STACK_MAX_SIZE);
    memset(this->elems, '\0', sizeof(int) * CHAR_STACK_MAX_SIZE);
}

/*------------------------------------------------------------------------------------------------*/

StackChar::~StackChar() {
    free(this->elems);
}

/*------------------------------------------------------------------------------------------------*/

void StackChar::pop(const int ch) {
    
    *(this->elems + this->count_of_elems) = ch;
    this->count_of_elems++;
    
}

/*------------------------------------------------------------------------------------------------*/

int StackChar::push() {
    if((this->count_of_elems) < 0)
        return -1;
    this->count_of_elems--;
    return *(this->elems + this->count_of_elems);
}


/*------------------------------------------------------------------------------------------------*/

bool StackChar::isEmpty() {
    return this->count_of_elems == 0 ? true : false;
}

/*------------------------------------------------------------------------------------------------*/



