#include <iostream>

using namespace std;

class Node {
public:
    Node(int idNumber) : id(idNumber) {};
    int id;
    Node* next = NULL;
};


/*
    1) Дан односвязный список, который может быть зациклен. Определить есть ли цикл, а так же длину цикла и длину "предцикла". Линейное время, константная память.
    
    Perfomance complexity: O(n)
    Spatial complexity: O(1)

    Use two pointers fast and slow. If they meet there is a loop, otherwise threre is no loop.
    After that move one of them at start position and start to move with step 1. When they meet
    there is a loop point.
*/

void LoopDetect(const Node* root, bool& isLoop, int& preLoopLen, int& postLoopLen) {
    preLoopLen = 0;
    postLoopLen = 0;
    isLoop = false;

    if (!root)
        return;

    const Node* slow = root;
    const Node* fast = root;

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            isLoop = true;
            break;
        }
    }

    if (!isLoop)
        return;

    fast = root;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
        preLoopLen++;
    }
    
    // postLoopLen = 0
    if (fast->next == fast)
        return;

    fast = fast->next; postLoopLen++;
    while (fast != slow) {
        fast = fast->next;
        postLoopLen++;
    }
    return;
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

        // test 1
        bool isLoop = true;
        int preLoopLen, postLoopLen;
        LoopDetect(n1, isLoop, preLoopLen, postLoopLen);
        if (isLoop)
            throw "1 test failed";

        // test 2
        n7->next = n1;
        LoopDetect(n1, isLoop, preLoopLen, postLoopLen);
        if (!isLoop || preLoopLen != 0 || postLoopLen != 7)
            throw "2 test failed";

        // test 3
        n7->next = n4;
        LoopDetect(n1, isLoop, preLoopLen, postLoopLen);
        if (!isLoop || preLoopLen != 3 || postLoopLen != 4)
            throw "3 test failed";

        // test 4
        n7->next = NULL;
        n1->next = n1;
        LoopDetect(n1, isLoop, preLoopLen, postLoopLen);
        if (!isLoop || preLoopLen != 0 || postLoopLen != 0)
            throw "4 test failed";

        // test 5
        n1->next = NULL;
        LoopDetect(n1, isLoop, preLoopLen, postLoopLen);
        if (isLoop || preLoopLen != 0 || postLoopLen != 0)
            throw "5 test failed";

        cout <<  "all test successed" << endl;

    } catch(char const * err) {
        cout << err << endl;
    }
    return 0;
}


