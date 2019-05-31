/**
 * Solution for Daily Coding Problem 25
 * 
 * Problem Description:
 * 
 * This problem was asked by Facebook.
 *
 *    Implement regular expression matching with the following special characters:
 *
 *    . (period) which matches any single character
 *    * (asterisk) which matches zero or more of the preceding element
 *     That is, implement a function that takes in a string and a valid regular expression and returns whether or not the string matches the regular expression.
 *
 *   For example, given the regular expression "ra." and the string "ray", your function should return true. The same regular expression on the string "raymond" should return false.
 *
 *   Given the regular expression ".*at" and the string "chat", your function should return true. The same regular expression on the string "chats" should return false.
 * 
 * 
 */
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

bool match(string str, string re) {
    if (re.empty()) {
        return str.empty(); //an empty regular expression can only match an empty string
    }
    if (str.empty()) {
        if (re[0] != '*')
            return false;
        else
        {
            return match(str, re.substr(1));
        }
    }
    else if(re[0] == '.') {
        return match(str.substr(1), re.substr(1));
    }
    else if(re[0] == '*') {
        return (match(str.substr(1), re) || match(str, re.substr(1)));
    }
    else {
        return (re[0] == str[0] && match(str.substr(1), re.substr(1)));
    }
}

void unitTests() {
    //each tuple is a test
    //{RE, stringToMatch, expectedAnswer}
    const vector<tuple<string, string, bool> > tests({
        {"cat", "cat", true},
        {".at", "cat", true},
        {".at", "bat", true},
        {"cat", "bat", false},
        {".", "h", true},
        {".", "hh", false},
        {"....", "shoe", true},
        {"....", "notshoe", false},
        {"*", "anything", true},
        {"*", "", true},
        {"*at", "at", true},
        {"*at", "cat", true},
        {"*at", "cata", false},
        {"*at.", "cata", true},
        {"*ata*", "ata", true},
        {"*ata*", "shoe atatatata", true},
        {"p*.", "pie", true},
        {"p*.","p", false}
    });
    
    for (auto [re, str, answer] : tests) {
        if (match(str, re) != answer) {
            cout << "Failed: ";
        }
        else
        {
            cout << "Passed: ";
        }
        cout << "re=\"" << re << "\", str=\"" << str << "\" ans=" << (answer ? "true" : "false") << endl;
        
    }
}
//simple test driver
int main(int argc, char **argv) {
    //super secret test mode
    if (argc == 2 && (string(argv[1]) == string("-t"))) {
        unitTests();
        return 0;
    }
    if (argc < 3) {
        cout << "ERROR: Missing command line arguments." << endl << endl;
        cout << "First argument:  regular expression" << endl;
        cout << "Second argument: string to check" << endl;

        return 1;
    }

    if (match(argv[2], argv[1]))
        cout << "Is a match!" << endl;
    else
    {
        cout << "Not a match!" << endl;
    }

    return 0;   
}