/*
This problem was asked by Google.

Implement locking in a binary tree. A binary tree node can be locked or unlocked only if all of its descendants or ancestors are not locked.

Design a binary tree node class with the following methods:

is_locked, which returns whether the node is locked
lock, which attempts to lock the node. If it cannot be locked, then it should return false. Otherwise, it should lock it and return true.
unlock, which unlocks the node. If it cannot be unlocked, then it should return false. Otherwise, it should unlock it and return true.
You may augment the node to add parent pointers or any other property you would like. You may assume the class is used in a single-threaded program, so there is no need for actual locks or mutexes. Each method should run in O(h), where h is the height of the tree.
*/
#include <iostream>
using namespace std;

class lockingBinaryTreeNode {
    public:
    lockingBinaryTreeNode * parent;
    lockingBinaryTreeNode * left;
    lockingBinaryTreeNode * right;

    lockingBinaryTreeNode(int startVal) {
        data = startVal;
        isLockedStatus = false;
        lockedDescendents = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    lockingBinaryTreeNode* addLeft(int n) {
        if (left != NULL)
            left->setData(n);
        else {
            left = new lockingBinaryTreeNode(n);
            left->parent = this;
        }

        return left;
    }

    lockingBinaryTreeNode* addRight(int n) {
        if (right != NULL)
            right->setData(n);
        else {
            right = new lockingBinaryTreeNode(n);
            right->parent = this;
        }

        return right;
    }

    bool is_locked() {
        return isLockedStatus;
    }

    bool isModifiable() {
        if (lockedDescendents > 0)
            return false;
        
        lockingBinaryTreeNode * cur = parent;
        while (cur != NULL) {
            if (cur->is_locked())
                return false;
            
            cur = cur->parent;
        }

        return true;    //if no locks are found in ancestors then it must be modifiable
    }

    bool lock() {
        if (isLockedStatus)
            return true;    //is already locked, so lock successful

        if (!isModifiable())
            return false;
        
        isLockedStatus = true;

        //update all the ancestors since their descendent is now locked
        lockingBinaryTreeNode * cur = parent;
        while(cur != NULL) {
            cur->lockedDescendents++;
            cur = cur->parent;
        }

        return true;

    }

    bool unlock() {
        if (!isLockedStatus)
            return true;    //success since we are already at desired state

        if (!isModifiable())
            return false;

        isLockedStatus = false;

        //update all the ancestors since their descendent is now locked
        lockingBinaryTreeNode * cur = parent;
        while(cur != NULL) {
            cur->lockedDescendents--;
            cur = cur->parent;
        }

        return true;
    }

    bool setData(int newData) {
        if (!isLockedStatus) {
            data = newData;
            return true;
        }
        else
            return false;
    }

    int getData() {
        return data;
    }
    private:
    bool isLockedStatus;
    int data;
    int lockedDescendents;  //keeps track of number of locked descendents
};

int main() {
    lockingBinaryTreeNode * bst = new lockingBinaryTreeNode(1);
    lockingBinaryTreeNode * cur = bst->addLeft(2);
    cur = cur->addLeft(3);
    cur->addLeft(4);
    cur->addRight(5);
    cur = cur->parent;
    cur->addRight(7);
    bst->addRight(12);

    return 0;
}