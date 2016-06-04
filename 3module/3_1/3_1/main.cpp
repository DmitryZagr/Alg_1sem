//
//  main.cpp
//  3_1
//
//  Created by Дмитрий  Загребаев on 21.05.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

/*
 Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, 
 рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. 
Затем разбейте найденное поддерево по ключу x так,
 чтобы в первом поддереве все ключи меньше x,
 а во втором больше или равны x.
Получившиеся два дерева сделайте дочерними для нового узла (x, y).
Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

3_1. Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.
*/

#include <iostream>
#include <stdint.h>

using namespace std;

template<class T, class Y = int> struct Node {
    T key;
    Y priority;
    Node<T> *left;
    Node<T> *right;
    
    Node(T newKey, Y newP = 0) {
        key = newKey;
        left = nullptr;
        right = nullptr;
        priority = newP;
    }
};

template <class T, class Y>
class DTree {
    Node<T, Y> *root;
    int depthD;
    
public:
    inline DTree() {
        root = nullptr;
        depthD = 0;
    }
    
    inline ~DTree() {
        clean(root);
    }
    
    void insert(T newKey, Y prior) {
        if(root == nullptr) {
            root = new Node<T, Y>(newKey, prior);
        } else {
            Node<T, Y>* newNode  = new Node<T, Y>(newKey, prior);
            addNode(root, newNode);
        }
    }
    
    int depth() {
        this->depthD = treeHight(root);
        return this->depthD;
        
    }
    
private:
    
    int treeHight (Node<T> *&curRoot)
    {
        int depthLeft, depthRight, depthval;
        
        if (curRoot == nullptr)
            depthval = -1;
        else
        {
            depthLeft = treeHight(curRoot->left);
            depthRight = treeHight(curRoot->right);
            depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
        }
        return depthval;
    }

    
    void addNode(Node<T, Y>*& curRoot, Node<T, Y>*& newNode){
        
        if(curRoot == nullptr) {
            curRoot = newNode;
        } else if(newNode->priority > curRoot->priority) {
            split(curRoot, newNode->key, newNode->left, newNode->right);
            curRoot = newNode;
        } else {
            if(curRoot->key > newNode->key) addNode(curRoot->left, newNode);
            else addNode(curRoot->right, newNode);
        }
    }
    
private:
    
    void split(Node<T, Y>*& curRoot, T key, Node<T, Y>*& left, Node<T, Y>*& right) {
        
        if (curRoot == nullptr) {
            
            left = right = nullptr;
            
        } else if (curRoot->key > key) {
            
            split(curRoot->left, key, left, curRoot->left);
            right = curRoot;
        } else {
            
            split(curRoot->right, key, curRoot->right, right);
            left = curRoot;
        }
    }

    
private:
    
    void clean(Node<T, Y> *&curRoot) {
        if(curRoot != nullptr) {
            clean(curRoot->left);
            clean(curRoot->right);
            delete curRoot;
            curRoot = nullptr;
        }
    }

};

template <class T>
class BTree {
    int32_t countOfNodes;
    Node<T> *root;
    int depthT;
    
public:
    inline BTree() {
        countOfNodes = 0;
        root = nullptr;
        depthT = 0;
    }
    
    inline ~BTree() {
        clean(root);
    }
    
public:
    void insert(T newKey) {
        if(root == nullptr) {
            root = new Node<T>(newKey);
        } else {
            addNode(newKey, root);
        }
        
    }
    
    void show()  {
        show(root);
    }
    
    int depth() {
        this->depthT = treeHight(root);
        return this->depthT;
        
    }
    
private:
    void show(Node<T> *&curRoot) const{
        if(curRoot != nullptr) {
            show(curRoot->left);
            std::cout << curRoot->key << " ";
            show(curRoot->right);
        }
    }
    
private:
    void addNode(T newKey, Node<T> *&curRoot){
        
        if(newKey < curRoot->key) {
            if(curRoot->left != nullptr) addNode(newKey, curRoot->left);
            else {
                
                curRoot->left = new Node<T>(newKey);
                countOfNodes++;
            }
        } else {
            if(curRoot->right != nullptr) addNode(newKey, curRoot->right);
            else {
                curRoot->right = new Node<T>(newKey);
                countOfNodes++;
            }
        }
    }
    
private:
    
    void clean(Node<T> *&curRoot) {
        if(curRoot != nullptr) {
            clean(curRoot->left);
            clean(curRoot->right);
            delete curRoot;
            curRoot = nullptr;
        }
    }
    
    int treeHight (Node<T> *&curRoot)
    {
        int depthLeft, depthRight, depthval;
        
        if (curRoot == nullptr)
            depthval = -1;
        else
        {
            depthLeft = treeHight(curRoot->left);
            depthRight = treeHight(curRoot->right);
            depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
        }
        return depthval;
    }
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    int32_t N = 0;
    std::cin >> N;
    
    int32_t key      = 0;
    int32_t priority = 0;
    
    BTree<int32_t> *bt = new BTree<int32_t>();
    DTree<int, int> *dt = new DTree<int, int>();
    
    for(int32_t i = 0; i < N; i++) {
        std::cin >> key >> priority;
        bt->insert(key);
        dt->insert(key, priority);
    }
    
    
    std::cout << bt->depth() - dt->depth() - 1;
    
    delete bt;
    
    //    std::cout << "Hello, World!\n";
    return 0;
}
