/*
This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
*/
#include <unordered_set>
#include <iostream>
#include <vector>
using namespace std;

bool subsetSumTwo(vector<int> & inputList, int sum) {
    if (inputList.size() < 2)
        return false;

    unordered_set<int> visited;

    for (vector<int>::iterator it = inputList.begin(); it != inputList.end(); it++) {
        int goal = sum - *it;
        if (visited.find(goal) != visited.end())    //O(1) to try to find the needed value
            return true;
    
        visited.insert(*it);
    }

    return false;
}

int main() {
    vector<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    a.push_back(7);
    a.push_back(9);

    cout << "Should be false: " << subsetSumTwo(a, 13) << endl;
    cout << "Should be true:  " << subsetSumTwo(a, 12) << endl;

    return 0;
}