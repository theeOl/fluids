//using glfw-3.3.8
#include <GLFW/glfw3.h>
#include "ENV.h"
#include "GRIDS.h"
#include "SOLVER.h"
#include "RENDER.h"


int main(void) {
    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(600, 600, "Eulerian Fluid Simulator", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    //ENV(
    int width = 300;
    int height = 300;
    float cellSz = 1.0;
    float uVel = 0.0;
    float vVel = 30.0;
    float pressure = 0.0;
    float density = 0.9;
    float temperature = 0.6;
    float dt = 0.9;
    int pSolverIter = 10;
    float relaxCoef = 1.7;
    float grav = 0.0;
    float visc = 0.0;
    float dataMin = 0.0;
    float dataMax = 1.0;
    RenderGridType renderGrid = DENSITY;
    //);
   
    ENV env(width, height, cellSz, uVel, vVel, pressure, density, temperature, dt, pSolverIter, relaxCoef, grav, visc, dataMin, dataMax, renderGrid);
    GRIDS grids(env);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);


        
        SOLVER(grids, env);
        RENDER(grids, env);


        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}