#ifndef DESK_H
#define DESK_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h" 

class Desk {
public:
    VAO vaoTop, vaoLegs;
    VBO vboTop, vboLegs;
    EBO eboTop, eboLegs;

    Desk();

    void Draw(Shader& shader, Texture& topTex, Texture& legTex);
    void Delete();
};

#endif
