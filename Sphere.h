#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Sphere {
public:
    VAO vao;
    VBO vbo;
    EBO ebo;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Sphere(float radius, unsigned int sectorCount, unsigned int stackCount);
    void Draw(Shader& shader);
    void Delete();
   
};

#endif
