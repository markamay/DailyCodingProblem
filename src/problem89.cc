/*

This problem was asked by LinkedIn.

Determine whether a tree is a valid binary search tree.

A binary search tree is a tree with two children, left and right, and satisfies the constraint that the key in the left child must be less than or equal to the root and the key in the right child must be greater than or equal to the root.

*/
#include <iostream>
#include <limits>
using namespace std;

const int INF = std::numeric_limits<int>::max();

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

bool isBST_helper(node * tree, int low, int high) {
    //base case: an empty tree trivially satisfies the bst invarient
    if (tree == NULL)
        return true;
    else if (tree->data < low || tree->data > high)
        return false;
    else
    {
        return (isBST_helper(tree->left, low, tree->data) &&
                isBST_helper(tree->right, tree->data, high));
    }
    
}

bool isBST (node * tree) {
    return isBST_helper(tree, -INF, INF);
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