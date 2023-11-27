#include "ENV.h"

ENV::ENV(int width, int height, float cellSz, float uVel, float vVel, float pressure,
    float density, float temperature, float dt, int pSolverIter, float relaxCoef, float grav, float visc, float min, float max, RenderGridType renderType)
    : sceneWidth(width), sceneHeight(height), cellSize(cellSz),
    initialUVel(uVel), initialVVel(vVel), initialPressure(pressure),
    initialDensity(density), initialTemperature(temperature),
    deltaTime(dt), pressureSolverIterations(pSolverIter), relaxCoefficient(relaxCoef), gravity(grav), viscosity(visc), dataMin(min), dataMax(max), renderGrid(renderType) {}

int ENV::getSceneWidth() const { return sceneWidth; }
int ENV::getSceneHeight() const { return sceneHeight; }
float ENV::getCellSize() const { return cellSize; }
float ENV::getInitialUVel() const { return initialUVel; }
float ENV::getInitialVVel() const { return initialVVel; }
float ENV::getInitialPressure() const { return initialPressure; }
float ENV::getInitialDensity() const { return initialDensity; }
float ENV::getInitialTemperature() const { return initialTemperature; }
float ENV::getDeltaTime() const { return deltaTime; }
int ENV::getPressureSolverIterations() const { return pressureSolverIterations; }
float ENV::getRelaxCoefficient() const { return relaxCoefficient; }
float ENV::getGravity() const { return gravity; }
float ENV::getViscosity() const { return viscosity;  }
float ENV::getDataMin() const { return dataMin; }
float ENV::getDataMax() const { return dataMax; }
RenderGridType ENV::getRenderGrid() const { return renderGrid; }
