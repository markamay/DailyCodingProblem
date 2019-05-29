/*

This problem was asked by LinkedIn.

Determine whether a tree is a valid binary search tree.

A binary search tree is a tree with two children, left and right, and satisfies the constraint that the key in the left child must be less than or equal to the root and the key in the right child must be greater than or equal to the root.

*/
#include <iostream>
using namespace std;

//Simple implement of a binary tree node
class node {
    public:
    node(int n) {
        data = n;
        left = NULL;
        right = NULL;
    }

    int data;
    node * left;
    node * right;
};

//a binary search tree satisfies:
//-the root is greater than its left child
//-the root is smaller than its right child
//-the left and right child are both valid binary search trees
//
//Therefore we can easily verify the first two requirements and then
//recursively check the left and right child to see if they satisfy the 
//requirements
bool isBST (node * tree) {
    //base case: an empty tree trivially satisfies the bst invarient
    if (tree == NULL)
        return true;
    else if (tree->left != NULL && tree->left->data > tree->data)
        return false;
    else if (tree->right != NULL && tree->right->data < tree->data)
        return false;
    else
    {
        return (isBST(tree->left) && isBST(tree->right));
    }
    
}

//test driver
int main() {
    node* root = new node(10);
    root->left = new node(5);
    root->left->left = new node(2);
    root->left->right = new node (7);
    root->right = new node(500);
    root->right->left = new node(150);
    root->right->right = new node (600);

    cout << (isBST(root) ? "IS BST" : "IS NOT BST") << endl;

    return 0;
}