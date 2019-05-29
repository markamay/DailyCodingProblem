/*
This problem was asked by Dropbox.

Given the root to a binary search tree, find the second largest node in the tree.
*/
#include <iostream>
#include <vector>
using namespace std;

class BST_Node {
    public:
    BST_Node(int n) {
        data = n;
        left = NULL;
        right = NULL;
    }

    int data;
    BST_Node * left;
    BST_Node * right;
};

void inOrderTraversal(BST_Node * cur, vector<int> & sortedList) {
    if (cur == NULL)
        return;
    
    inOrderTraversal(cur->left, sortedList);
    sortedList.push_back(cur->data);
    inOrderTraversal(cur->right, sortedList);
}

int getSecondLarget(BST_Node * root) {
    vector<int> sortedList;
    inOrderTraversal(root, sortedList);

    if (sortedList.size() >= 2)
        return sortedList[sortedList.size() - 2];
    else
    {
        return 0; 
    }
}

//driver
int main() {
    BST_Node* root = new BST_Node(10);
    root->left = new BST_Node(5);
    root->left->left = new BST_Node(2);
    root->left->right = new BST_Node (7);
    root->right = new BST_Node(500);
    root->right->left = new BST_Node(150);
    root->right->right = new BST_Node (600);

    cout << getSecondLarget(root) << endl;

    return 0;
}