#include <iostream>

using namespace std;

/*
    This function removes element by it's pointer
    Я так понимаю, что этот алгоритм не используется часто, потому что имеет подводные камни.
    Например после удаления эдлемента могут поломаться какие-т указатели. Например в этом примере,
    
    1) После вызова removeElement(n4) на самом деле поломается указатель n5. Причем снаружи это можно сразу не заметить,
    поскольку delete не очищает память за собой.

    2) Вызов removeElement(n4->next) нельзя заменить на removeElement(n6), потому что внутри происходит присваивание 
    el = NULL, и если использоват указатель n6, то n4->next все равно не будет равно NULL

*/

class Node {
public:
    Node(int cId) : id(cId) {};
    Node& operator=(const Node& s) {
        this->id = s.id;
        this->next = s.next;

        // by convention always return *this
        return *this;
    }

    int id;
    Node* next = NULL;
};

void removeElement(Node*& el) {
    if (!el)
        return;

    if (!el->next) {
        delete el;
        el = NULL;
        return;
    }

    Node* tmp = el->next;
    *el = *(el->next);
    delete tmp;
}

void printList(const Node* first) {
    while (first) {
        cout << first->id << " ";
        first = first->next;
    }
    cout << endl;
}

int main(int argc, const char* argv[]) {
    try {

        Node* n1 = new Node(1);
        Node* n2 = new Node(2); n1->next = n2;
        Node* n3 = new Node(3); n2->next = n3;
        Node* n4 = new Node(4); n3->next = n4;
        Node* n5 = new Node(5); n4->next = n5;
        Node* n6 = new Node(6); n5->next = n6;

        printList(n1);
        removeElement(n4);
        printList(n1);

        removeElement(n4->next);
        printList(n1);
        removeElement(n1);
        printList(n1);

    } catch(char const* err) {
        cout << err << endl;
    }
    return 0;
}
