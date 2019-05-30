/**
 * Solution for Daily Coding Problem 113
 * 
 * Problem Description:
 * 
 * This problem was asked by Google.
 * Given a string of words delimited by spaces, reverse the words in string. For example, given "hello world here", return "here world hello"
 * Follow-up: given a mutable string representation, can you perform this operation in-place?
 * 
 * @author [Mark May](https://github.com/markamay)
 */
#include <string>
#include <iostream>
using namespace std;

/**
 * Reverses the characters in a subsection of a string
 * 
 * @param[in/out] str The string being modified. Result is stored in place.
 * @param[in] start The index of the first character included in the reverse process
 * @param[out]end   The index of the last character included in the reverse process  
 * @return None
 */
void reverseString(string & str, size_t start, size_t end) {
    while (end > start) {
        swap(str[start], str[end]);
        start++;
        end--;
    }
}

/**
 * @brief Reverses the words in a string
 * The reverse is done in place by first reversing the string
 * completely (so all the words are backwards) and then reversing
 * each individual word.
 * 
 * @param str The string to be reversed with each word separated by a whitespace.
 *            Result is saved in this reference parameter
 * @return None
 */
void reverseWords(string & str) {
    reverseString(str, 0, str.size() - 1);

    size_t start = 0, end = str.find(' ');
    while (end != string::npos && start < str.size()) {
        reverseString(str, start, end - 1);
        start = end + 1;
        end = str.find(' ', start);
    }
    reverseString(str, start, str.size() - 1); //For the last word since there is no space at end
}

//test driver
int main(int argc, char **argv) {
    string str;
    if (argc > 1) {
        str = argv[1];
    }
    else { 
        cout << "Enter a string: ";
        getline(cin, str);
    }

    reverseWords(str);
    cout << str << endl;

    return 0;

}