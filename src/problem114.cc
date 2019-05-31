/**
 * Solution for Daily Coding Problem 114
 * 
 * Problem Description:
 * 
 * This problem was asked by Facebook.
 * Given a string and a set of delimiters, reverse the words in the string while maintaining the relative order of the delimiters. 
 * For example, given "hello/world:here", return "here/world:hello"
 * Follow-up: Does your solution work for the following cases: "hello/world:here/", "hello//world:here"
 * 
 * @author [Mark May](https://github.com/markamay)
 */
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
using namespace std;

size_t findDelimiters(string str, unordered_set<char> & delimiters) {
    for (size_t i = 0; i < str.size(); i++) {
        if (delimiters.find(str[i]) != delimiters.end())
            return i;
    }
    return string::npos;
}

string reverseWords(string str, unordered_set<char> delimiters) {
    stack<string> wordList;
    queue<string> delimiterList;
    string results;
    size_t loc = 0;

    if (str.empty())
        return str;
    
    while (delimiters.find(str[0]) != delimiters.end() && !str.empty()) {
        results += str[0];
        str.erase(0, 1);
    }

    loc = findDelimiters(str, delimiters);
    while (loc != string::npos) {
        wordList.push(str.substr(0, loc));
        str.erase(0, loc);

        loc = 1;
        while ((loc < str.size()) && (delimiters.find(str[loc]) != delimiters.end())) {
            loc++;
        };
        delimiterList.push(str.substr(0, loc));
        str.erase(0, loc);

        loc = findDelimiters(str, delimiters);
    }

    if (!str.empty()) {
        wordList.push(str);
    }

    while (!wordList.empty()) {
        results += wordList.top();
        wordList.pop();
        if (!delimiterList.empty())  {
            results += delimiterList.front();
            delimiterList.pop();
        }
    }

    if (!delimiterList.empty())
        results += delimiterList.front();

    return results;
}

//test driver
int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "ERROR: Enter string to reverse and the delimiter characters (as 1 string) at the command line" << endl;
        return 1;
    }

    string delimiters = argv[2];

    unordered_set<char> delimiterList;
    for (auto ch : delimiters) {
        delimiterList.insert(ch);
    }

    cout << reverseWords(argv[1], delimiterList) << endl;

    return 0;
}
