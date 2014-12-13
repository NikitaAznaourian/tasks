#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
#include <locale>
    
using namespace std;

std::locale loc;

class Node {
public:
    Node(int n) : val(n) {};
    Node(const Node& node) : left(node.left), right(node.right), val(node.val){};
    
    Node *left = NULL, *right = NULL;
    int val;
};

Node* copyTree(Node* root) {
    if (!root)
        return NULL;
    
    Node* newRoot = new Node(*root);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

int main() {
    try {
        
        Node* n1 = new Node(4);
        Node* n2 = new Node(2); n1->left = n2;
        Node* n3 = new Node(6); n1->right = n3;
        Node* n4 = new Node(7); n2->right = n4;
        
        Node* newRoot = copyTree(n1);
        
        if (newRoot->val != 4 || newRoot == n1 || newRoot->left->val != 2 || newRoot->left->right->val != 7 || newRoot->left == n2 || newRoot->left->right == n4 ||
            newRoot->right->val != 6)
            throw "test failed";
        
        cout << "All test successfull\n";
        
    } catch(char const * err) {
        cout << err << endl;
    }
    
    return 0;
}
