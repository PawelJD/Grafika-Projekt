#include "Desk.h"

// Blat stołu – pozycja, normal, TexCoord
GLfloat deskVertices[] = {
    -4.0f,-0.6f, 2.0f,  0,1,0,  0,0,
    -4.0f,-0.6f,-2.0f,  0,1,0,  0,1,
     4.0f,-0.6f,-2.0f,  0,1,0,  1,1,
     4.0f,-0.6f, 2.0f,  0,1,0,  1,0,
    -4.0f,-0.7f, 2.0f,  0,-1,0, 0,0,
    -4.0f,-0.7f,-2.0f,  0,-1,0, 0,1,
     4.0f,-0.7f,-2.0f,  0,-1,0, 1,1,
     4.0f,-0.7f, 2.0f,  0,-1,0, 1,0
};
GLuint deskIndices[] = {
    0,1,2, 0,2,3, 4,5,6, 4,6,7,
    0,1,5, 0,5,4, 1,2,6, 1,6,5,
    2,3,7, 2,7,6, 3,0,4, 3,4,7
};

// Nogi stołu – pozycja, normal, TexCoord
GLfloat legVertices[] = {
    // Prawa przednia (X: 3.5-3.9, Z: 1.5-1.9)
    3.9f,-0.7f,1.9f, 0,1,0, 0,0,
    3.5f,-0.7f,1.9f, 0,1,0, 1,0,
    3.5f,-0.7f,1.5f, 0,1,0, 1,1,
    3.9f,-0.7f,1.5f, 0,1,0, 0,1,
    3.9f,-2.7f,1.9f, 0,-1,0, 0,0,
    3.5f,-2.7f,1.9f, 0,-1,0, 1,0,
    3.5f,-2.7f,1.5f, 0,-1,0, 1,1,
    3.9f,-2.7f,1.5f, 0,-1,0, 0,1,

    // Prawa tylna (Z: -1.5 do -1.9)
    3.9f,-0.7f,-1.5f, 0,1,0, 0,0,
    3.5f,-0.7f,-1.5f, 0,1,0, 1,0,
    3.5f,-0.7f,-1.9f, 0,1,0, 1,1,
    3.9f,-0.7f,-1.9f, 0,1,0, 0,1,
    3.9f,-2.7f,-1.5f, 0,-1,0, 0,0,
    3.5f,-2.7f,-1.5f, 0,-1,0, 1,0,
    3.5f,-2.7f,-1.9f, 0,-1,0, 1,1,
    3.9f,-2.7f,-1.9f, 0,-1,0, 0,1,

    // Lewa przednia (X: -3.9 do -3.5, Z: 1.5-1.9)
    -3.5f,-0.7f,1.9f, 0,1,0, 0,0,
    -3.9f,-0.7f,1.9f, 0,1,0, 1,0,
    -3.9f,-0.7f,1.5f, 0,1,0, 1,1,
    -3.5f,-0.7f,1.5f, 0,1,0, 0,1,
    -3.5f,-2.7f,1.9f, 0,-1,0, 0,0,
    -3.9f,-2.7f,1.9f, 0,-1,0, 1,0,
    -3.9f,-2.7f,1.5f, 0,-1,0, 1,1,
    -3.5f,-2.7f,1.5f, 0,-1,0, 0,1,

    // Lewa tylna (Z: -1.5 do -1.9)
    -3.5f,-0.7f,-1.5f, 0,1,0, 0,0,
    -3.9f,-0.7f,-1.5f, 0,1,0, 1,0,
    -3.9f,-0.7f,-1.9f, 0,1,0, 1,1,
    -3.5f,-0.7f,-1.9f, 0,1,0, 0,1,
    -3.5f,-2.7f,-1.5f, 0,-1,0, 0,0,
    -3.9f,-2.7f,-1.5f, 0,-1,0, 1,0,
    -3.9f,-2.7f,-1.9f, 0,-1,0, 1,1,
    -3.5f,-2.7f,-1.9f, 0,-1,0, 0,1
};


GLuint legIndices[] = {
    // Noga prawa przednia (offset 0)
    0,1,2, 0,2,3, 4,5,6, 4,6,7, 0,4,5, 0,5,1, 3,7,6, 3,6,2, 1,5,6, 1,6,2, 0,4,7, 0,7,3,
    // Prawa tylna (offset 8)
    8 + 0,8 + 1,8 + 2, 8 + 0,8 + 2,8 + 3, 8 + 4,8 + 5,8 + 6, 8 + 4,8 + 6,8 + 7, 8 + 0,8 + 4,8 + 5, 8 + 0,8 + 5,8 + 1, 8 + 3,8 + 7,8 + 6, 8 + 3,8 + 6,8 + 2, 8 + 1,8 + 5,8 + 6, 8 + 1,8 + 6,8 + 2, 8 + 0,8 + 4,8 + 7, 8 + 0,8 + 7,8 + 3,
    // Lewa przednia (offset 16)
    16 + 0,16 + 1,16 + 2, 16 + 0,16 + 2,16 + 3, 16 + 4,16 + 5,16 + 6, 16 + 4,16 + 6,16 + 7, 16 + 0,16 + 4,16 + 5, 16 + 0,16 + 5,16 + 1, 16 + 3,16 + 7,16 + 6, 16 + 3,16 + 6,16 + 2, 16 + 1,16 + 5,16 + 6, 16 + 1,16 + 6,16 + 2, 16 + 0,16 + 4,16 + 7, 16 + 0,16 + 7,16 + 3,
    // Lewa tylna (offset 24)
    24 + 0,24 + 1,24 + 2, 24 + 0,24 + 2,24 + 3, 24 + 4,24 + 5,24 + 6, 24 + 4,24 + 6,24 + 7, 24 + 0,24 + 4,24 + 5, 24 + 0,24 + 5,24 + 1, 24 + 3,24 + 7,24 + 6, 24 + 3,24 + 6,24 + 2, 24 + 1,24 + 5,24 + 6, 24 + 1,24 + 6,24 + 2, 24 + 0,24 + 4,24 + 7, 24 + 0,24 + 7,24 + 3
};


Desk::Desk() {
    vaoTop.Bind();
    vboTop = VBO(deskVertices, sizeof(deskVertices));
    eboTop = EBO(deskIndices, sizeof(deskIndices));
    vaoTop.LinkAttrib(vboTop, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoTop.LinkAttrib(vboTop, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoTop.LinkAttrib(vboTop, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoTop.Unbind(); vboTop.Unbind(); eboTop.Unbind();

    vaoLegs.Bind();
    vboLegs = VBO(legVertices, sizeof(legVertices));
    eboLegs = EBO(legIndices, sizeof(legIndices));
    vaoLegs.LinkAttrib(vboLegs, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoLegs.LinkAttrib(vboLegs, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoLegs.LinkAttrib(vboLegs, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoLegs.Unbind(); vboLegs.Unbind(); eboLegs.Unbind();
}

// Dodajemy funkcję Draw z osobnymi teksturami
void Desk::Draw(Shader& shader, Texture& topTex, Texture& legTex) {
    // Blat
    topTex.Bind();
    vaoTop.Bind();
    shader.SetMat4("model", glm::mat4(1.0f));
    glDrawElements(GL_TRIANGLES, sizeof(deskIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Nogi
    legTex.Bind();
    vaoLegs.Bind();
    shader.SetMat4("model", glm::mat4(1.0f));
    glDrawElements(GL_TRIANGLES, sizeof(legIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Desk::Delete() {
    vaoTop.Delete(); vboTop.Delete(); eboTop.Delete();
    vaoLegs.Delete(); vboLegs.Delete(); eboLegs.Delete();
}