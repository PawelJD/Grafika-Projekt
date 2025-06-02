#pragma once
#ifndef PAD_H
#define PAD_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h"

class Pad {
public:
    VAO vaoPad;
    VBO vboPad;
    EBO eboPad;

    Pad();
    void Draw(Shader& shader, Texture& baseTex);
    void Delete();
};

#endif
