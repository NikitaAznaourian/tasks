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

enum STATE {INIT, INT, COMMA, OPENING, CLOSING};

class Node {
public:
    int id;
    vector<Node*> descendants;
    
    Node(int cId) : id(cId) {};
};

//deserialize string

void deserializeH(string& serialized, size_t& pos, vector<Node*>& children) {
    if (pos >= serialized.size())
        return;
    
    Node* curNode;
    int id = 0;
    
    STATE st = INIT;
    
    while (pos < serialized.size()) {
        if (isdigit(serialized[pos])) {
            if (st != INIT && st != COMMA)
                throw "bad state";
            id = 10*id +stoi(string() + serialized[pos]);
            st = INT;
            pos++;
        } else if (serialized[pos] == '{') {
            if (st != INT)
                throw "{ without int";
            
            st = OPENING;
            curNode = new Node(id); id = 0;
            children.push_back(curNode);
            
            deserializeH(serialized, ++pos, curNode->descendants);
            curNode = NULL;
        } else if (serialized[pos] == ',') {
            if (st != OPENING && st != INT)
                throw "bad state";
            
            if (id) {
                children.push_back(new Node(id));
                id = 0; curNode = NULL;
            }
            st = COMMA;
            pos++;
        } else if (serialized[pos] == '}') {
            if (st != INT && st != OPENING)
                throw "bad state";
            if (id) {
                children.push_back(new Node(id));
                id = 0; curNode = NULL;
            }
            pos++;
            st = CLOSING;
            return;
        } else {
            throw "Unknow character in the string";
        }
    }
}

Node* deserialize(string& serialized) {
    if (serialized.empty())
        return NULL;
    
    if (serialized[0] != '{' || serialized[serialized.size()-1] != '}')
        throw "Incorrect string";
    
    size_t pos = 1;
    vector<Node*> root;
    deserializeH(serialized, pos, root);
    
    return root[0];
}

// serialize string

void serializeH(Node* root, string& serialized) {
    if (!root)
        return;
    
    serialized.append(to_string(root->id));
    
    for (size_t i = 0; i< root->descendants.size(); i++) {
        if (i == 0)
            serialized.push_back('{');
        
        serializeH(root->descendants[i], serialized);

        if (i != root->descendants.size()-1) {
            serialized.push_back(',');
        } else {
            serialized.push_back('}');
        }
    }
    
}

void serialize(Node* root, string& serialized) {
    serialized.clear();
    if (!root)
        return;
    
    serialized.push_back('{');
    serializeH(root, serialized);
    serialized.push_back('}');
}

// compare two trees
bool compareTrees(Node* root1, Node* root2) {
    if ( (!root1 && root2) || (root1 && !root2) )
        return false;
    
    if (!root1 && !root2)
        return true;
    
    if (root1->descendants.size() != root2->descendants.size() || root1->id != root2->id)
        return false;
    
    for (auto i = 0; i < root1->descendants.size(); i++) {
        if (!compareTrees(root1->descendants[i], root2->descendants[i]))
            return false;
    }
    
    return true;
}


int main() {
    try {
        string res;
        
        // 1 test
        serialize(NULL, res);
        if (!res.empty())
            throw "first test failed";
        
        // 2 test
        Node* n1 = new Node(1);
        serialize(n1, res);
        if (res != "{1}")
            throw "2 test failed";
        
        Node* root = deserialize(res);
        if (!compareTrees(n1, root))
            throw "2.1 test failed";
        

        // 3 test
        Node* n2 = new Node(2); n1->descendants.push_back(n2);
        
        serialize(n1, res);
        if (res != "{1{2}}")
            throw "3 test failed";
        
        root = deserialize(res);
        if (!compareTrees(n1, root))
            throw "3.2 test failed";
        
        // 4 test
        Node* n3 = new Node(3); n1->descendants.push_back(n3);
        Node* n4 = new Node(4); n1->descendants.push_back(n4);
        
        serialize(n1, res);
        if (res != "{1{2,3,4}}")
            throw "4 test failed";
        
        root = deserialize(res);
        if (!compareTrees(n1, root))
            throw "4.2 test failed";

        // 5 test
        Node* n5 = new Node(5); n2->descendants.push_back(n5);
        Node* n6 = new Node(6); n2->descendants.push_back(n6);
        
        serialize(n1, res);
        if (res != "{1{2{5,6},3,4}}")
            throw "5 test failed";
        
        root = deserialize(res);
        if (!compareTrees(n1, root))
            throw "5.2 test failed";

        // 6 test
        Node* n7 = new Node(7); n4->descendants.push_back(n7);
        Node* n8 = new Node(8); n4->descendants.push_back(n8);
        Node* n9 = new Node(9); n8->descendants.push_back(n9);
        
        serialize(n1, res);
        if (res != "{1{2{5,6},3,4{7,8{9}}}}")
            throw "6 test failed";
        
        root = deserialize(res);
        if (!compareTrees(n1, root))
            throw "6.2 test failed";

        cout << "All test successfull\n";
        
    } catch(char const * err) {
        cout << err << endl;
    }
    
    return 0;
}


