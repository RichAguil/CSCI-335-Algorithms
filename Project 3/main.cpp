#include "Field.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<vector<int>> testVector;
    vector<int> vector0{1, 2, 3, 4, 5, 6};
    vector<int> vector1{1, 2, 3, 4, 6};
    vector<int> vector2{5, 3, 8, 1, 2};
    vector<int> vector3{4, 6, 7, 5, 5};
    vector<int> vector4{2, 4, 8, 9, 4};
    
    testVector.push_back(vector0);
    testVector.push_back(vector0);
    testVector.push_back(vector0);
    testVector.push_back(vector0);
    testVector.push_back(vector0);
    //cout<<testVector.size()<<endl;

    Field testField(testVector);
    testField.printMatrix();
    cout<<testField.Weight(3,2,1,4)<<endl;
    cout<<"\n";
    cout<<testField.Weight(4,0,1,2)<<endl;
    cout<<testField.PathCost()<<endl;
    return 0;
}