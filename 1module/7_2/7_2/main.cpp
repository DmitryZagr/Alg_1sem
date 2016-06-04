//7_2. Заявки на переговоры.
//В большой IT­фирме есть только одна переговорная комната.
//Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
//Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
//Число заявок ≤ 100000.


#include <iostream>

struct Node {
    size_t begin;
    size_t end;
    struct Node *next;
    inline Node(size_t b, size_t e) {
        this->begin = b; this->end = e; this->next = nullptr;
    }
    inline ~Node() {};
    size_t static Lenght(Node* node);
};

typedef struct Node Node;

class List {
    
private:
    Node *head;
    
private:
    Node* SortedMerge(Node* a, Node* b);
    void FrontBackSplit(Node* source,
                        Node** frontRef,
                        Node** backRef);
    
public:
    void MergeSort(Node** headRef);
    
public:
    inline List() {this->head = nullptr;}
    ~List();
    
public:
    inline Node *getHead() {return this->head;};
    inline List *setHead(Node *head) {this->head = head; return this;}
    List* add(size_t begin, size_t end);
    bool isEmpty() const;
    void show() const;
    size_t Lenght() const;
    size_t getCountOfRequests();
};

void readNumber(List* list);


int main(int argc, const char * argv[]) {
    
    List *listOfRequests = new List();
    
    readNumber(listOfRequests);
    
    Node* h = listOfRequests->getHead();
    
    (listOfRequests->MergeSort(&h));
    
//    listOfRequests->setHead(h)->show();
    
    std::cout << listOfRequests->setHead(h)->getCountOfRequests();
    
    delete listOfRequests;
    
    return 0;
}

/*------------------------------------------------------------------------------------------------*/

List* List::add(size_t begin, size_t end) {
    
    if (this->head == nullptr) {
        this->head = new Node(begin, end);
    } else {
        Node *tmp = new Node(begin, end);
        tmp->next = this->head;
        head = tmp;
    }
    
    return this;
}

/*------------------------------------------------------------------------------------------------*/

void readNumber(List* list) {
    
    size_t end = 0;
    size_t begin = 0;
    
    while (true) {
        
        std::cin >> begin >> end;
        if (std::cin.fail()) {
            break;
        }
        
        list->add(begin, end);
    }
}

/*------------------------------------------------------------------------------------------------*/

List::~List() {
    
    Node *tmp = nullptr;
    
    while (this->head) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

/*------------------------------------------------------------------------------------------------*/

bool List::isEmpty() const {
    return head == nullptr ? true : false;
}

/*------------------------------------------------------------------------------------------------*/

void List::show() const {
    Node *tmp = this->head;
    
    while (tmp) {
        std:: cout << tmp->begin << " "  << tmp->end << std::endl;
        tmp = tmp->next;
    }
}

/*------------------------------------------------------------------------------------------------*/

size_t List::Lenght() const {
    Node *tmp = this->head;
    size_t countOfElems = 0;
    
    while (tmp) {
        countOfElems++;
        tmp = tmp->next;
    }
    
    return countOfElems;
}

/*------------------------------------------------------------------------------------------------*/

size_t List::getCountOfRequests() {
    
//    std::cout << "__________\n";
    
    if (this->isEmpty()) {
        return 0;
    }
    
    size_t count = 1;
    
    size_t begin = this->head->begin;
    size_t end   = this->head->end;
    
    Node *tmp = this->head;
    
    while (tmp) {
        
        if (end < tmp->end && tmp->begin >= end) {
//            std:: cout << tmp->begin << " " << tmp->end << std::endl;
            begin = tmp->begin;
            end = tmp->end;
            count++;
        }
        
        tmp = tmp->next;
    }
    
    return count;
}

/*------------------------------------------------------------------------------------------------*/


void List::MergeSort(Node** headRef)
{
    Node* head = *headRef;
    Node* a;
    Node* b;
    // вырожденный случай – длина списка равно 0 или 1
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    FrontBackSplit(head, &a, &b);
    MergeSort(&a); // рекурсивная сортировка подсписков
    MergeSort(&b);
    *headRef  = SortedMerge(a, b);
}

Node* List::SortedMerge(Node* a, Node* b)
{
    Node* result = NULL;
    if (a==NULL) return(b);
    else if (b==NULL) return(a);
    if (a->end <= b->end)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}

/*------------------------------------------------------------------------------------------------*/

void List::FrontBackSplit(Node* source,
                    Node** frontRef,
                    Node** backRef)
{
    
    size_t len = Node::Lenght(source);
    size_t i;
    Node* current = source;
    if (len < 2)
    {
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        size_t hopCount = (len-1)/2;
        for (i = 0; i<hopCount; i++)
        {
            current = current->next;
        }
        // исходный список разбивается на два подсписка
        *frontRef = source;
        *backRef = current->next;
        current->next = NULL;
    }
}


size_t Node::Lenght(Node* node) {
    if (!node) {
        return 0;
    } else {
        Node *tmp = node;
        size_t count = 0;
        while (tmp) {
            count++;
            tmp = tmp->next;
        }
        return count;
    }
    
}

/*------------------------------------------------------------------------------------------------*/