#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Node {
public:
    Node(int tid) : id(tid) {};
    int id;
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = NULL;
};

// Left subtree, root , right subtree

vector<int> inorderTraversal(Node* root) {
    stack<Node*> st;
    vector<int> res;
    while (!st.empty() || root) {
        if (root) {
            // just go left until end
            while (root) {
                st.push(root);
                root = root->left;
            }
        } else {
            root = st.top();
            st.pop();
            res.push_back(root->id);
            root = root->right;
        }
    }
    
    return res;
}

vector<int> InOrderWithoutStack(Node* root) {
    vector<int> res;

    if (!root)
        return res;
    
    Node* p1 = root, *p2 = p1->parent;
    
    while (p1) {
        if (p1->left && p1->parent == p2) {
            p2 = p1; p1 = p1->left;
            continue;
        }
        
        if (p1->right != p2 || !p2)
            res.push_back(p1->id);
        
        if (p1->right && p1->right != p2) {
            p2 = p1; p1 = p1->right;
        } else {
            p2 = p1; p1 = p1->parent;
        }
    }
    
    return res;
}

int main() {
    try {
        vector<int> res;
        vector<int> exp;
        
        Node* n1 = new Node(1);
        Node* n2 = new Node(2); n1->left = n2; n2->parent = n1;
        Node* n3 = new Node(3); n1->right = n3; n3->parent = n1;
        Node* n4 = new Node(4); n2->left  = n4; n4->parent = n2;
        Node* n5 = new Node(5); n2->right = n5; n5->parent = n2;
        Node* n6 = new Node(6); n5->right = n6; n6->parent = n5;
        Node* n7 = new Node(7); n3->left = n7; n7->parent = n3;
        
        //1 test
        res = InOrderWithoutStack(n1);
        
        exp = {4,2,5,6,1,7,3};
        if (res != exp)
            throw "1 test failed";
        
        // 2 test
        n1->left = NULL;
        res = InOrderWithoutStack(n1);
        exp = {1,7,3};

        if (res != exp)
            throw "2 test failed";
        
        // 3 test
        n1->right = NULL;
        res = InOrderWithoutStack(n1);
        exp = {1};
        
        if (res != exp)
            throw "3 test failed";

        cout << "All test successed\n";
    } catch(char const* err) {
        cout << err << endl;
    }
    return 0;
}

