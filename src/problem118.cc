/**
 * Solution for Daily Coding Problem 118
 * 
 * Problem Description:
 * 
 * This problem was asked by Google.
 * Given a sorted list of integers, square the elements and give the output in sorted order.
 * For example, given [-9, -2, 0, 2, 3], return [0, 4, 4, 9, 81].
 * 
 * @author [Mark May](https://github.com/markamay)
 * 
 */
#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
using namespace std;

void outputVector(vector<int> * a) {
    for (vector<int>::iterator it = a->begin(); it != a->end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

vector<int>* merge(vector<int>* a, vector<int>* b) {
    assert(a != NULL);
    assert(b != NULL);

    vector<int> * newList = new vector<int>;
    vector<int>::reverse_iterator itA = a->rbegin(); 
    vector<int>::iterator itB = b->begin();

    while ((itA != a->rend()) && (itB != b->end())) {
        if (*itA < *itB) {
            newList->push_back(*itA);
            itA++;
        }
        else {
            newList->push_back(*itB);
            itB++;
        }
    }

    while (itA != a->rend()) {
        newList->push_back(*(itA++));
    }
    while (itB != b->end()) {
        newList->push_back(*(itB++));
    }

    return newList;
}

vector<int>* squareElements(vector<int>* origList) {
    if (origList == NULL)
        return NULL;
    
    vector<int> * negList = new vector<int>;
    vector<int> * posList = new vector<int>;

    vector<int>::iterator it = origList->begin();
    while ((it != origList->end()) && (*it < 0)) {
        negList->push_back(pow(*it, 2));
        it++;
    }

    while(it != origList->end()) {
        posList->push_back(pow(*it,2));
        it++;
    }

    vector<int> * result = merge(negList, posList);

    delete negList;
    delete posList;

    return result;
}

//test driver main function
int main() {
    vector<int> a = {-9, -8, -3, 0, 2, 7, 8, 10};
    vector<int> * result = squareElements(&a);

    outputVector(result);

    return 0;
}