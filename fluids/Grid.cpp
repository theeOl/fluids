#include "Grid.h"

Grid::Grid(int width, int height, float initialValue)
    : width(width), height(height) {
    data = createGrid(width, height, initialValue);
}

Grid::~Grid() { deleteGrid(data, height);}

float Grid::getValue(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return data[x][y];
    }
    throw std::out_of_range("Index out of range in getValue");
}

void Grid::setValue(int x, int y, float value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        data[x][y] = value;
    }
    else {
        throw std::out_of_range("Index out of range in setValue");
    }
}

void Grid::swap(Grid& other) {
    std::swap(data, other.data);
    std::swap(width, other.width);
    std::swap(height, other.height);
}

float** Grid::createGrid(int width, int height, float initialValue) {
    float** grid = new float* [width];
    for (int i = 0; i < width; ++i) {
        grid[i] = new float[height];
        for (int j = 0; j < height; ++j) {
            if (i<width-width/ 2.6 && i>=width/ 2.6 &&
                j<height-height/ 1.4 && j>=height/ 8) { grid[i][j] = initialValue; }
            else { grid[i][j] = 0.0; }
            
        }
    }
    return grid;
}

void Grid::deleteGrid(float** grid, int height) {
    for (int i = 0; i < height; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

