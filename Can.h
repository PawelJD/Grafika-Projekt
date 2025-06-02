#ifndef CAN_H
#define CAN_H

#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Can {
public:
    // Konstruktor
    Can(float radius, float height, unsigned int sectorCount);

    // Metody rysuj¹ce
    void DrawSide(Shader& shader);
    void DrawTop(Shader& shader);
    void DrawBottom(Shader& shader);
    void Delete();

private:
    // Œciany puszki
    VAO vaoSide;
    VBO vboSide;
    EBO eboSide;
    std::vector<float> sideVertices;
    std::vector<unsigned int> sideIndices;

    // Górna pokrywka
    VAO vaoTop;
    VBO vboTop;
    EBO eboTop;
    std::vector<float> topVertices;
    std::vector<unsigned int> topIndices;

    // Dolna pokrywka
    VAO vaoBottom;
    VBO vboBottom;
    EBO eboBottom;
    std::vector<float> bottomVertices;
    std::vector<unsigned int> bottomIndices;
};

#endif
