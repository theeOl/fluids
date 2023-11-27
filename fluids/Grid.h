#pragma once
#ifndef GRID_H
#define GRID_H

#include <stdexcept>

class Grid {
private:
    float** data;
    int width;
    int height;

public:
    Grid(int width, int height, float initialValue = 0.0f);
    ~Grid();

    float getValue(int x, int y) const;
    void setValue(int x, int y, float value);

    int getWidth() const { return width; }  
    int getHeight() const { return height; }  

    void swap(Grid& other);

    static float** createGrid(int width, int height, float initialValue);
    static void deleteGrid(float** grid, int height);
};

#endif
