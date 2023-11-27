#pragma once
#ifndef SOLVER_H
#define SOLVER_H

#include "GRIDS.h"
#include "ENV.h"

void SOLVER(GRIDS& grids, const ENV& env); //run through all simulation steps

void Advection(GRIDS& grids, const ENV& env); //advect uVel vVel density temperature using semiLagrangien, backward tracing, interpolation 
void advectVelocityFields(GRIDS& grids, float deltaTime, float cellSize);
void advectScalarFields(GRIDS& grids, float deltaTime, float cellSize);
float interpolateBilinear(const Grid& grid, float x, float y);

void ExternalForces(GRIDS& grids, const ENV& env);

void Diffusion(GRIDS& grids, const ENV& env);

void Pressure(GRIDS& grids, const ENV& env); //solve pressure using poisson, gauss-seidel
float computeDivergence(const GRIDS& grids, int x, int y, float cellSize);
float computePressure(const GRIDS& grids, int x, int y, float divergence, float cellSize, float deltaTime, float relaxCoef);
void project(GRIDS& grids, float cellSize, float deltaTime); //solve incompressibility, subtract gradient of pressure from velocity

void handleBoundaries(GRIDS& grids, const ENV& env);

void TimeIntegration(GRIDS& grids, const ENV& env);

#endif