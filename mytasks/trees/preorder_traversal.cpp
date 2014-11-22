#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
    Node(int idNumber) : id(idNumber) {};
    int id;
    Node* parent = NULL, *left = NULL, *right = NULL;
};

// R -> A -> B

void preorderRecursive(Node* root, vector<int>& res) {
    if (!root)
        return;
    
    res.push_back(root->id);
    if (root->left)
        preorderRecursive(root->left, res);
    if (root->right)
        preorderRecursive(root->right, res);
}

void preorderNonRecursive(Node* root, vector<int>& res) {
    res.clear();
    
    if (!root)
        return;
    
    stack<Node*> st;
    st.push(root);
    
    while (!st.empty()) {
        root = st.top(); st.pop();
        res.push_back(root->id);
        if(root->right)
            st.push(root->right);
        if(root->left)
            st.push(root->left);
    }
}

int main() {

    try {
        vector<int> resRec, resNonRec;
        vector<int> exp;
        
        Node* n1 = new Node(1);
        Node* n2 = new Node(2); n1->left = n2; n2->parent = n1;
        Node* n3 = new Node(3); n1->right = n3; n3->parent = n1;
        Node* n4 = new Node(4); n2->left  = n4; n4->parent = n2;
        Node* n5 = new Node(5); n2->right = n5; n5->parent = n2;
        Node* n6 = new Node(6); n5->right = n6; n6->parent = n5;
        Node* n7 = new Node(7); n3->left = n7; n7->parent = n3;
        
        //1 test
        preorderRecursive(n1,resRec);
        preorderNonRecursive(n1, resNonRec);
        
        exp = {1,2,4,5,6,3,7};
        if (resRec != exp || resNonRec != exp)
            throw "1 test failed";

        // 2 test
        n1->left = NULL;
        resRec.clear();
        preorderRecursive(n1,resRec);
        preorderNonRecursive(n1, resNonRec);
        
        exp = {1,3,7};

        if (resRec != exp || resNonRec != exp)
            throw "2 test failed";

        // 3 test
        n1->right = NULL;
        resRec.clear();
        preorderRecursive(n1,resRec);
        preorderNonRecursive(n1, resNonRec);
        
        exp = {1};
        
        if (resRec != exp || resNonRec != exp)
            throw "3 test failed";

        cout <<  "all test successed" << endl;
        
    } catch(char const * err) {
        cout << err << endl;
    }
    return 0;
}


