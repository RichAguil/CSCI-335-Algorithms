#include<stdexcept>
#include <cmath>
template<typename T>
squareMatrix<T>::squareMatrix() : _ptr(nullptr), _rowSize(0), _columnSize(0)
{}

template<typename T>
squareMatrix<T>::~squareMatrix()
{
    if (_rowSize > 0) {
        for (int i = 0; i < _columnSize; i++) {
            delete[] _ptr[i];
        }
    }
    delete[] _ptr;
}

template<typename T>
squareMatrix<T>::squareMatrix(const squareMatrix<T>& otherMatrix) : _ptr(new T*[otherMatrix._rowSize]), _rowSize{otherMatrix._rowSize}, _columnSize(otherMatrix._columnSize)
{
   if (otherMatrix._ptr == nullptr) {
      return; 
   }
    for (size_t i = 0; i < _columnSize; i++) {
        _ptr[i] = new T[_columnSize];
    }

    for (int i = 0; i < _rowSize; i++){
        for (int j = 0; j < _columnSize; j++) {
            _ptr[i][j] = otherMatrix._ptr[i][j];
        }
    }
}

template<typename T>
squareMatrix<T>::squareMatrix(squareMatrix<T>&& otherMatrix) :_ptr(otherMatrix._ptr), _rowSize(otherMatrix._rowSize), _columnSize(otherMatrix._columnSize)
{  
    for (int i = 0; i < otherMatrix._columnSize; i++) {
        delete[] otherMatrix._ptr[i];
    }
    otherMatrix._rowSize = 0;
    otherMatrix._columnSize = 0; 
    delete [] otherMatrix._ptr;

}

template<typename T>
squareMatrix<T>& squareMatrix<T>::operator=(const squareMatrix<T>& otherMatrix)
{
    if (this == &otherMatrix)  {
        return *this; 
    }
    if (_ptr != nullptr) {

        for (int i = 0; i < _columnSize; i++) {
            delete[] _ptr[i];
        }
        delete[] _ptr;
    }
    _rowSize = otherMatrix._rowSize;
    _columnSize = otherMatrix._columnSize;
    _ptr = new T*[otherMatrix._rowSize];

    for (size_t i = 0; i < _columnSize; i++) {
        _ptr[i] = new T[_columnSize];
    }

    for (int i = 0; i < _rowSize; i++){
        for (int j = 0; j < _columnSize; j++) {
            _ptr[i][j] = otherMatrix._ptr[i][j];
        }
    }
   return *this;
}

template<typename T>
squareMatrix<T>& squareMatrix<T>::operator=(squareMatrix<T>&& otherMatrix)
{
   if (_ptr != nullptr) {
        for (int i = 0; i < _columnSize; i++) {
            delete[] _ptr[i];
        }
        delete [] _ptr;
   }

   _ptr = otherMatrix._ptr;
   _rowSize = otherMatrix._rowSize;
   _columnSize = otherMatrix._columnSize;

    for (int i = 0; i < otherMatrix._columnSize; i++) {
        delete[] otherMatrix._ptr[i];
    }
    delete [] otherMatrix._ptr;

   return *this;
}

template <typename T>
bool squareMatrix<T>::operator==(squareMatrix& otherMatrix)
{
    if (_rowSize != otherMatrix._rowSize && _columnSize != otherMatrix._rowSize) {
        return false;
    }

    for (int i = 0; i < _rowSize; i++) {
        for (int j = 0; j < _columnSize; j++) {
            if (_ptr[i][j] != otherMatrix._ptr[i][j]) {
                std::cout<<_ptr[i][j]<<std::endl;
                std::cout<<otherMatrix._ptr[i][j]<<std::endl;
                return false;
            }
        }
    }

    return true;
}

template<typename T>
squareMatrix<T>& squareMatrix<T>::operator+(const squareMatrix& otherMatrix)
{
    if (this->_rowSize != otherMatrix._rowSize && this->_columnSize != otherMatrix._columnSize) {
        throw std::domain_error("Matrices do not match");
    }

    for (int i = 0; i < otherMatrix._rowSize; i++) {
        for (int j = 0; j <otherMatrix._columnSize; j++) {
            this->_ptr[i][j] = this->_ptr[i][j] + otherMatrix._ptr[i][j];
        }
    }
    return *this;
}

template<typename T>
size_t squareMatrix<T>::size() const
{
   return _rowSize*_columnSize;
}

template<typename T>
T& squareMatrix<T>::at(size_t index1, size_t index2)
{
   if (index1 < _rowSize && index2 < _columnSize) {
       return _ptr[index1][index2];
   } else {
       throw std::out_of_range("Indices are out of matrix range");  
   }  
}

template<typename T>
void squareMatrix<T>::resize(size_t newSize)
{
    if (_rowSize > 0) {
        for (size_t i = 0; i < _columnSize; i++) {
            delete[] _ptr[i];
        }
        delete[] _ptr;
    }
    _rowSize = newSize;
    _columnSize = newSize;
    _ptr = new T*[_rowSize];
    for (size_t i = 0; i < _columnSize; i++) {
        _ptr[i] = new T[_columnSize];
    }
}

