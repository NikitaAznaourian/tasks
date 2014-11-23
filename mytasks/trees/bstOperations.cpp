class Node {
public:
    Node(int val) : id(val) {};
    int id;
    Node* left = nullptr, *right = nullptr, *parent = nullptr;
};

void treeInsert(Node*& root, Node* z) {
    if (!root) {
        root = z;
        return;
    }
    
    if (z->id >= root->id) {
        if (root->right) {
            treeInsert(root->right, z);
        } else {
            root->right = z;
            z->parent = root;
        }
    } else {
        if (root->left) {
            treeInsert(root->left, z);
        } else {
            root->left = z;
            z->parent = root;
        }
    }
    
    return;
}


int main() {

    return 0;
};
