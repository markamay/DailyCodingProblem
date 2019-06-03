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
#include <string>
using namespace std;

//Base class for a node in our binary tree
class ArithNode {
    public:
    virtual string data()  = 0;
    virtual string to_string() = 0;
    virtual int evaluate() = 0;
};

class ArithOperationNode : public ArithNode {
    public:
    ArithNode * left;
    ArithNode * right;

    enum class Operation { PLUS = '+', MINUS = '-', TIMES = '*', DIVIDE = '/' };

    ArithOperationNode(Operation initOp, ArithNode * initLeft = NULL, ArithNode * initRight = NULL) {
        op = initOp;
        left = initLeft;
        right = initRight;
    }

    string to_string() {
        return ("(" + left->to_string() + " " + data() + " " + right->to_string() + ")");
    }

    string data() {
        //looks funky, but this returns a char array which can be used to
        //create a string from one of the string's constructors
        return {static_cast<char>(op)};
    }

    int evaluate() {
        assert(left != NULL);
        assert(right != NULL);

        switch (op) {
            case Operation::PLUS:
                return (left->evaluate() + right->evaluate());
            case Operation::MINUS:
                return (left->evaluate() - right->evaluate());
            case Operation::DIVIDE:
                return (left->evaluate() / right->evaluate()); 
            case Operation::TIMES:
                return (left->evaluate() * right->evaluate());
        }

        return -1; //not really gonna ever trigger
    }

    private:
    Operation op;
};

class ArithIntegerNode : public ArithNode {
    public:
    ArithIntegerNode(int initVal) : val(initVal) { };

    int evaluate() { return val; }

    string to_string() {
        return data();
    }

    string data() { return std::to_string(val); }

    private:
    int val;
};

ArithNode* Arith(int nodeValue) {
    return (new ArithIntegerNode(nodeValue));
}

ArithNode* Arith(ArithOperationNode::Operation op, ArithNode* left, ArithNode* right) {
    return (new ArithOperationNode(op, left, right));
}

//test driver
int main() {
    typedef ArithOperationNode::Operation OP;
    ArithNode* tree = Arith(OP::PLUS, 
                        Arith(OP::TIMES,
                            Arith(50),
                            Arith(2)
                            ),
                        Arith(OP::MINUS,
                            Arith(25),
                            Arith(OP::DIVIDE,
                                Arith(30),
                                Arith(6)
                                )
                            )
                        );
    
    cout << "Should be 120: " << endl;
    cout << tree->to_string() << " = " << tree->evaluate() << endl;

    return 0;
}