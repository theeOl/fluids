#include "SOLVER.h"
#include <algorithm>
#include <iostream>



void SOLVER(GRIDS& grids, const ENV& env) {
    Advection(grids, env);
    ExternalForces(grids, env);
    Diffusion(grids, env);
    Pressure(grids, env);
    handleBoundaries(grids, env);
    TimeIntegration(grids, env);
}



void Advection(GRIDS& grids, const ENV& env) {
    float deltaTime = env.getDeltaTime();
    float cellSize = env.getCellSize();
    advectVelocityFields(grids, deltaTime, cellSize);
    advectScalarFields(grids, deltaTime, cellSize);
}

void advectVelocityFields(GRIDS& grids, float deltaTime, float cellSize) {
    Grid& uVelGrid = grids.getUVelGrid();
    Grid& vVelGrid = grids.getVVelGrid();
    Grid& uVelGridSwap = grids.getUVelGridSwap();
    Grid& vVelGridSwap = grids.getVVelGridSwap();

    // Advection for each cell in the velocity grids
    for (int y = 0; y < uVelGrid.getHeight(); ++y) {
        for (int x = 0; x < uVelGrid.getWidth()-1; ++x) {
            // Backward trace
            float xBack = x - uVelGrid.getValue(x, y) * deltaTime / cellSize;
            float yBack = y - vVelGrid.getValue(x, y) * deltaTime / cellSize;

            // Interpolate the velocity at the backward traced position
            uVelGridSwap.setValue(x, y, interpolateBilinear(uVelGrid, xBack, yBack));
        }
    }

    for (int y = 0; y < vVelGrid.getHeight()-1; ++y) {
        for (int x = 0; x < vVelGrid.getWidth(); ++x) {
            // Backward trace
            float xBack = x - uVelGrid.getValue(x, y) * deltaTime / cellSize;
            float yBack = y - vVelGrid.getValue(x, y) * deltaTime / cellSize;

            // Interpolate the velocity at the backward traced position
            vVelGridSwap.setValue(x, y, interpolateBilinear(vVelGrid, xBack, yBack));
        }
    }

    // Swap the old and new velocity grids
    uVelGrid.swap(uVelGridSwap);
    vVelGrid.swap(vVelGridSwap);
}

void advectScalarFields(GRIDS& grids, float deltaTime, float cellSize) {

    Grid& densityGrid = grids.getDensityGrid();
    Grid& temperatureGrid = grids.getTemperatureGrid();
    Grid& densityGridSwap = grids.getDensityGridSwap();
    Grid& temperatureGridSwap = grids.getTemperatureGridSwap();

    const Grid& uVelGrid = grids.getUVelGrid();
    const Grid& vVelGrid = grids.getVVelGrid();

    // Advection for each cell in the scalar grids
    for (int y = 0; y < densityGrid.getHeight(); ++y) {
        for (int x = 0; x < densityGrid.getWidth(); ++x) {
            // Backward trace
            float xBack = x - uVelGrid.getValue(x, y) * deltaTime / cellSize;
            float yBack = y - vVelGrid.getValue(x, y) * deltaTime / cellSize;

            // Interpolate the scalar values at the backward traced position
            densityGridSwap.setValue(x, y, interpolateBilinear(densityGrid, xBack, yBack));
            temperatureGridSwap.setValue(x, y, interpolateBilinear(temperatureGrid, xBack, yBack));
        }
    }

    // Swap the old and new scalar grids
    densityGrid.swap(densityGridSwap);
    temperatureGrid.swap(temperatureGridSwap);
}

float interpolateBilinear(const Grid& grid, float x, float y) {
    // Calculate the integer parts of x and y
    int xInt = static_cast<int>(x);
    int yInt = static_cast<int>(y);

    // Calculate the fractional parts of x and y
    float xFrac = x - xInt;
    float yFrac = y - yInt;

    // Clamp the coordinates to ensure they are within the grid bounds
    xInt = std::max(0, std::min(xInt, grid.getWidth() - 2));
    yInt = std::max(0, std::min(yInt, grid.getHeight() - 2));

    // Retrieve the values at the corner points of the cell
    float v00 = grid.getValue(xInt, yInt);       // Bottom-left
    float v10 = grid.getValue(xInt + 1, yInt);   // Bottom-right
    float v01 = grid.getValue(xInt, yInt + 1);   // Top-left
    float v11 = grid.getValue(xInt + 1, yInt + 1); // Top-right

    // Interpolate between the values
    float interpBottom = (1 - xFrac) * v00 + xFrac * v10;
    float interpTop = (1 - xFrac) * v01 + xFrac * v11;

    // Final interpolation between top and bottom interpolations
    float interpolatedValue = (1 - yFrac) * interpBottom + yFrac * interpTop;

    return interpolatedValue;
}


void ExternalForces(GRIDS& grids, const ENV& env) {}


void Diffusion(GRIDS& grids, const ENV& env) {}


void Pressure(GRIDS& grids, const ENV& env) {
    // Retrieve necessary parameters from the environment
    float deltaTime = env.getDeltaTime();
    float cellSize = env.getCellSize();
    int iterations = env.getPressureSolverIterations();  
    float relaxCoef = env.getRelaxCoefficient();

    // Iteratively solve the Poisson equation for the pressure
    for (int iter = 0; iter < iterations; ++iter) {
        for (int y = 0; y < grids.getPressureGrid().getHeight(); ++y) {
            for (int x = 0; x < grids.getPressureGrid().getWidth(); ++x) {
                // Compute the divergence at this cell
                float divergence = computeDivergence(grids, x, y, cellSize);

                // Compute the pressure value using the neighboring pressure values
                // and the divergence. This typically involves averaging the neighboring
                // pressure values and adjusting based on the divergence and other factors
                float pressure = computePressure(grids, x, y, divergence, cellSize, deltaTime, relaxCoef);

                // Update the pressure grid
                grids.getPressureGrid().setValue(x, y, pressure);
            }
        }

        // Handle pressure boundary conditions after each iteration
    }

    project(grids, cellSize, deltaTime);
}

float computeDivergence(const GRIDS& grids, int x, int y, float cellSize) {
    // Ensure indices are within grid bounds
    x = std::max(0, std::min(x, grids.getUVelGrid().getWidth() - 2));
    y = std::max(0, std::min(y, grids.getVVelGrid().getHeight() - 2));

    // Calculate the horizontal velocity difference across the cell
    float uRight = grids.getUVelGrid().getValue(x + 1, y);
    float uLeft = grids.getUVelGrid().getValue(x, y);
    float uDiff = (uRight - uLeft) / cellSize;

    // Calculate the vertical velocity difference across the cell
    float vTop = grids.getVVelGrid().getValue(x, y + 1);
    float vBottom = grids.getVVelGrid().getValue(x, y);
    float vDiff = (vTop - vBottom) / cellSize;

    // The divergence is the sum of these differences
    float divergence = uDiff + vDiff;

    return divergence;
}

float computePressure(const GRIDS& grids, int x, int y, float divergence, float cellSize, float deltaTime, float relaxCoef) {
    // Retrieve the pressure values from the neighboring cells
    float pLeft = (x > 0) ? grids.getPressureGrid().getValue(x - 1, y) : 0.0f;
    float pRight = (x < grids.getPressureGrid().getWidth() - 1) ? grids.getPressureGrid().getValue(x + 1, y) : 0.0f;
    float pBottom = (y > 0) ? grids.getPressureGrid().getValue(x, y - 1) : 0.0f;
    float pTop = (y < grids.getPressureGrid().getHeight() - 1) ? grids.getPressureGrid().getValue(x, y + 1) : 0.0f;

    // Compute the new pressure value
    // This is typically a variation of the Gauss-Seidel relaxation formula
    // For fluid simulations, it can include terms from the divergence and other factors
    float newPressure = (pLeft + pRight + pBottom + pTop - (divergence * cellSize * cellSize)) / 4.0f;
    newPressure = (1 - relaxCoef) * grids.getPressureGrid().getValue(x, y) + relaxCoef * newPressure;

    return newPressure;
}

void project(GRIDS& grids, float cellSize, float deltaTime) {

    // Adjust the horizontal velocity field (uVelGrid)
    for (int y = 0; y < grids.getUVelGrid().getHeight(); ++y) {
        for (int x = 1; x < grids.getUVelGrid().getWidth() - 1; ++x) {
            float pressureLeft = grids.getPressureGrid().getValue(x - 1, y);
            float pressureRight = grids.getPressureGrid().getValue(x, y);
            float pressureGradient = (pressureRight - pressureLeft) / cellSize;

            float newUVal = grids.getUVelGrid().getValue(x, y) - deltaTime * pressureGradient;
            grids.getUVelGrid().setValue(x, y, newUVal);
        }
    }

    // Adjust the vertical velocity field (vVelGrid)
    for (int y = 1; y < grids.getVVelGrid().getHeight() - 1; ++y) {
        for (int x = 0; x < grids.getVVelGrid().getWidth(); ++x) {
            float pressureBottom = grids.getPressureGrid().getValue(x, y - 1);
            float pressureTop = grids.getPressureGrid().getValue(x, y);
            float pressureGradient = (pressureTop - pressureBottom) / cellSize;

            float newVVal = grids.getVVelGrid().getValue(x, y) - deltaTime * pressureGradient;
            grids.getVVelGrid().setValue(x, y, newVVal);
        }
    }

    // Handle boundaries if necessary
}




void handleBoundaries(GRIDS& grids, const ENV& env) {}

void TimeIntegration(GRIDS& grids, const ENV& env){}
