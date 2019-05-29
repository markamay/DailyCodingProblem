/*
This problem was asked by Google.

The power set of a set is the set of all its subsets. Write a function that, given a set, generates its power set.

For example, given the set {1, 2, 3}, it should return {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}.

You may also use a list or array to represent a set.
*/
#include <iostream>
#include <vector>
using namespace std;

template<class T>
void powerSetGenerator(vector<T> & orig, vector<vector<T> > & solution) {
    solution.push_back(vector<T>()); //pushback the emptyset to start

    for (size_t i = 0; i < orig.size(); i++) {
        size_t curSize = solution.size();
        for (size_t j = 0; j < curSize; j++) {
            vector<T> newSet = solution[j];
            newSet.push_back(orig[i]);
            solution.push_back(newSet);
        }
    }
}

int main() {
    vector<int> mySet;
    for (size_t i = 0; i < 3; i++) {
        mySet.push_back(i);
    }

    vector<vector<int> > powerSet;
    powerSetGenerator<int>(mySet, powerSet);
    cout << "--------------" << endl;
    cout << "Sets (size=" << powerSet.size() << ")" << endl;
    cout << "--------------" << endl;
    for (size_t i = 0; i < powerSet.size(); i++) {
        cout << "{ ";
        for (size_t j = 0; j < powerSet[i].size(); j++) {
            cout << powerSet[i][j] << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}