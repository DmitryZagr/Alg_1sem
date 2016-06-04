//
//  main.cpp
//  Haffman
/*
Задача 5. Алгоритм сжатия данных Хаффмана
(6 баллов и более)
Написать реализацию функций:
void compress_string(const std::string &source, std::string &compressed);
void decompress_string(const std::string &compressed, std::string &result);

Обвязка из main проверяет контрольную сумму и совпадение исходных данных с результатом сжатия-расжатия.
 Если хотя бы на одном тесте результат не совпадает с исходником, задача не проходит.
 В качестве тестовых данных используются 50 случайных листингов кода из 33 контеста.
 Решения, прошедшие все тесты попадают в лидерборд.
http://tp-test1.tech-mail.ru:82/huffman_2016_spring/
Данные на доске почета обновляются раз в 30 секунд.

Тестирующая программа выводит размер сжатого файла.
В лидерборде решения ранжируются по возрастанию суммарного размера сжатых файлов.

Для получения 6 баллов требуется средняя степень сжатия Kc <= 0.5. 
Лучшие 3 решения с Kc <= 0.5 из каждой группы оцениваются в 15 баллов.

Пример минимального решения:
void compress_string(const std::string &source, std::string &compressed) {
    compressed = source;
}
void decompress_string(const std::string &compressed, std::string &result) {
    result = compressed;
}
*/

//
//  Created by Дмитрий  Загребаев on 14.05.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <map>
#include <list>
#include <vector>

using namespace std;


struct Tree {
    Tree *left;
    Tree *right;
    Tree *root;
    char ch;
    double freq;
    
public:
    Tree() {
        this->left = this->right = nullptr;
        this->ch = '\0';
    }
    
    Tree(char ch, double freq, Tree *left, Tree *right) {
        this->ch    = ch;
        this->freq  = freq;
        this->left  = left;
        this->right = right;
    }
    
    inline bool isLeaf() { return (left == nullptr) && (right == nullptr); }
    
    inline double getFreq() const {return this->freq;}
    
};


//template<class T>
class Haffman {
    
private:
    const string *source_str;
    string *compressed_str;
    string *decompressed_str;
    
    map<char, double> map_char_freq;
    
    Tree *tree;
    
public:
    Haffman();
    ~Haffman();
    bool operator()(const Tree a, const Tree b)
    {
        return a.getFreq() < b.getFreq();
    }
    
public:
    void compress_string(const std::string &source, std::string &compressed);
    void decompress_string(const std::string &compressed, std::string &result);
    void set_source_str();
    
    std::string *get_source_str() const;
    
private:
    void fill_map_char_freq();
    void buildTree();
    void buildCode(Tree *&root);
};

Haffman::Haffman() {
}

Haffman::~Haffman() {
//    this->source_str->clear();
//    this->compressed_str->clear();
//    this->decompressed_str->clear();
    this->map_char_freq.clear();
}

void Haffman::buildCode(Tree *& root) {
    if(root != nullptr) {
        buildCode(root->left);
        std::cout << root->ch << " :  " << root->freq << endl ;
        buildCode(root->right);
    }
}

void Haffman::buildTree() {
    Tree *node   = nullptr;
    Tree *parent = nullptr;
    
//    list<Tree> nodeList;
    
    vector<Tree> nodeVect;
    
    
    struct {
        bool operator()(const Tree a, const Tree b)
        {
            return a.getFreq() < b.getFreq();
        }
    } customLess;
    
//    sort(nodeVect.begin(), nodeVect.end(), customLess);
    
    for(auto itMap = map_char_freq.begin(); itMap != map_char_freq.end(); itMap++) {
        node = new Tree(itMap->first, itMap->second, nullptr, nullptr);
//        nodeList.push_back(*node);
        nodeVect.push_back(*node);
    }
    
    
    while(nodeVect.size() > 1) {
        sort(nodeVect.begin(), nodeVect.end(), customLess);
        auto itVectList = nodeVect.begin();
//        std::sort(nodeVect.begin(), nodeVect.end(), std::less<double>());
//        sort(nodeVect.begin(), nodeVect.end(), customLess);
        Tree left = *itVectList;
        double lFreq = itVectList->getFreq();
        itVectList += 1;
        Tree right = *(itVectList);
        double rFreq = itVectList->getFreq();
        parent = new Tree('\0', lFreq + rFreq, &left, &right);
        nodeVect.push_back(*parent);
        nodeVect.erase(nodeVect.begin());
        nodeVect.erase(nodeVect.begin());
        cout << nodeVect.size()  << endl;
    }

    
    
//    std::sort(nodeList.begin(), nodeList.end(), customLess);
//    nodeList.sort();
    
//    while(nodeList.size() > 1) {
//        auto itNodeList = nodeList.begin();
//        std::sort(nodeList.begin(), nodeList.end(), std::less<double>());
//        Tree left = *itNodeList;
//        double lFreq = itNodeList->getFreq();
//        Tree right = *(itNodeList++);
//        double rFreq = itNodeList->getFreq();
//        parent = new Tree('\0', lFreq + rFreq, &left, &right);
//        nodeList.push_back(*parent);
//        nodeList.erase(nodeList.begin(), nodeList.begin()++);
//    }
    
    this->tree = parent;
//    nodeList.clear();
    
}



void Haffman::fill_map_char_freq() {
    
    for(int i = 0; i < this->source_str->length() ; i ++) {
        if(this->map_char_freq.find(source_str->at(i)) != map_char_freq.end()) {
            map_char_freq.at(source_str->at(i)) =  (1.0 +
                                                    map_char_freq.at(source_str->at(i)) *
                                                    source_str->length()) /
                                                    (double)source_str->length();
        } else map_char_freq.insert(pair<char, double>(source_str->at(i),
                                                       1.0 / (double)source_str->length()));
    }
}


void Haffman::compress_string(const std::string &source, std::string &compressed) {
    this->source_str = &source;
    this->fill_map_char_freq();
    
    for(auto itMap = map_char_freq.begin(); itMap != map_char_freq.end(); itMap++) {
        cout << itMap->first << " : " << itMap->second << "\n";
    }
    
    this->buildTree();
    
    this->buildCode(this->tree);
}

int main(int argc, const char * argv[]) {
    
    Haffman *haffman = new Haffman();
    
    std:: string source, compressed, result;
    
    std::getline(std::cin, source);
    
    haffman->compress_string(source, compressed);
    
    delete haffman;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

































































































