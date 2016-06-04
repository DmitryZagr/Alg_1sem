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
};

typedef struct Node Node;

class List {
    
private:
    
    List *head = nullptr;
    List *next = nullptr;
    size_t begin = 0;
    size_t end = 0;
    
private:
    static size_t prevEnd;
    
private:
    void static FrontBackSplit(List* source,
                        List** frontRef,
                        List** backRef);
    List* SortedMerge(List* a, List* b);
    
public:
    void MergeSort(List** headRef);
    
public:
    List();
//    List( size_t begin, size_t end);
    ~List();
    
public:
    List* add(size_t begin, size_t end);
    bool isEmpty() const;
    void show() const;
    size_t Lenght() const;
    size_t getCountOfRequests();
};

void readNumber(List* list);






int main(int argc, const char * argv[]) {
    
    List *listOfRequests = new List();
    
//    readNumber(listOfRequests);
    listOfRequests->add(1, 2);
    listOfRequests->add(2, 5);
    listOfRequests->add(7, 10);
    listOfRequests->add(2 , 3);
    listOfRequests->add(6, 7);
    listOfRequests->add(4, 7);
    listOfRequests->add(3, 6);
    listOfRequests->add(3, 5);
    listOfRequests->add(1, 2);
    listOfRequests->add(6, 7);
    listOfRequests->add(4, 5);
    listOfRequests->add(6, 10);
    listOfRequests->add(4, 5);

    listOfRequests->show();
    
    std::cout << "\n____________\n";
    
    listOfRequests->MergeSort(&listOfRequests);
    
    listOfRequests->show();
    
//    std::cout << listOfRequests->getCountOfRequests();
    
    
    return 0;
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

List::List() {
    this->head = nullptr;
    this->next = nullptr;
    this->end = 0;
    this->begin = 0;
}

/*------------------------------------------------------------------------------------------------*/

List::~List() {
    
    List *tmp = nullptr;
    
    while (this->head) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

/*------------------------------------------------------------------------------------------------*/

List* List::add(size_t begin, size_t end) {
    
    List *node  = new List();
    node->end   = end;
    node->begin = begin;
    
    if (this->head == nullptr) {
        this->head = node;
        this->next = nullptr;
    } else {
        node->next = head;
        head = node;
        
    }

    
    
//    if (this->head == nullptr) {
//        this->head = node;
//        return this;
//    } else {
//        
//        List *tmp  = this->head;
//        List *prev = nullptr;
//        
//        if (this->head->begin == begin && this->head->end == end) {
//            delete node;
//            return this;
//        }
//        
//        
//        if ( this->head->end >= node->end ) {
//            node->next = this->head;
//            this->head = node;
//            return this;
//        }
//        
////        size_t prevEnd = this->head->end;
//        
//        while (tmp) {
//            
//            prev = tmp;
//            tmp  = tmp->next;
//            
//            if (!tmp) {
////                std:: cout << "LOL " << prev->begin << " " << prev->end << " " << node->begin << "\n";
//                if (prev->end <= node->end /*&& node->begin >= prev->end*/) //!!!
//                    prev->next = node;
//                else {
//                    node->next = this->head;
//                    this->head = node;
//                }
//            } else {
//                
//                if ((tmp->begin == begin && tmp->end == end) || (prev->begin == begin && prev->end == end)) {
//                    delete node;
//                    return this;
//                }
//                
//                if (node->end <= tmp->end /*&& node->begin >= prev->end*/) {
////                    if (node->begin >= prev->end) {
//                        prev->next = node;
//                        node->next = tmp;
////                        List::prevEnd = end;
//                        return this;
////                    }
////                    return this;
//                }
//            }
//            
////            if (prevEnd != prev->end) {
////                prevEnd = prev->end;
////                std:: cout << "| " << prevEnd << " |\n";
////            }
//        }
//    }
    
    return this;
}

/*------------------------------------------------------------------------------------------------*/

bool List::isEmpty() const {
    return head == nullptr ? true : false;
}

/*------------------------------------------------------------------------------------------------*/

void List::show() const {
    List *tmp = this->head;
    
    while (tmp) {
        std:: cout << tmp->begin << " "  << tmp->end << std::endl;
        tmp = tmp->next;
    }
}

/*------------------------------------------------------------------------------------------------*/

size_t List::Lenght() const {
    List *tmp = this->head;
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
    
    List *tmp = this->head->next;
    
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

void List::MergeSort(List** headRef)
{
    printf("begin\n");
    List* head = (*(headRef))->head;
    List* a;
    List* b;
    // вырожденный случай – длина списка равно 0 или 1
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    FrontBackSplit(head, &a, &b);
    MergeSort(&a); // рекурсивная сортировка подсписков
    MergeSort(&b);
    (*headRef)->head  = SortedMerge(a, b);
    
    (*headRef)->show();
    
    std::cout << "end\n";
}

/*------------------------------------------------------------------------------------------------*/

//void MergeSort(struct node** headRef)
//{
//    struct node* head = *headRef;
//    struct node* a;
//    struct node* b;
//    // вырожденный случай – длина списка равно 0 или 1
//    if ((head == NULL) || (head->next == NULL))
//    {
//        return;
//    }
//    FrontBackSplit(head, &a, &b);
//    MergeSort(&a); // рекурсивная сортировка подсписков
//    MergeSort(&b);
//    *headRef  = SortedMerge(a, b);
//}

/*------------------------------------------------------------------------------------------------*/

void List::FrontBackSplit(List* source,
                    List** frontRef,
                    List** backRef) {
    size_t len = source->List::Lenght();
    size_t i;
     std::cout << "len: " << len << std::endl;
    List* current = source;
    if (len < 2)
    {
        (*frontRef)->head = source->head;
        (*backRef)->head = nullptr;
    }
    else
    {
        size_t hopCount = (len-1)/2;
        std::cout << "hopCount: " << hopCount << std::endl;
        for (i = 0; i < hopCount; i++)
        {
            current = current->next;
        }
        // исходный список разбивается на два подсписка
        *frontRef = source;
        (*backRef)->head = current->next;
        current->next = NULL;
    }
    
}

/*------------------------------------------------------------------------------------------------*/

List* List::SortedMerge(List* a, List* b)
{
    List* result = NULL;
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


/*------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------*/
