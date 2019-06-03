/**
 * Solution for Daily Coding Problem 117
 * 
 * Problem Description:
 * 
 * This problem was asked by Facebook.
 * Given a binary tree, return the level of the tree with minimum sum.
 * 
 * @author [Mark May](https://github.com/markamay)
 */
#include <iostream>
#include <queue>
using namespace std;

class Node {
    public:
    int data;
    Node * left;
    Node * right;

    Node (int initData, Node * initLeft = NULL, Node * initRight = NULL) {
        data = initData;
        left = initLeft;
        right = initRight;
    }
};

/**
 * Returns the level in a binary tree in which the sum of all
 * the nodes is at a minimum.
 * 
 * @param root is the pointer to the root of the binary tree
 * @return 0 if root is NULL, otherwise the level with the min sum
 *         is returned. 1 being the root level, 2 being its children, etc
 */
size_t minSumLevel(Node * root) {
    if (root == NULL) {
        return 0;
    }

    constexpr Node * END_LEVEL = NULL;
    queue<Node*> tree;  //used for breadth first search of the tree
    size_t minLevel = 1; 
    size_t minSum = root->data;
    size_t curSum = 0;
    size_t curLevel = 1;

    tree.push(root);
    tree.push(END_LEVEL);

    while (tree.size() > 1) {
        Node * curNode = tree.front();
        tree.pop();

        if (curNode == END_LEVEL) {
            if (curSum < minSum) {
                minSum = curSum;
                minLevel = curLevel;
            }

            curSum = 0;
            curLevel++;
            tree.push(END_LEVEL);
        }
        else {
            if (curNode->left != NULL)
                tree.push(curNode->left);
            if (curNode->right != NULL)
                tree.push(curNode->right);

            curSum += curNode->data;
        }
    }

    return minLevel;
}

//test driver
int main() {
    Node * treeA = new Node(50,
                    new Node(12),
                    new Node(73)
                    );
    Node * treeB = NULL;
    Node * treeC = new Node (500,
                        new Node(250,
                            new Node(32),
                            new Node(200,
                                new Node(900),
                                new Node(87)
                            )
                        ),
                        new Node(87,
                            new Node(1),
                            new Node(2)
                        )
                    );

    cout << "Should be 1: " << minSumLevel(treeA) << endl;
    cout << "Should be 0: " << minSumLevel(treeB) << endl;
    cout << "Should be 3: " << minSumLevel(treeC) << endl;

    return 0;
}