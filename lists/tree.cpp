#include <iostream>
#include <queue>
#include <string>

using namespace std;

/*
6) Распечатать двоичное дерево "по уровням". То есть для дерева
   A
    B  C
    D E F

    Надо вывести
    A
    BC
    DEF
    с переводами строк.
*/


class Node {
public:
    Node *left = NULL, *right = NULL;
    char letter;
    Node(char c) : letter(c) {};
};

void printtree(Node* root, string& res) {
    res.clear();

    if (!root)
        return;

    queue<Node*> q;

    q.push(root);
    q.push(NULL);
    Node* tmp;

    while (true) {
        if (!q.front()) {
            q.pop();
            if (q.empty())
                break;
            
            cout << endl;
            res.append("\n");
            q.push(NULL);
            continue;
        }
        
        tmp = q.front(); q.pop();
        cout << tmp->letter; res.push_back(tmp->letter);
        if (!q.empty() && q.front()) {
            cout << " ";
            res.push_back(' ');
        }

        if (tmp->left)
            q.push(tmp->left);
        if (tmp->right)
            q.push(tmp->right);
    }
    cout << endl;

    return;
}

int main() {
    try {
        string res;
        printtree(NULL, res);

        // 1 test
        if (!res.empty())
            throw "1 test failed";

        // 2 test
        Node* n1 = new Node('A');
        printtree(n1, res);

        if (res != "A")
            throw "2 test failed";

        // 3 test
        Node* n2 = new Node('B'); n1->left = n2;
        printtree(n1, res);
        if (res != "A\nB")
            throw "3 test failed";
        
        // 4 test
        Node* n3 = new Node('C'); n1->right = n3;
        printtree(n1, res);
        if (res != "A\nB C")
            throw "4 test failed";

        // 5 test
        Node* n4 = new Node('D'); n3->right = n4;
        Node* n5 = new Node('E'); n4->right = n5;

        printtree(n1, res);
        if (res != "A\nB C\nD\nE")
            throw "5 test failed";
        
        cout << "All tests successed" << endl;
    } catch (char const* err) {
        cout << err << endl;
    }
    return 0;
}

