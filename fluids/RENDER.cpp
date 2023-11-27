#include "RENDER.h"
#include <GLFW/glfw3.h>
#include <vector>

void RENDER(const GRIDS& grids, const ENV& env) {
    const Grid* gridToRender;
    int width = env.getSceneWidth();
    int height = env.getSceneHeight();

    switch (env.getRenderGrid()) {
    case U_VEL:
        gridToRender = &grids.getUVelGrid();
        //width += 1;
        break;
    case V_VEL:
        gridToRender = &grids.getVVelGrid();
        //height += 1;
        break;
    case PRESSURE:
        gridToRender = &grids.getPressureGrid();
        break;
    case DENSITY:
        gridToRender = &grids.getDensityGrid();
        break;
    case TEMPERATURE:
        gridToRender = &grids.getTemperatureGrid();
        break;
    default:
        return;
    }

    float min = env.getDataMin();
    float max = env.getDataMax();
   
    // Prepare texture
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Populate texture data
    std::vector<unsigned char> textureData(width * height * 3); // RGB format
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            float value = (gridToRender->getValue(i, j) - min) / (max - min); // Normalize
            unsigned char color = static_cast<unsigned char>(255 * value);
            int index = 3 * (i * width + j);
            textureData[index] = color;     // R
            textureData[index + 1] = color; // G
            textureData[index + 2] = color; // B
        }
    }

    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.data());

    // Render texture
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);  // Bottom Left
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);  // Bottom Right
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);  // Top Right
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);  // Top Left
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Clean up
    glDeleteTextures(1, &textureId);
}