#include "GRIDS.h"

GRIDS::GRIDS(const ENV& env)
    : uVelGrid(env.getSceneWidth() + 1, env.getSceneHeight(), env.getInitialUVel()),
    vVelGrid(env.getSceneWidth(), env.getSceneHeight() + 1, env.getInitialVVel()),
    uVelGridSwap(env.getSceneWidth() + 1, env.getSceneHeight()),
    vVelGridSwap(env.getSceneWidth(), env.getSceneHeight() + 1),
    pressureGrid(env.getSceneWidth(), env.getSceneHeight(), env.getInitialPressure()),
    densityGrid(env.getSceneWidth(), env.getSceneHeight(), env.getInitialDensity()),
    temperatureGrid(env.getSceneWidth(), env.getSceneHeight(), env.getInitialTemperature()),
    densityGridSwap(env.getSceneWidth(), env.getSceneHeight()),
    temperatureGridSwap(env.getSceneWidth(), env.getSceneHeight())
{}

GRIDS::~GRIDS() {}

const Grid& GRIDS::getUVelGrid() const {
    return uVelGrid;
}

Grid& GRIDS::getUVelGrid() {
    return uVelGrid;
}

Grid& GRIDS::getUVelGridSwap() {
    return uVelGridSwap;
}

const Grid& GRIDS::getVVelGrid() const {
    return vVelGrid;
}

Grid& GRIDS::getVVelGrid() {
    return vVelGrid;
}

Grid& GRIDS::getVVelGridSwap() {
    return vVelGridSwap;
}

const Grid& GRIDS::getDensityGrid() const {
    return densityGrid;
}

Grid& GRIDS::getDensityGrid() {
    return densityGrid;
}

Grid& GRIDS::getDensityGridSwap() {
    return densityGridSwap;
}

const Grid& GRIDS::getTemperatureGrid() const {
    return temperatureGrid;
}

Grid& GRIDS::getTemperatureGrid() {
    return temperatureGrid;
}

Grid& GRIDS::getTemperatureGridSwap() {
    return temperatureGridSwap;
}



const Grid& GRIDS::getPressureGrid() const {
    return pressureGrid;
}

Grid& GRIDS::getPressureGrid() {
    return pressureGrid;
}