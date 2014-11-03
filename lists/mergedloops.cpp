#include <iostream>

using namespace std;

class Node {
public:
    Node(int idNumber) : id(idNumber) {};
    int id;
    Node* next = NULL;
};


/*
    2) Два односвязных списка с некоторого момента могут совпадать, т.е. Node *a,*b; a != b; a.next == b.next. Найти точку слияния. Линейное время, константная память.
    Усложнённый вариант на подумать — за время, линейное по расстоянию до точки слияния (т.е. для списка с длинным хвостом мы можем прочитать не все элементы)

    Note: Реализовываю сразу сложный вариант, потому что первый я писал сам - он простой (дойти до конца, посчитать кол-во узлов, итд).

    Описание: 
    1) Идем с обоих начал и разворачиваем список пока они либо не станут равными (если расстояние до пересечения одинаковые), либо пока не дойдут
    до конца (значит пересечения нет), либо один из них не дойдет до начала другого.

    2) Если пересечения нет, то придется еще раз пройтись по обоим спискам и развернуть еще раз.
    3) Если Пересечение есть, то тот, который дошел до начала второго идет обратно и опять разворачивает список, пока не дойдет до своего начала
    4) Теперь первый и второй указаетли находятся на одинаковом расстояние до точки пересечения. Поэтому первй просто идет вперед, пока они не встретятся, а второй 
    идет назад и при этом еще разворачивает список.
    5) Тот указатель на котором они встретятся и будет ответом.
    6) Второй продолжает идти по списку и разворачивать его.

    - На самом деле в этом алгоритме есть баг, что если хвост короче, чем длина одной из голов, то он вернет NULL, но для того, чтобы это проверить придется пройтись 
    до конца за O(n)

    Сложность: 8m, где m - длина до пересечения от каждого из начал списков

*/
void reverseList(Node* root) {
    if (!root)
        return;
    
    Node* tmp = root, *prev = NULL, *next = tmp->next;
    while (tmp) {
        tmp->next = prev;
        prev = tmp;
        tmp = next;
        if (tmp)
            next = tmp->next;
    }
}

Node* processRevertedLists(Node* prev1, Node* tmp1, Node* prev2, Node* tmp2, Node* next2, Node* root) {
    Node* res = NULL;
    
    reverseList(prev1);
    prev1->next = tmp1;
    
    tmp2->next = prev2;
    prev2 = next2;
    next2 = tmp2->next;
    tmp1 = root;

    // move to function
    while (tmp2 != tmp1) {
        tmp2->next = prev2;
        prev2 = tmp2;
        tmp2 = next2;
        if (tmp2)
            next2 = tmp2->next;

        if (tmp1)
            tmp1 = tmp1->next;
    }

    res = tmp1;

    // just reverse the rest of list
    reverseList(tmp2);

    if(tmp2)
        tmp2->next = prev2;
    return res;
}

Node* findCross(Node* root1, Node* root2) {
    if (!root1 || !root2)
        return NULL;
    
    Node* tmp1 = root1, *prev1 = NULL, *next1 = tmp1->next;
    Node* tmp2 = root2, *prev2 = NULL, *next2 = tmp2->next;
    bool reachRoot = false;
    
    while (tmp1 && tmp2) {
        if (tmp1 == root2 || tmp2 == root1 || tmp1 == tmp2) {
            reachRoot = true;
            break;
        }
        
        tmp1->next = prev1;
        prev1 = tmp1;
        tmp1 = next1;

        tmp2->next = prev2;
        prev2 = tmp2;
        tmp2 = next2;

        if (tmp2)
            next2 = tmp2->next;
        if (tmp1)
            next1 = tmp1->next;
    }
    
    if (!reachRoot) {
        // На самом деле то, что мы достигли конца списка может означать также и то, что хвост не очень длинный,
        // но раз в этом случае лучше использоват алгоритм с подсчетом длины        

        reverseList(prev1);
        prev1->next = tmp1;

        reverseList(prev2);
        prev2->next = tmp2;
        return NULL;
    }

    if (tmp1 == root2) {
        return processRevertedLists(prev1, tmp1, prev2, tmp2, next2, root1);
    } else {
        return processRevertedLists(prev2, tmp2, prev1, tmp1, next1, root2);
    }
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

        Node* n8 = new Node(8);
        Node* n9 = new Node(9); n8->next = n9; n9->next = n4;

        // 1 test
        Node* res = findCross(n1, n8);
        if (!res )
            throw "1 test failed";
        if (res->id != 4)
            throw "2 test failed";

        // 3 test
        n9->next = NULL;
        if (findCross(n1, n8))
            throw "3 test failed";

        // 4 test
        if (findCross(n1, n3)->id != 3 )
            throw "4 test failed";        

        cout <<  "all test successed" << endl;

    } catch(char const * err) {
        cout << err << endl;
    }
    return 0;
}


