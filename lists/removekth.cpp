#include <iostream>

using namespace std;

class Node {
public:
    Node(int idNumber) : id(idNumber) {};
    int id;
    Node* next = NULL;
};


/*
    3) Удалить из односвязного списка k-ый элемент с конца. Линейное время, константная память.

    Описание: Идти двумя указателями. На расстояние к. Когда второй дойдет до конца - первый будет тем эл-ом, который нужно удалить
*/

void removeKth(Node*& root, int k) {
    if (!root || k < 0)
        return;

    Node* first = root;

    while (k--) {
        first = first->next;
        if (!first)
            throw "Too big k";
    }

    Node* res = root;
    Node* prev;
    while (first->next) {
        first = first->next;
        prev = res;
        res = res->next;
    }

    if (res == root) {
        root = root->next;
    } else {
        prev->next = res->next;
    }

    delete res;
}

bool containsId (Node* root, int id) {
    while (root) {
        if (root->id == id)
            return true;
        root = root->next;
    }

    return false;
}

int main() {
    try {
        Node* n1 = new Node(1);
        Node* n2 = new Node(2); n1->next = n2;
        Node* n3 = new Node(3); n2->next = n3;
        Node* n4 = new Node(4); n3->next = n4;
        Node* n5 = new Node(5); n4->next = n5;
        Node* n6 = new Node(6); n5->next = n6;
        Node* n7 = new Node(7); n6->next = n7;

        // 1 test
        if (!containsId(n1, 6))
            throw "1 test failed";

        // 2 test
        removeKth(n1, 1);
        if (containsId(n1, 6))
            throw "2 test failed";
        
        // 3 test
        if (!containsId(n1, 7))
            throw "3 test failed";

        // 4 test
        removeKth(n1, 0);
        if (containsId(n1, 7))
            throw "4 test failed";

        // 5 test
        removeKth(n1, 4);
        if (containsId(n1, 1))
            throw "5 test failed";

        // 6 test
        bool ex = false;
        try {
            removeKth(n2, 4);
        } catch(...) {
            ex = true;
        }

        if (!ex)
            throw "6 test failed";

        cout <<  "all test successed" << endl;

    } catch(char const * err) {
        cout << err << endl;
    }
    return 0;
}


