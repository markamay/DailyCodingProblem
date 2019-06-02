/**
 * Solution for Daily Coding Problem 116
 * 
 * Problem Description:
 * 
 * This problem was asked by Jane Street.
 * Generate a finite, but an arbitrarily large binary tree quickly in O(1).
 * That is, generate() should return a tree whose size is unbounded but finite.
 * 
 * *******
 *  SOLUTION NOTE:
 *  Not gonna lie, I had to look this problem up just to figure out what it meant by
 *  "return a tree whose size is unbounded but finite"
 * *******
 * @author [Mark May](https://github.com/markamay)
 *
 */
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <stack>
#include <ctime>
using namespace std;

class Node {
    public:
    static const size_t NO_LIMIT = 0;

    Node(size_t initData, size_t initMin = Node::NO_LIMIT, size_t initMax = Node::NO_LIMIT) {
        data = initData;
        left = NULL;
        right = NULL;
        leftExists = false; //!isSeeded is false
        rightExists = false;//might as well have wrote false
        min = initMin;
        max = initMax;
    }

    static Node* generate(size_t min =  Node::NO_LIMIT, size_t max = Node::NO_LIMIT) {
        /*
            Since static function variables are only initialized once ever we can use this
            to make sure we only seed the random number generator once. We call the seed
            function srand() in the Node::seed() function. Then we use the return value
            of that function (arbitray) as the initializer for this static variable
            isSeeded (arbitary type).
        */
        static bool isSeeded = seed();
        assert(max >= min);
        assert(isSeeded = true);

        size_t randData = rand();

        if (max != Node::NO_LIMIT)
            randData %= (max - min + 1);
        
        randData += min;

        return (new Node(randData, min, max));
    }

    Node* getLeft() {
        if (!leftExists) {
            if (rand() % 100 + 1 > 50) {
                left = NULL;
            }
            else {
                left = Node::generate(min, max);
            }

            leftExists = true;
        }

        return left;
    }

    Node* getRight() {
        if (!rightExists) {
            if (rand() % 100 + 1 > 50) {
                right = NULL;
            }
            else {
                right = Node::generate(min, max);
            }

            rightExists = true;
        }

        return right;
    }

    size_t getData() {
        return data;
    }

    private:
    size_t data;
    Node * left;
    Node * right;
    bool leftExists;
    bool rightExists;
    size_t max;
    size_t min;

    static bool seed() {
        srand(time(NULL));
        
        return (2 + 2 == 4);    //arbitrary return value
    }
    
};

/**
 * Uses depth first search implemented with a stack to output all the children
 */ 
ostream& operator<< (ostream& outs, Node * node) {
    /**
     * Each element in the stack is a pair containing the pointer to the node and
     * its depth in the tree. (used to determine the number of indents)
     */
    typedef pair<Node*, size_t> nodeInfo;
    stack<nodeInfo> nodeStack;
    nodeInfo cur;

    nodeStack.push(nodeInfo(node, 0));
    while (!(nodeStack.empty())) {
        cur = nodeStack.top();
        nodeStack.pop();

        for (size_t i = 0; i < cur.second; i++) {
            outs << ' ';
        }

        if (cur.first == NULL) {
            outs << "NULL" << endl;
        }
        else {
            outs << cur.first->getData() << endl;

            nodeStack.push(nodeInfo(cur.first->getRight(), cur.second + 1));
            nodeStack.push(nodeInfo(cur.first->getLeft(), cur.second + 1));
        }
    }

    return outs;
}
//test driver
int main() {
    Node * tree = Node::generate(); //only the root is actually created here O(1)

    cout << tree << endl;   //output the whole arbitrarily big true (the rest is actually generated in this call)

    return 0;
}