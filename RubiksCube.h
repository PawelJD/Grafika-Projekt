#pragma once
#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include <glm/glm.hpp>

class RubiksCube {
public:
    VAO vao;
    VBO vbo;
    EBO ebo;
    GLsizei indexCount;

    RubiksCube(float size);
    void Draw(Shader& shader, glm::vec3 position);
    void Delete();
};

#endif
