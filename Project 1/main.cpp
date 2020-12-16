#include <iostream>
#include "squareMatrix.h"
using namespace std;

int main() {
    squareMatrix <int> square1;
    square1.resize(50);
    square1.at(0,0) = 5;
    squareMatrix<int> square2;
    square2 = square1;
    if (square2 == square1) {
        cout<<"Equal"<<endl;
    } else {
        cout<<"Not equal"<<endl;
    }
    squareMatrix <int> square4;
    square4.resize(60);
    squareMatrix<int> square3 = square2 + square4;
    cout<<square3.at(0,0)<<endl;
    cout<<square2.at(0,0)<<endl;
    return 0;
}
