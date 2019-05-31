/**
 * Solution for Daily Coding Problem 57
 * 
 * Problem Description:
 * 
 * This problem was asked by Amazon.
 * 
 * Given a string s and an integer k, break up the string into multiple lines such that each line has a length of k or less. You must break it up so that words don't break across lines. Each line has to have the maximum possible amount of words. If there's no way to break the text up, then return null.
 * 
 * You can assume that there are no spaces at the ends of the string and that there is exactly one space between each word.
 * 
 * For example, given the string "the quick brown fox jumps over the lazy dog" and k = 10, you should return: ["the quick", "brown fox", "jumps over", "the lazy", "dog"]. No string in the list has a length of more than 10.
 * 
 * @author [Mark May](https://github.com/markamay)
 * 
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//helper function, splits a string into individual words separated by spaces
void split(string str, vector<string> & splitResult) {
    if (str.empty()) {
        return;
    }

    size_t loc = str.find(' ');
    while (loc != string::npos) {
        splitResult.push_back(str.substr(0, loc));
        str.erase(0, loc + 1);

        loc = str.find(' ');
    }

    if (!str.empty())
        splitResult.push_back(str);
}

//splits a string into lines no more than k chars more line
//returns a pointer to a vector so I could return NULL if impossible
vector<string>* breakString(string str, size_t k) {
    vector<string> words;
    split(str, words);

    vector<string> * results = new vector<string>;
    string curLine;

    for (auto word : words) {
        if (word.size() > k) {
            delete results; //memory leaks are bad
            return NULL;
        }
        else if (curLine.empty()) {
            curLine = word;
        }
        else if (curLine.size() + word.size() + 1 > k) {
            results->push_back(curLine);
            curLine = word;
        }
        else {
            curLine += (" " + word);
        }
    }
    //makes sure the last line is in the results
    //checks if the line is empty in case the string was empty to begin with
    if (!curLine.empty())
        results->push_back(curLine);

    return results;
}

//test driver
int main() {
    string str;
    size_t k;

    cout << "Enter string to split." << endl;
    cout << ">";
    getline(cin, str);
    cout << "Enter max chars per line" << endl;
    cout << ">";
    cin >> k;

    vector<string> * results = breakString(str, k);

    if (results == NULL) {
        cout << "Unsplitable" << endl;
    }
    else {
        for (auto line : *results) {
            cout << line << endl;
        }
        cout << "Count: " << results->size() << endl;
    }

    return 0;
}