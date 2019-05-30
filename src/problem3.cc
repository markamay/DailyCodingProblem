/**
 * Solution for Daily Coding Problem 3
 * 
 * Note: This can be done much simpler than the way I did it, I just wanted to try something fun.
 * 
 * Problem Description:
 * 
 *    This problem was asked by Google.
 *
 *    Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, and deserialize(s), which deserializes the string back into the tree.
 *
 *    For example, given the following Node class
 *
 *    class Node:
 *        def __init__(self, val, left=None, right=None):
 *            self.val = val
 *            self.left = left
 *            self.right = right
 *    The following test should pass:
 *
 *    node = Node('root', Node('left', Node('left.left')), Node('right'))
 *    assert deserialize(serialize(node)).left.left.val == 'left.left'
 *
 * @author [Mark May](https://github.com/markamay)
 *
 */
#include <iostream>
#include <string>
#include <stack>
using namespace std;

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

//test driver
int main() {
    Node * root = new Node("this is a test", 
                          new Node("I hope it works", new Node("please"), new Node("please please")),
                          new Node("right node"));
    typedef Serializer srl;

    if (srl::deserialize(srl::serialize(root))->left->left->val == string("please"))
        cout << "Success!" << endl;
    else
    {
        cout << "Failure!" << endl; //shouldn't happen because I said please
    }
    
    return 0;
}