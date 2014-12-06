//
//  main.cpp
//  tmp
//

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
#include <locale>
    
using namespace std;

std::locale loc;


/*
    In binary tree find all ways that summarize as input value
    Career of programmer 4.9
*/

class Node {
public:
    Node(int i) : val(i) {};
    Node* left = NULL, *right = NULL;
    int val;
};

void findWaysH(Node* root, int sum, vector<vector<Node*>>& res, vector<Node*> curRes) {
    if (!root)
        return;
    
    curRes.push_back(root);
    int curSum = 0;
    
    for (int i = curRes.size()-1; i >= 0; i--) {
        curSum += curRes[i]->val;
        
        if (curSum == sum) {
            vector<Node*> curWay(curRes.begin()+i, curRes.end());
            res.push_back(curWay);
        }
    }
    
    if (root->left)
        findWaysH(root->left, sum, res, curRes);
    if (root->right)
        findWaysH(root->right, sum, res, curRes);
    
    curRes.pop_back();
    return;
}

void findWays(Node* root, int sum, vector<vector<Node*>>& res) {
    res.clear();
    if (!root)
        return;
    vector<Node*> curRes;
    findWaysH(root, sum, res, curRes);
    return;
}

int main() {
    try {
        Node* n1 = NULL;
        vector<vector<Node*>> res;
        
        // 1 test
        findWays(n1,10, res);
        if (res.size())
            throw "1 test failed";
        
        // 2 test
        n1 = new Node(1);
        findWays(n1,10, res);
        if (res.size())
            throw "2 test failed";
        
        // 3 test
        n1 = new Node(1);
        findWays(n1,1, res);
        if (res.size() != 1 && res[0][0]->val != 1)
            throw "3 test failed";
        
        // 4 test
        Node* n2= new Node(2); n1->left = n2;
        Node* n3= new Node(6); n1->right = n3;
        Node* n4= new Node(3); n2->left = n4;
        Node* n5= new Node(4); n2->right = n5;
        Node* n6= new Node(-1); n3->left = n6;
        Node* n7= new Node(0); n3->right = n7;
        Node* n8= new Node(1); n6->right = n8;
        Node* n9= new Node(0); n7->left = n9;
        Node* n10= new Node(6); n9->right = n10;
        Node* n11= new Node(1); n10->left = n11;
        
        findWays(n1,7, res);
        vector<vector<Node*>> excp = {{n1,n2,n5}, {n1,n3}, {n1,n3,n6,n8}, {n1,n3,n7}, {n1,n3,n7, n9}, {n10, n11}, {n9, n10, n11}, {n7, n9, n10, n11}};
        if (res != excp)
            throw "4 test failed";
        
        cout << "All test successfull\n";
        
    } catch(char const * err) {
        cout << err << endl;
    }
    
    return 0;
}










