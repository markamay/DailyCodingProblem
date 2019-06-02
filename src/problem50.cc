/**
 * Solution for Daily Coding Problem 50
 * 
 * Problem Description:
 * 
 * This problem was asked by Microsoft.
 *
 * Suppose an arithmetic expression is given as a binary tree. Each leaf is an integer and each internal node is one of '+', '−', '∗', or '/'.
 * 
 * Given the root to such a tree, write a function to evaluate it.
 * 
 * For example, given the following tree:
 * 
 *     *
 *    / \
 *   +    +
 *  / \  / \
 * 3  2  4  5
 * You should return 45, as it is (3 + 2) * (4 + 5).
 * 
 * @author [Mark May](https://github.com/markamay)
 * 
 */
#include <iostream>
#include <assert.h>
#include <stack>
#include <string>
using namespace std;

/**
 * @class Node 
 * 
 * Represents a Node in our binary tree represenation of a mathematical expression.
 * A node can either be a leaf, which should be an integer.
 * Or it can be a math operator (in which case it should have two leaves)
 * 
 */
class Node {
    public:
    Node * left;
    Node * right;

    enum class operation { PLUS = '+', MINUS = '-', TIMES = '*', DIVIDE = '/'};

    Node(int data, Node * setLeft = NULL, Node * setRight = NULL) {
        isLeaf = true;
        num = data;
        left = setLeft;
        right = setRight;
    }

    Node(operation setOp, Node * setLeft = NULL, Node * setRight = NULL) {
        isLeaf = false;
        op = setOp;
        left = setLeft;
        right = setRight;
    }

    int data() {
        if (isLeaf)
            return num;
        else
            return (static_cast<int>(op));
    }

    bool isValid() {
        if (isLeaf)
            return (left == NULL && right == NULL);
        else if (left == NULL || right == NULL)
            return false;
        else
            return (left->isValid() && right->isValid());
    }

    bool leaf() {
        return isLeaf;
    }

    int evaluate_helper() {
        if (isLeaf)
            return num;
        else {
            switch (op) {
                case operation::PLUS:
                    return (left->evaluate_helper() + right->evaluate_helper());
                case operation::MINUS:
                    return (left->evaluate_helper() - right->evaluate_helper());
                case operation::DIVIDE:
                    return (left->evaluate_helper() / right->evaluate_helper());
                case operation::TIMES:
                    return (left->evaluate_helper() * right->evaluate_helper());
                default:
                    throw "THIS ISN'T HUMANLY POSSIBLE";
            }
        }
    }

    int evaluate() {
        assert(isValid());

        return (evaluate_helper());
    }

    private:
    int num;
    operation op;
    bool isLeaf;
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
            outs << '\t';
        }

        if (cur.first == NULL) {
            outs << "NULL" << endl;
        }
        else {
            outs << cur.first->val << endl;

            nodeStack.push(nodeInfo(cur.first->right, cur.second + 1));
            nodeStack.push(nodeInfo(cur.first->left, cur.second + 1));
        }
    }

    return outs;
}
//test driver
int main() {
    typedef Node::operation op;

    Node * expr = new Node(op::PLUS,
                    new Node(50),
                    new Node(op::DIVIDE,
                        new Node(20),
                        new Node (4)
                    ) 
                );
    
    cout << "should be 55: " << expr->evaluate() << endl;

    return 0;
}