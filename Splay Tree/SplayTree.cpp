#include "SplayTree.h"

Node* SplayTree::createNode(Node *parent, int value) {
    return new Node{value, nullptr, nullptr, parent};
}

void SplayTree::leftRotate(Node* node){
    Node* rightNode = node->right, *rightLeftNode = rightNode->left;
    if(node == root)
        root = rightNode;
    else if(node == node->parent->right)
        node->parent->right = rightNode;
    else
        node->parent->left = rightNode;
    rightNode->parent = node->parent;
    rightNode->left = node;
    node->right = rightLeftNode;
    node->parent = rightNode;
    if(rightLeftNode)
        rightLeftNode->parent = node;
}
void SplayTree::rightRotate(Node* node){
    Node* leftNode = node->left, *leftRightNode = leftNode->right;
    if(node == root)
        root = leftNode;
    else if(node == node->parent->right)
        node->parent->right = leftNode;
    else
        node->parent->left = leftNode;
    leftNode->parent = node->parent;
    leftNode->right = node;
    node->left = leftRightNode;
    node->parent = leftNode;
    if(leftRightNode)
        leftRightNode->parent = node;
}

Node* SplayTree::search(int value) {
    splay(root, value);
    return root;
}

void SplayTree::deleteNode(int value) {
    splay(root, value);
    if(root->value != value){
        cout << "Value doesn't exists\n";
        return;
    }
    Node* leftSubtree = root->left, *rightSubtree = root->right;
    delete root;
    if(!leftSubtree)
        root = rightSubtree;
    else if(!rightSubtree)
        root = leftSubtree;
    else{
        leftSubtree->right = rightSubtree;
        root = leftSubtree;
        rightSubtree->parent = leftSubtree;
    }
    if(root)
        root->parent = nullptr;
    size--;
}

void SplayTree::insertNode(int value) {
    if(!root)
        root = createNode(nullptr, value);
    else{
        splay(root, value);
        Node *newNode;
        if (root->value > value) {
            newNode = new Node{value, root->left, root, nullptr};
            if (root->left)
                root->left->parent = newNode;
            root->left = nullptr;
        } else {
            newNode = new Node{value, root, root->right, nullptr};
            if (root->right)
                root->right->parent = newNode;
            root->right = nullptr;
        }
        root->parent = newNode;
        root = newNode;
    }
    size++;
}

void SplayTree::splay(Node *rootNode, int value) {
    Node* curr = rootNode;
    while(true){
        if(curr->value > value && curr->left) {
            curr = curr->left;
            continue;
        }else if(curr->value < value && curr->right) {
            curr = curr->right;
            continue;
        }
        break;
    }
    while(curr->parent){
        Node* gp = curr->parent->parent;
        if(gp && curr->parent == gp->left){
            if(curr == curr->parent->left)
                rightRotate(gp);
            else
                leftRotate(curr->parent);
            rightRotate(curr->parent);
        }else if(gp && curr->parent == gp->right){
            if(curr == curr->parent->right)
                leftRotate(gp);
            else
                rightRotate(curr->parent);
            leftRotate(curr->parent);
        }else if(curr == curr->parent->left)
            rightRotate(curr->parent);
        else
            leftRotate(curr->parent);
    }
}

void SplayTree::printTreeHelper(Node *node, string indent, bool isRight, ostream& ostream1) const {
    if(node){
        ostream1 << indent;
        if(isRight){
            ostream1 << "R----";
            indent += "   ";
        }else{
            ostream1 <<  "L----";
            indent += "|  ";
        }
        ostream1 << node->value << '\n';
        printTreeHelper(node->left, indent, false, ostream1);
        printTreeHelper(node->right, indent, true, ostream1);
    }
}

int SplayTree::height(int value) const {
    Node* searchedNode = searchNode(value);
    return searchedNode ? treeHeightHelper(searchedNode): -1;
}

int SplayTree::treeHeight() const{
    return treeHeightHelper(root) + 1;
}

int SplayTree::treeHeightHelper(Node *node) const{
    if(!node)
        return -1;
    return max(treeHeightHelper(node->left), treeHeightHelper(node->right)) + 1;
}

Node* SplayTree::searchNodeHelper(Node *node, int value) const {
    if(!node || node->value == value)
        return node;
    else if(node->value > value)
        return searchNodeHelper(node->left, value);
    else
        return searchNodeHelper(node->right, value);
}

Node* SplayTree::searchNode(int value) const{
    return searchNodeHelper(root, value);
}

bool SplayTree::isEmpty() const {
    return size == 0;
}

int SplayTree::depthHelper(Node *node, int value) const {
    if(!node)
        return -size;
    else if(node->value == value)
        return 0;
    return node->value > value ? depthHelper(node->left, value) + 1 : depthHelper(node->right, value) + 1;
}

int SplayTree::depth(int value) const{
    return depthHelper(root, value);
}

ostream& operator<<(ostream& ostream1, const SplayTree* splayTree){
    ostream1 << "Size: " << splayTree->size << '\n';
    if(splayTree->root)
        splayTree->printTreeHelper(splayTree->root, "", true, ostream1);
    else
        ostream1 << "Tree is empty\n";
    return ostream1;
}