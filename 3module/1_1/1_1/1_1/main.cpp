//
//  main.cpp
//  1_1
//

/*
Задача 1. Хеш-таблица (6 баллов)
Реализуйте структуру данных типа “множество строк” на основе динамической
 хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв. 
Начальный размер таблицы должен быть равным 8-ми.
Перехеширование выполняйте при добавлении элементов в случае, 
 когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, 
 удаления строки из множества и проверки принадлежности данной строки множеству.
1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
1_2. Для разрешения коллизий используйте двойное хеширование.
Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. 
Запись операции состоит из типа операции и следующей за ним через пробел строки,
 над которой проводится операция.
Тип операции  – один из трех символов:
+  означает добавление данной строки в множество;
-  означает удаление  строки из множества;
?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL,
 в зависимости от того, встречается ли данное слово в нашем множестве.
stdin
stdout
+ hello
+ bye
? bye
+ bye
- bye
? bye
? hello
OK
OK
OK
FAIL
OK
FAIL
OK

*/
//  Created by Дмитрий  Загребаев on 20.05.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//


#include<iostream>
#include<string>
#include<vector>
#include<string.h>

#define A ( 997 )
#define DELETED ( -1 )
#define NOT_INDEX ( -1 )

using namespace std;

const int DefaultTableSize = 8;
const int GrowFactor = 8;

int Hash(const string& data, int tableSize) {
    
    int hash = 0;
    
    for(int i = 0; i < data.size(); i++) {
        hash = (hash * A + data[i]) % tableSize;
    }
    
    return hash;
}

class HashTable {
    
private:
    string* table;
//    int* keyIndexArr;// запоминаем индексы ключей для перехэширования
    unsigned int keysCount;
    unsigned int tableSize;
    string delFlag;
    string nullFlag;
    
public:
    HashTable();
    ~HashTable();
    
public:
    bool has(const string &data) const;
    bool add(const string &data);
    
    bool del(const string& data);
    
private:
    void resize();
};




HashTable::HashTable() {
    delFlag = "Deleted_DELETED";
    nullFlag = "NULL_NULL";
    table = new string[DefaultTableSize];
    for(int i = 0; i < DefaultTableSize; i++)
        table[i] = nullFlag;
    
    //        keyIndexArr = new int[DefaultTableSize];
    //        memset(keyIndexArr, NOT_INDEX, sizeof(int) * DefaultTableSize);
    keysCount = 0;
    tableSize = DefaultTableSize;
    
}

HashTable::~HashTable() {
    delete[] table;
    //        delete[] keyIndexArr;
}


bool HashTable::has(const string &data) const {
    
    int hash = Hash(data, this->tableSize);
    
    for(int i = 0; i < tableSize; i++) {
        
        hash = hash + i % tableSize;
        
        if(hash >= tableSize)
            hash %= tableSize;
        
        if(table[hash] == nullFlag) return false;
        if(table[hash] == data) {
            return true;
        }
    }
    return false;
}

bool HashTable::add(const string &data) {
    
    resize();
    
    int hash = Hash(data, this->tableSize);
    
    
    for(int i = 0; i < tableSize; i++) {
        
        if(table[hash] == delFlag) {
            if(i++ > tableSize)
                break;
        }
        
        hash = hash + i % tableSize;
        
        if(hash >= tableSize)
            hash %= tableSize;
        
        if(table[hash] == data)
            return false;
        
        if(table[hash] == nullFlag /*|| table[hash] == delFlag*/) {
            table[hash] = data;
            keysCount++;
            //                keyIndexArr[keysCount] = hash;
            return true;
        }
        
    }
    
    return false;
}

bool HashTable::del(const string& data) {
    
    int hash = Hash(data, this->tableSize);
    
    for(int i = 0; i < tableSize; i++) {
        
        hash = hash + i % tableSize;
        
        if(hash >= tableSize)
            hash %= tableSize;
        
        if(table[hash] == nullFlag  || table[hash] == delFlag)
            return false;
        
        if(table[hash] == data) {
            table[hash] = delFlag;
            return true;
        }
    }
    
    return false;
}


void HashTable::resize() {
    
    if(( (double)(keysCount + 1) / tableSize ) >= 3.0 / 4.0  ) {
        
        unsigned int newTableSize = tableSize * GrowFactor;
        string* newTable = new string[newTableSize];
        for(unsigned int i = 0; i < newTableSize; i++)
            newTable[i] = nullFlag;
        
        int hash = 0;
        
        for(unsigned int i = 0; i < tableSize; i++) {
            
            if(table[i] != nullFlag ) {
                
                if( table[i] == delFlag) {
                    if(i++ > tableSize)
                        break;
                }
                
                hash = Hash(table[i], newTableSize);
                
                for(unsigned int j = 0; j < newTableSize; j++ ) {
                    hash = hash + j % newTableSize;
                    if(hash >= newTableSize)
                        hash %= newTableSize;
                    
                    if(newTable[hash] == nullFlag ) {
                        newTable[hash] = table[i];
                        break;
                    }
                }
            }
        }
        
        delete [] table;
        table = newTable;
        tableSize = newTableSize;
    }
}





int main()
{
    char operation;
    string word;
    
    HashTable *ht =new HashTable();
    
    while (true) {
        
        std::cin >> operation >> word;
        if (std::cin.fail()) {
            break;
        } else {
            switch (operation) {
                case '+':
                    cout << (ht->add(word) ? "OK" : "FAIL") << endl;
                    break;
                
                case '-':
                    cout << (ht->del(word) ? "OK" : "FAIL") << endl;
                    break;
                    
                case '?':
                    cout << (ht->has(word) ? "OK" : "FAIL") << endl;
                    break;
    
                default:
                    break;
            }
        }
    }
    
    delete ht;

    
    return 0;
}

