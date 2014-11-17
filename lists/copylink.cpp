#include <iostream>

using namespace std;

/*
7*) Глубокое копирование односвязного списка с дополнительным указателем.
В каждом элементе списка хранится дополнительный указатель Node*, который указывает на элемент того же списка (вперёд или назад — неизвестно)

Надо за линейное время и константную память изготовить глубокую копию списка. Т.е. Если в оригинальном списке дополнительный
указатель в седьмом элементе указывал на пятый элемент от начала, то и в копии дополнительный указатель седьмого элемента копии указывает на пятый элемент копии.

Решение:
    После каждого элемента создаем его копию. И элемент оригинального списка начинат указывать на вновь созданный элемент. А новый элемент начинает указывать
    на следующий элемент оригинального списка.
    Например: 1->2->3->4 => 1->1'->2->2'->3->3'->4->4'

    Дальше идем посписку еще раз и меняем поле random в созданных элементах. Если 1->random = 4, то 1'->random = 4->next

    3-ий проход - разделяем списко на 2
*/

class Node {
public:
    Node(int i) : val(i) {};
    Node* next = NULL;
    Node* random = NULL;
    int val;
};

Node* copy(Node* root) {
    if (!root)
        return NULL;

    Node* curNode = root;
    Node* createdNode;
    
    while (curNode) {
        createdNode = new Node(curNode->val);
        createdNode->next = curNode->next;
        curNode->next = createdNode;

        curNode = createdNode->next;
    }

    curNode = root;
    while (curNode) {
        if (!curNode->random) {
            curNode->next->random = NULL;
        } else {
            curNode->next->random = curNode->random->next;
        }
        curNode = curNode->next->next;
    }

    // result to return
    Node* resRoot = root->next;
    
    curNode = root;
    Node* tmp;
    while (curNode->next) {
        tmp = curNode->next;
        curNode->next = curNode->next->next;
        curNode = tmp;
    }

    return resRoot;
}

int getLength(const Node* root) {
    int counter = 0;
    while (root) {
        counter++;
        root = root->next;
    }

    return counter;
}

void removeList(Node* root) {
    Node* tmp;
    while (root) {
        tmp = root;
        root = root->next;
        delete tmp;
    }
}

bool EqualLists(const Node* root1, const Node* root2) {
    while (1) {
        if ( (root1 && !root2) || (root2 && !root1) )
            return false;
        if (!root1 && !root2)
            return true;
        
        if ( (root1->val != root2->val) || (root1->random->val != root2->random->val))
            return false;

        root1 = root1->next;
        root2 = root2->next;
    }
}

int main() {
    try {
        
        // 1 test
        Node* res = copy(NULL);
        if (res)
            throw "1 test failed";

        // 2 test
        Node* n1 = new Node(1); n1->random = n1;
        res = copy(n1);
        if (getLength(res) != 1 || res->random != res)
            throw "2 test failed";
        removeList(res);

        // 3 test
        Node* n2 = new Node(2); n1->next = n2;
        Node* n3 = new Node(3); n2->next = n3; n3->random = n1;
        Node* n4 = new Node(4); n3->next = n4; n1->random = n4; n2->random = n4; n4->random = n2;

        res = copy(n1);
        if (!EqualLists(n1, res))
            throw "3 test failed";

        cout << "All tests successed" << endl;

    } catch (char const * err ) {
        cout << err << endl;
    }
    
    return 0;
}
