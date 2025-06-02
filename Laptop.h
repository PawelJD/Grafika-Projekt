#pragma once
#ifndef LAPTOP_H
#define LAPTOP_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h"
#include <glm/glm.hpp>

class Laptop {
public:
    VAO vaoBase, vaoMonitor, vaoScreen;
    VBO vboBase, vboMonitor, vboScreen;
    EBO eboBase, eboMonitor, eboScreen;

    Laptop();
    Laptop(float baseWidth, float baseHeight, float baseDepth, float monitorWidth, float monitorHeight, float monitorDepth, float screenInset);

    void Draw(Shader& shader, Texture& keyboardTex, Texture& monitorTex, Texture& screenTex);

    void Delete();
};

#endif
