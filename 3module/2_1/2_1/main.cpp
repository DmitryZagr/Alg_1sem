//
//  main.cpp
//  2_1
//
/*
 Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
 Требуется построить бинарное дерево, заданное наивным порядком вставки.
 Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
*/
//  Created by Дмитрий  Загребаев on 13.05.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>
#include <stdint.h>

template<class T> struct Node {
    T key;
    Node<T> *left;
    Node<T> *right;
    
    Node(T newKey) {
        key = newKey;
        left = nullptr;
        right = nullptr;
    }
};

template <class T>
class BTree {
    int32_t countOfNodes;
    Node<T> *root;
    
public:
    inline BTree() {
        countOfNodes = 0;
        root = nullptr;
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
//            std::cout << " priv ";
        }
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    int32_t N = 0;
    std::cin >> N;
    
    int32_t buf = 0;
    
    
    BTree<int32_t> *bt = new BTree<int32_t>();
    
    for(int32_t i = 0; i < N; i++) {
        std::cin >> buf;
        bt->insert(buf);
    }
    
    bt->show();
    
    delete bt;
    
//    std::cout << "Hello, World!\n";
    return 0;
}
