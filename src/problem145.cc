/**
 * Solution for Daily Coding Problem 145
 * 
 * Problem Description:
 * 
 * This is your coding interview problem for today.
 * This problem was asked by Google.
 * Given the head of a singly linked list, swap every two nodes and return its head.
 * For example, given 1 -> 2 -> 3 -> 4, return 2 -> 1 -> 4 -> 3.
 * 
 * @author [Mark May](https://github.com/markamay)
 */
#include <iostream>
using namespace std;

class ListNode {

public:
    ListNode(int d = 0, ListNode * n = NULL) {
        data = d;
        next = n;
    }

    int getData() { return data; }
    ListNode* getNext() { return next; }
    
    void setNext(ListNode* n) { next = n; }
    void setData(int d) { data = d; }

    friend ostream& operator<< (ostream& outS, ListNode* l) {
        while (l != NULL) {
            outS << l->data << " ";
            l = l->next;
        }
        return outS;
    }
private:
  int data;
  ListNode * next;  
};

ListNode* swapEveryTwoNodes(ListNode* curNode) {
    //base case 1: current node is NULL
    if (curNode == NULL)
        return NULL;
    //base case 2: there is only one node left
    else if (curNode->getNext() == NULL)
        return curNode;
    else {
        ListNode* newFirst = curNode->getNext();
        ListNode* newSecond = curNode;
        ListNode* newTail = swapEveryTwoNodes(curNode->getNext()->getNext());

        newFirst->setNext(newSecond);
        newSecond->setNext(newTail);

        return newFirst;
    }
}

//test driver main function
int main() {
    ListNode* head = new ListNode(0, 
                        new ListNode(1, 
                        new ListNode(2, 
                        new ListNode(3,
                        new ListNode(4,
                        new ListNode(5,
                        new ListNode(6,
                        new ListNode(7,
                        new ListNode(8
                        )))))))));

    cout << "Before swap: " << head << endl;
    
    head = swapEveryTwoNodes(head);

    cout << "After swap:  " << head << endl;

    return 0;
}