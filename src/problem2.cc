/*

This problem was asked by Uber.

Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].

Follow-up: what if you can't use division?

*/
#include <iostream>
#include <vector>
using namespace std;

//without division
vector<int>* specialProductMapping(vector<int>& inputVector) {
    vector<int> * result = new vector<int>;

    //outer for loop's iteration corresponds to one element
    //in the result vector
    for (size_t i = 0; i < inputVector.size(); i++) {
        int product = 1;

        //inner for loop's iteration corresponds to multiplying
        //an individual element in the input vector with the current
        //result
        for (size_t j = 0; j < inputVector.size(); j++) {
            if (i != j) {
                product *= inputVector[j];
            }
        }

        result->push_back(product);
    }

    return result;
}

int main() {
    vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);

    vector<int>* result = specialProductMapping(a);

    for (vector<int>::iterator i = result->begin(); i != result->end(); i++) {
        cout << *i << " ";
    }

    cout << endl;

    return 0;
}