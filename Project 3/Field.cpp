#include "Field.h"
#include <iostream>
#include <algorithm>

Field::Field(const std::vector<std::vector<int>>& input) {

    length = input.size();
    height = input[0].size();

    if (height == 0 || length == 0) {
        throw std::out_of_range("Input vector is of size zero");
    }

    storageMatrix.resize(length, std::vector<int>(height, 0)); //This initializes a 2D vector with zeros
    weightMatrix.resize(length, std::vector<int>(height, 0)); //This matrix shall hold the sum of the indices for the weight method

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            storageMatrix[i][j] = input[i][j];
        }
    }

    //Weight precomputation starts here
    //In order to create a running sum of the columns and rows leading up to the index, the columns must be summed up, and the rows must be summed up
    //As an example, for the index at row 2, column 3, the value at that index will be the sum of column 3 up until row 2, and the sum of row 2 up until column 3 (hopefully, that makes sense)

    //This is the column summation
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            if (i != 0) {
                weightMatrix[i][j] = storageMatrix[i][j] + weightMatrix[i-1][j];
            } else {
                weightMatrix[i][j] = storageMatrix[i][j];
            }
        }
    }
    //This is the row summation
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            if (j != 0) {
                weightMatrix[i][j] = weightMatrix[i][j] + weightMatrix[i][j-1];
            }
        }
    }

    std::cout<<"Storage Matrix for copy constructor"<<std::endl;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            std::cout << storageMatrix[i][j] << " ";
            if (j == height - 1) {
                std::cout<<"\n";
            }
        }
    }
}

Field::Field(std::vector<std::vector<int>>&& input) {
    
    length = input.size();
    height = input[0].size();

    if (height == 0 || length == 0) {
        throw std::out_of_range("Input vector is of size zero");
    }

    storageMatrix = std::move(input);
    weightMatrix.resize(length, std::vector<int>(height, 0));
    //This is the column summation
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            if (i != 0) {
                weightMatrix[i][j] = storageMatrix[i][j] + weightMatrix[i-1][j];
            } else {
                weightMatrix[i][j] = storageMatrix[i][j];
            }
        }
    }
    //This is the row summation
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            if (j != 0) {
                weightMatrix[i][j] = weightMatrix[i][j] + weightMatrix[i][j-1];
            }
        }
    }

    std::cout<<"Storage Matrix for move constructor"<<std::endl;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            std::cout << storageMatrix[i][j] << " ";
            if (j == height - 1) {
                std::cout<<"\n";
            }
        }
    }
    
}

int Field::Weight(int x1, int y1, int x2, int y2) {
    //(1,0,4,3)
    int sum = 0;
    std::cout<<"Height: "<<height<<std::endl;
    std::cout<<"Length: "<<length<<std::endl;

    //The next two if-statements checks if coordinates are out of bounds
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) {
        throw std::out_of_range("Bounds are out of range");
    }

    if (y1 >= length || x1 >= height || y2 >= length || x2 >= height) {
        throw std::out_of_range("Bounds are out of range");
    }

    //If the coordinates happen to be the same
    if (x1 == x2 && y1 == y2) {
        return storageMatrix[y1][x1];
    }

    //This is for the case in which one of the starting points is at the origin
    if (x1 == 0 && y1 == 0) {
        return weightMatrix[y2][x2];
    } else if (x2 == 0 && y2 == 0) {
        return weightMatrix[y1][x1];
    }
    //These series of if-statements account for the different combinations of x1,y1, x2, y2
    if (x2 > x1 && y2 > y1 && x1 > 0 && y1 > 0) {
        sum = weightMatrix[y2][x2] - weightMatrix[y2][x1 - 1] - weightMatrix[y1 - 1][x2] + weightMatrix[y1 - 1][x1 - 1];
    } else if (x2 < x1 && y2 < y1 && x2 > 0 && y2 > 0) {
        sum = weightMatrix[y1][x1] - weightMatrix[y1][x2 - 1] - weightMatrix[y2 - 1][x1] + weightMatrix[y2 - 1][x2 - 1];
    } else if (x2 > x1 && y2 < y1 && x1 > 0 && y2 == 0) {
        sum = weightMatrix[y1][x2] - weightMatrix[y1][x1 - 1];
    } else if (x2 < x1 && y2 > y1 && x2 > 0 && y1 == 0) {
        sum = weightMatrix[y2][x1] - weightMatrix[y2][x2 - 1];
    } else if (x2 < x1 && y2 > y1 && x2 > 0 && y1 > 1) {
        sum = weightMatrix[y2][x1] - weightMatrix[y1 - 1][x1] - weightMatrix[y2][x2 - 1] + weightMatrix[y1 - 1][x2 - 1];
    } else if (x1 < x2 && y2 < y1 && x1 > 0 && y2 > 0) {
        sum = weightMatrix[y1][x2] - weightMatrix[y2 - 1][x2] - weightMatrix[y1][x1 - 1] + weightMatrix[y2 - 1][x1 - 1];
    } else if (x1 < x2 && y2 < y1 && x1 == 0 && y2 == 0) {
        sum = weightMatrix[y1][x2];
    } else if (x1 < x2 && y2 < y1 && x1 == 0 && y2 > 0) {
        sum = weightMatrix[y1][x2] - weightMatrix[x1][x2];
    } else if (x2 < x1 && y2 > y1 && x2 == 0 && y1 > 0) {
        sum = weightMatrix[y2][x1] - weightMatrix[x2][x1];
    } else if (x2 < x1 && y2 > y1 && x2 == 0 && y1 == 0) {
        sum = weightMatrix[y2][x1];
    }

    return sum;
}

int Field::PathCost() {

    if (length == 0 || height == 0) {
        return 0;
    }
    std::vector<std::vector<int>> pathMatrix(length, std::vector<int>(height, 0));

    //Fill first row
    /*
    for (int j = 0; j < height; j++) {
        pathMatrix[0][j] = weightMatrix[0][j];
    }
    //Fill first column
    for (int i = 0; i < length; i++) {
        pathMatrix[i][0] = weightMatrix[i][0];
    }
    */
   
    int x = height - 1;
    int y = length - 1;
    int leftValue;
    int topValue;
    int pathCost = storageMatrix[y][x];
    std::cout<<"Initial pathcost: "<<pathCost<<std::endl;

    while(true) {
        //Calculating the cost of taking the right path on pathMatrix
        if (y-1 >= 0) {
            topValue = storageMatrix[y][x] + storageMatrix[y - 1][x];
        }

        //Calculating the cost of taking the bottom path on pathMatrix
        if (x-1 >= 0) {
           leftValue = storageMatrix[y][x] + storageMatrix[y][x - 1];
        }
        
        if (topValue < leftValue) {
            pathCost += storageMatrix[y-1][x];
            y--;
        } else {
            pathCost += storageMatrix[y][x-1];
            x--;
        }
        std::cout<<"Current path cost: "<<pathCost<<std::endl;
        if (x == 0 && y == 0) {
            break;
        }

        //These set the variable to the max value an int could have. This is done after each iteration 
        //to ensure that if it reaches the edge of matrix, it will choose a viable path
        topValue = std::numeric_limits<int>::max();
        leftValue = std::numeric_limits<int>::max();
    }

    return pathCost;
}

void Field::printMatrix() {

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            std::cout << weightMatrix[i][j] << " ";
            if (j == height - 1) {
                std::cout<<"\n";
            }
        }
    }
}
