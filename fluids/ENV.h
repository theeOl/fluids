#pragma once
#ifndef ENV_H
#define ENV_H


enum RenderGridType {
    U_VEL,
    V_VEL,
    PRESSURE,
    DENSITY,
    TEMPERATURE
};


class ENV {
private:
    int sceneWidth;
    int sceneHeight;
    float cellSize;
    float initialUVel;
    float initialVVel;
    float initialPressure;
    float initialDensity;
    float initialTemperature;
    float deltaTime;
    int pressureSolverIterations;
    float relaxCoefficient;
    float gravity;
    float viscosity;
    float dataMin;
    float dataMax;
    RenderGridType renderGrid;

public:
    ENV(int width, int height, float cellSz, float uVel, float vVel, float pressure,
        float density, float temperature, float dt, int pSolverIter, float relaxCoef, float grav, float visc, float min, float max, RenderGridType renderType);

    int getSceneWidth() const;
    int getSceneHeight() const;
    float getCellSize() const;
    float getInitialUVel() const;
    float getInitialVVel() const;
    float getInitialPressure() const;
    float getInitialDensity() const;
    float getInitialTemperature() const;
    float getDeltaTime() const;
    int getPressureSolverIterations() const;
    float getRelaxCoefficient() const;
    float getGravity() const;
    float getViscosity() const;
    float getDataMin() const;
    float getDataMax() const;
    RenderGridType getRenderGrid() const;
};

#endif 
