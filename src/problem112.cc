/*
*
*    Author: Mark May (markamay@live.com)
*    Date: 5/29/2019
*
*    Problem Description:
*        This problem was asked by Twitter.
*        Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree. Assume that each node in the tree also has a pointer to its parent.
*        According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
*
*/
#include <iostream>
using namespace std;

/*
    Represents an individual node in a binary tree.
    Each node should have pointers to their own children,
    and per the problem description a pointer to its parent.
*/
class node {
    public:
    node(int n) {
        data = n;
        lChild = NULL;
        rChild = NULL;
        parent = NULL;
    }

    void pushLeft(int n) {
        lChild = new node(n);
        lChild->parent = this;
    }
    void pushRight(int n) {
        rChild = new node(n);
        lChild->parent = this;
    }

    int data;
    node * lChild;
    node * rChild;
    node * parent;
};

int depth(node * a) {
    int curDepth = 0;

    while (a != NULL) {
        a = a->parent;
        curDepth++;
    }

    return curDepth;
}

//returns NULL is a and b have no common ancestors
//returns the LCA of nodes a and b
node* lca(node * a, node * b) {
    //if a or b are NULL then no LCA is possible
    if (a == NULL || b == NULL) {
        return NULL;
    }

    int aDepth = depth(a);
    int bDepth = depth(b);
    //cout << "Depth A: " << aDepth << endl;
    //cout << "Depth B: " << bDepth << endl;

    //traverse up from a and b until we find ancestors that are
    //at the same depth in the tree (since we know no ancestor exists
    //below the the depths of a and b)
    while(aDepth > bDepth) {
        a = a->parent;
        aDepth--;
    }
    while (bDepth > aDepth) {
        b = b->parent;
        bDepth--;
    }

    /*
        Once a and b are at the same depth in the tree then
        we keep traversing higher in the tree until we find
        a depth in which a and b are equal (or until we reach the root)
    */
    while (a != b && a != NULL && b != NULL) {
        a = a->parent;
        b = b->parent;
    }

    return a;
}

//test driver
int main() {
    node* root = new node(1);
    root->pushLeft(2);
    root->pushRight(3);
    node* cur = root->lChild;
    cur->pushLeft(4);
    cur->pushRight(5);
    cur = root->rChild;
    cur->pushLeft(6);
    cur->pushRight(7);
    cur = root->lChild->lChild;
    cur->pushLeft(8);
    cur->pushRight(9);
    cur = cur->parent->rChild;
    cur->pushLeft(10);
    cur->pushRight(11);
    cur = root->rChild->lChild;
    cur->pushLeft(12);
    cur->pushRight(13);
    cur = cur->parent->rChild;
    cur->pushLeft(14);
    cur->pushRight(15);

    cur = lca(root, root->lChild->lChild->lChild);
    cout << ((cur == NULL) ? 0 : cur->data) << endl;

    return 0;


}
