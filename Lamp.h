#pragma once
#ifndef LAMP_H
#define LAMP_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h"
#include <glm/glm.hpp>

class Lamp {
public:
    VAO vao;
    VBO vbo;
    EBO ebo;

    Lamp();
    void Draw(Shader& shader, Texture& lampTex);
    void Delete();
};

#endif
