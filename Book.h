#ifndef BOOK_H
#define BOOK_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h"

class Book {
public:
    VAO vaoBase, vaoMiddle, vaoCover, vaoSpine;
    VBO vboBase, vboMiddle, vboCover, vboSpine;
    EBO eboBase, eboMiddle, eboCover, eboSpine;

    Book();
    void Draw(Shader& shader, Texture& baseTex, Texture& middleTex, Texture& coverTex);
    void Delete();
};

#endif
