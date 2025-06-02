#include "Pad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Uniwersalny prostopad³oœcian
GLfloat padVertices[] = {
    // Pozycja         Normal        TexCoord
    -0.4f, -0.5f,  0.5f, 0,0,1,  0,0,
     0.4f, -0.5f,  0.5f, 0,0,1,  1,0,
     0.4f,  0.5f,  0.5f, 0,0,1,  1,1,
    -0.4f,  0.5f,  0.5f, 0,0,1,  0,1,

    -0.4f, -0.5f, -0.5f, 0,0,-1, 0,0,
     0.4f, -0.5f, -0.5f, 0,0,-1, 1,0,
     0.4f,  0.5f, -0.5f, 0,0,-1, 1,1,
    -0.4f,  0.5f, -0.5f, 0,0,-1, 0,1,

    -0.4f,  0.5f,  0.5f, 0,1,0,  0,0,
     0.4f,  0.5f,  0.5f, 0,1,0,  1,0,
     0.4f,  0.5f, -0.5f, 0,1,0,  1,1,
    -0.4f,  0.5f, -0.5f, 0,1,0,  0,1,

    -0.4f, -0.5f,  0.5f, 0,-1,0, 0,0,
     0.4f, -0.5f,  0.5f, 0,-1,0, 1,0,
     0.4f, -0.5f, -0.5f, 0,-1,0, 1,1,
    -0.4f, -0.5f, -0.5f, 0,-1,0,  0,1,

     0.4f, -0.5f,  0.5f, 1,0,0,  0,0,
     0.4f, -0.5f, -0.5f, 1,0,0, 1,0,
     0.4f,  0.5f, -0.5f, 1,0,0, 1,1,
     0.4f,  0.5f,  0.5f, 1,0,0,  0,1,

    -0.4f, -0.5f,  0.5f, -1,0,0, 0,0,
    -0.4f, -0.5f, -0.5f, -1,0,0, 1,0,
    -0.4f,  0.5f, -0.5f, -1,0,0, 1,1,
    -0.4f,  0.5f,  0.5f, -1,0,0, 0,1
};

GLuint padIndices[] = {
    0,1,2, 0,2,3,    4,5,6, 4,6,7,
    8,9,10, 8,10,11, 12,13,14, 12,14,15,
    16,17,18, 16,18,19, 20,21,22, 20,22,23
};

Pad::Pad() {
    vaoPad.Bind();
    vboPad = VBO(padVertices, sizeof(padVertices));
    eboPad = EBO(padIndices, sizeof(padIndices));
    vaoPad.LinkAttrib(vboPad, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoPad.LinkAttrib(vboPad, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoPad.LinkAttrib(vboPad, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoPad.Unbind(); vboPad.Unbind(); eboPad.Unbind();
}

void Pad::Draw(Shader& shader, Texture& baseTex) {

    baseTex.Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -0.6f, 0.5));
    model = glm::scale(model, glm::vec3(4.0f, 0.01f, 2.0f));
    shader.SetMat4("model", model);
    vaoPad.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(padIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Pad::Delete() {
    vaoPad.Delete(); vboPad.Delete(); eboPad.Delete();
}