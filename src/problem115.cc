/**
 * Solution for Daily Coding Problem 115
 * 
 * Problem Description:
 * 
 * This problem was asked by Google.
 * Given two non-empty binary trees s and t, check whether tree t has exactly the same 
 * structure and node values with a subtree of s. 
 * 
 * A subtree of s is a tree consists of a node in s and all of this node's descendants. 
 * The tree s could also be considered as a subtree of itself.
 * 
 * *****************
 *  Two different solutions are given.
 *  First one (wrapped in namespace "SolutionA") uses a serializer class that I wrote
 *  for Problem 3 to serialize s and t into strings. Then I can use the std::string::find()
 *  method to see if t serialized is within s serialized.
 * 
 * Second one (wrapped in namespace "SolutionB") recurisvely checks if s == t or if t is a subtree
 * of one of the children of s.
 * 
 * *****************
 * @author [Mark May](https://github.com/markamay)
 *
 */
#include <iostream>
#include <stack>
#include <string>
using namespace std;

/*******************
 * Note: The following Node class and Serializer class was used in my solution for problem #3.
********************/ 

/**
 * @class Node
 * 
 * Represents a node in a binary tree of strings
 */
class Node {
    public:
    string val;
    Node * left;
    Node * right;

    Node(string initVal, Node * initLeft = NULL, Node * initRight = NULL) {
        val = initVal;
        left = initLeft;
        right = initRight;
    }

    /**
     * Overloaded insertion operator (<<) to output a Node pointer
     * 
     * Will output the root, followed by its left child followed by its children
     * followed by the right child followed by its children. Each node is on its
     * own line and is indented one more tab from its parent. Siblings should be at
     * the indentation level. If a node is NULL then "NULL" is outputted in place
     * of the child's value
     * 
     * Ex:
     * 
     *  root
     *      leftChild
     *          leftChild's LeftChild
     *              ...
     *          leftChild's RightChild
     *              ...
     *      rightChild
     *          rightChild's LeftChild
     *              ...
     *          rightChild's RightChild
     *              ...
     * 
     * @param outs The stream to be outputted to
     *        node The node being outputted
     * @return outs
     */
    friend ostream& operator<< (ostream& outs, Node * node);
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

/**
 * @class Serializer
 * 
 * @brief Wrapper for the serialize and the deserialize functions
 * 
 * The Node class's serialize and deserialize function are declared statically here to
 * delimit scope and to 'hide' the helper functions which are declared private here.
 * The Serializer class has no member variables and all functions are static so there
 * is no need to declare a Serializer object. namespaces could have also been used instead
 * but I wanted to try something more 'java'-esque this time around.
 * The functions would work just find without being wrapped in the class.
 */
class Serializer {
    public:
    /**
     * Returns the inputted node as a serialized string in a format
     * similar to json.
     * 
     * @param root The pointer to the node to be serialized.
     * @return A string containing all necessary information about a node in the format:
     *      {"data": {"size": length_of_data, "data": "root's data"}, 
     *          "left"  : {"size" : length_of_serialized_left_child,
     *                      "data" :
     *                     {"data" : "left child's data",
     *                      "left" : ...,
     *                      "right": ...
     *                      } 
     *                      },
     *          "right" : {"size" : length_of_serialized_right_child,
     *                      "data" :
     *                     {"data" : "right child's data",
     *                      "left" : ...,
     *                      "right": ...,   
     *                      }
     *                    },
     *          }
     *      }
     * 
     *     If a node is NULL then "{}" will be returned for its data
     */
    static string serialize(Node* root) {
        if (root == NULL)
            return "{}";
        else {
            string leftSerialized  = serializeChildNode(root->left);
            string rightSerialized = serializeChildNode(root->right);
            string result = "{"
                + serializeKeyValue("data", serializeString(root->val)) + ", "
                + serializeKeyValue("left",  leftSerialized) + ", "
                + serializeKeyValue("right", rightSerialized)
                + "}";
            return result;
        }
    }
    /**
     *  Takes a string created by the serialize function above and creates
     *  the original tree.
     * 
     *  @params serializedNode The tree represented as a string (format must be same
     *                          as described in the documentation for the serialize function) 
     *  @returns The pointer to the root of the reconstructed tree
     */
    static Node* deserialize(string serializedNode) {
        if (serializedNode == "{}") {
            return NULL;
        }
        else {
            string nodeData = parseNodeData(serializedNode);
            string leftNodeSerialized  = parseNodeData(serializedNode);
            string rightNodeSerialized = parseNodeData(serializedNode);

            Node* result = new Node(nodeData, 
                                    deserialize(leftNodeSerialized),
                                    deserialize(rightNodeSerialized));

            return result;
        }
    }

    private:
    /**
     * Serializes a child node by calling the serialize function on the node
     * and concatenating that with the size of the resulting string.
     * 
     * @param childNode The desired node to be serialized
     * @return The serialized node
     */
    static string serializeChildNode(Node * childNode) {
        string serializedData = serialize(childNode);
        size_t size = serializedData.size();

        return ("{" 
                    + serializeKeyValue("size", to_string(size)) + ", "
                    + serializeKeyValue("data", serializedData) + ", "
                    + 
                "}"
        );
    }

    /**
     * Parses out the first bit of avaiable data in a serialized string
     * using the size provided in the string. The retrieved data is erased
     * from the passed in string.
     * 
     * @param curNode The remaining part of the serialized string. The next key in the string
     *                should be the "size" of some attribute, followed by the attribute.
     * @return The first "data" substring available in curNode
     */
    static string parseNodeData(string & curNode) {
        size_t loc = curNode.find("size", 0);       //get the start of the key for the size data
        loc = curNode.find("\"", loc + 5) + 1;      //gets the start of the size value
        size_t endLoc = curNode.find("\"", loc);    //gets the end of the size value
        size_t dataSize = stoi(curNode.substr(loc, endLoc - loc));  //extracts the size as uint
        
         loc = curNode.find("data", endLoc);  //similar process as above
         loc = curNode.find("\"", loc + 5) + 1;
         string nodeData = curNode.substr(loc, dataSize);
         curNode.erase(0, loc + dataSize + 1);      //remove the already parsed data

         return nodeData;
    }

    /**
     * Adds quotation marks to the start and end of a string
     * 
     * @param data The string you want in quotation marks
     * @return The data string wrapped in quotation marks
     */
    static string inQuotes(string data) {
        data = "\"" + data + "\"";
        return data;
    }

    /**
     * Returns the serialization of [key] mapped to [value]
     * 
     * @param key The key/descriptor of the data
     * @param value The value/data being stored
     * @return The string:
     *     "[key] : [value]"
     */
    static string serializeKeyValue(string key, string value) {
        return (inQuotes(key) + ":" + inQuotes(value));
    }

    /**
     * Takes a string and serializes it for use with our Node serializer.
     * To avoid having to deal with escaping control characters like quotes
     * the serialized string will include the size of the string so that 
     * when we encounter a string in our object we don't have to look at the
     * characters to find the end, just count from the start to the end.
     * 
     * @param data The string to be serialized
     * @return The serialized string in the format:
     *    {"size": "$(data.size())", "data": "$(data)"} 
     */
    static string serializeString(string data) {
        string result = "{"
            + serializeKeyValue("size", to_string(data.size())) + ", "
            + serializeKeyValue("data", data)
            + "}";
        return result;
    }
};

namespace SolutionA {
    /**
    * Checks if a Node [t] is a subtree of Node [s].
    * 
    * @param s is a pointer to the main tree/Node
    * @param t is a pointer to the possible subtree of s
    *  
    * @return true if s and t are exactly equal
    * @return true if t is a subtree of s->left or s->right
    * @return false if s is NULL but t is not NULL
    */
    bool isSubTree(Node * s, Node * t) {
        Serializer serial;

        string s_serialized = serial.serialize(s);
        string t_serialized = serial.serialize(t);

        return (s_serialized.find(t_serialized) != string::npos);
    }

};

namespace SolutionB {
    /**
     * Overloaded function determining if two trees are equal
     * 
     * @param lhs is the node at the left side of the equality operator
     *        rhs is the node at the right side of the equality operator
     * 
     * @return true if lhs and rhs both have the same data value and
     *         lhs and rhs's left and right subtrees are equal
     * @return false if lhs and rhs have different data values or if 
     *         one of the nodes has a NULL child and for that same child
     *         the other node isn't NULL
     */
    bool operator==(Node lhs, Node rhs) {
        if (lhs.val != rhs.val)
            return false;
        else if ((lhs.left == NULL) xor (rhs.left == NULL)) {
            return false; //if only one of the node's left tree is NULL then the nodes can't be equal
        }
        else if ((lhs.right == NULL) xor (rhs.right == NULL)) {
            return false; //same though process as for the left trees except for the right tree
        }
        else {
            bool leftSideEqual  = (lhs.left == NULL) || (*(lhs.left) == *(rhs.left));
            bool rightSideEqual = (lhs.right == NULL) || (*(lhs.right) == *(rhs.right));

            return (leftSideEqual && rightSideEqual);
        }
    }

    /**
     * Checks if a Node [t] is a subtree of Node [s].
     * 
     * @param s is a pointer to the main tree/Node
     * @param t is a pointer to the possible subtree of s
     *  
     * @return true if s and t are exactly equal
     * @return true if t is a subtree of s->left or s->right
     * @return false if s is NULL but t is not NULL
     */
    bool isSubTree(Node * s, Node * t) {
        //an empty tree we will consider a subset of any tree
        if (t == NULL) 
            return true;
        //if s is NULL then t can only be a subset if t is NULL but we already checked that case
        else if (s == NULL) 
            return false;
        //t is a subtree of s if s and t are equal
        else if (*s == *t) 
            return true;
        //t is a subtree of s if t is a subtree of one of s's children
        else {
            return (isSubTree(s->left, t) || isSubTree(s->right, t));
        }
    }
}

//test driver
int main(int argc, char **argv) {
    Node * a = new Node("root", 
                    new Node("leftTree",
                        new Node("leftleftTree",
                            new Node("leftleftleftTree"),
                            new Node ("leftleftrightTree")
                        )
                    ), 
                    new Node("rightTree",
                        NULL,
                        new Node("rightrightTree")
                    )
                );
    Node * b = new Node("leftleftTree",
                    new Node("leftleftleftTree"),
                    new Node ("leftleftrightTree")
                );
    Node * c = new Node("rightTree");

    cout << "\nUsing Serializer method: " << endl;
    {
    using namespace SolutionA;
    cout << "Should be true:  " << isSubTree(a, b) << endl;
    cout << "Should be false: " << isSubTree(b, c) << endl;
    cout << "Should be true:  " << isSubTree(a, a) << endl;
    cout << "Should be false: " << isSubTree(NULL, a) << endl;
    }

    cout << "\nUsing recursive method: " << endl;
    {
    using namespace SolutionB;
    cout << "Should be true:  " << isSubTree(a, b) << endl;
    cout << "Should be false: " << isSubTree(b, c) << endl;
    cout << "Should be true:  " << isSubTree(a, a) << endl;
    cout << "Should be false: " << isSubTree(NULL, a) << endl;
    }

    return 0;
}