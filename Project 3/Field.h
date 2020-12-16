#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Field {
    private:
        int length = 0;
        int height = 0;
        std::vector<std::vector<int>> storageMatrix;
        std::vector<std::vector<int>> weightMatrix;
    public:
        Field(const std::vector<std::vector<int>>& input);
        Field(std::vector<std::vector<int>>&& input);
        int Weight(int x1, int y1, int x2, int y2);
        int PathCost();
        void printMatrix();
};

#include "Field.cpp"
#endif