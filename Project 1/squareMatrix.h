#pragma once

template<typename T>
class squareMatrix
{
private:
   T** _ptr;
   size_t _rowSize;
   size_t _columnSize;

public:
   squareMatrix();
   // Big Five
   ~squareMatrix(); //destructor
   squareMatrix(const squareMatrix& otherMatrix); //copy constructor
   squareMatrix(squareMatrix&& otherMatrix); //move constructor
   squareMatrix& operator=(const squareMatrix& otherMatrix); //copy assignment overload
   squareMatrix& operator=(squareMatrix&& otherMatrix); //move assignment overload
   squareMatrix& operator+(const squareMatrix& otherMatrix);
   bool operator==(squareMatrix& otherMatrix);
   size_t size() const;
   T& at(size_t index1, size_t index2);
   void resize(size_t newSize);
};

#include "squareMatrix.cpp"
