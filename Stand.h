#ifndef STAND_H
#define STAND_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Stand {
public:
    VAO vao;
    VBO vbo;
    EBO ebo;

    Stand();
    void Draw(Shader& shader);
    void Delete();
};

#endif
