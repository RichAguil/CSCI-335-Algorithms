#include <iostream>
#include "squareMatrix.h"
int main() {
  //std::cout << "Hello World!\n";
  squareMatrix<int> x;
  std::cout << "x size:" << x.size() << std::endl;
  x.resize(5);
  std::cout << "x size (should be 5): " << x.size() << std::endl;
  squareMatrix<int> y;
  squareMatrix<int> z;
  y.resize(5);
  y.at(0,3) = 5;
  x.at(0,3) = 5;
  if( x==y ) // here x calls the operator== and supplies y as a parameter
   std::cout<< "Matrices x and y are equal!"<< std::endl;

  if( y==z ) // here A calls the operator== and supplies B as a parameter
   std::cout<< "Matrices y and z are equal!"<< std::endl;

  y.resize(5);
  y.at(4,4) = 8;
  std::cout << "y[4][4] is: (should be 8)" << y.at(4,4) << std::endl;
  y.resize(6);
  std::cout << "y[4][4] is: (should be 0)" << y.at(4,4) << std::endl;
  //y.at(6,4) = 7;
  squareMatrix<int> a;
  a.resize(2);
  for(int i = 0; i < 2; i++)
  {
    for(int j=0;j<2;j++)
    {
      a.at(i,j) = 2;
    }
  }
  squareMatrix<int> b;
  b.resize(2);
  for(int i = 0; i < 2; i++)
  {
    for(int j=0;j<2;j++)
    {
      b.at(i,j) = 3;
    }
  }
  squareMatrix<int> c = a + b;
  std::cout << "c[1][0] is: " << c.at(1,0) << std::endl;
  a = b = c;
  std::cout << b.at(1,0) <<  c.at(0,1) <<  a.at(0,1) << std::endl;
  squareMatrix<int> d = std::move(c);
  //SquareMatrix<int> d = c;
  std::cout<< "size of SquareMatrix d is: " << d.size() << std::endl; 
  std::cout<< "d[0][1] = " <<  d.at(0,1) << std::endl;
  std::cout<< "c size is: " << c.size() << std::endl;
  c.resize(5);
  squareMatrix<int> e;
  e.resize(3);
  c.at(0,0) = 7;
  e = std::move(c);
  std::cout << e.at(0,0) << e.size() << c.size();
  //std::cout << c.at(0,0);

  squareMatrix<int> h(e);
  std::cout << h.at(0,0) << e.at(0,0) << std::endl;
  h = x;
  std::cout << "h size is: (should be 5) " << h.size() << std::endl << "h[0][3] = (should be 5) " << h.at(0,3);
  squareMatrix<int> w;
  w.at(0,0) = 5;
}