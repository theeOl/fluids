#pragma once
#ifndef GRIDS_H
#define GRIDS_H

#include "ENV.h"
#include "Grid.h"

class GRIDS {
private:
    Grid uVelGrid, vVelGrid; //uVelGrid = width + 1; vVelGrid = height + 1; (staggered grids)
    Grid uVelGridSwap, vVelGridSwap; //for swapping 
    Grid densityGrid, temperatureGrid;
    Grid densityGridSwap, temperatureGridSwap; //for swapping

    Grid pressureGrid;

public:
    GRIDS(const ENV& env);
    ~GRIDS();

    const Grid& getUVelGrid() const;
    const Grid& getVVelGrid() const;
    const Grid& getDensityGrid() const;
    const Grid& getTemperatureGrid() const;

    const Grid& getPressureGrid() const;

    Grid& getUVelGrid();
    Grid& getUVelGridSwap();
    Grid& getVVelGrid();
    Grid& getVVelGridSwap();
    Grid& getDensityGrid();
    Grid& getDensityGridSwap();
    Grid& getTemperatureGrid();
    Grid& getTemperatureGridSwap();

    Grid& getPressureGrid();
};

#endif
