#include "Book.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Uniwersalny prostopad³oœcian
GLfloat cuboidVertices[] = {
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

GLuint cuboidIndices[] = {
    0,1,2, 0,2,3,    4,5,6, 4,6,7,
    8,9,10, 8,10,11, 12,13,14, 12,14,15,
    16,17,18, 16,18,19, 20,21,22, 20,22,23
};

Book::Book() {
    vaoBase.Bind();
    vboBase = VBO(cuboidVertices, sizeof(cuboidVertices));
    eboBase = EBO(cuboidIndices, sizeof(cuboidIndices));
    vaoBase.LinkAttrib(vboBase, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoBase.LinkAttrib(vboBase, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoBase.LinkAttrib(vboBase, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoBase.Unbind(); vboBase.Unbind(); eboBase.Unbind();

    vaoMiddle.Bind();
    vboMiddle = VBO(cuboidVertices, sizeof(cuboidVertices));
    eboMiddle = EBO(cuboidIndices, sizeof(cuboidIndices));
    vaoMiddle.LinkAttrib(vboMiddle, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoMiddle.LinkAttrib(vboMiddle, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoMiddle.LinkAttrib(vboMiddle, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoMiddle.Unbind(); vboMiddle.Unbind(); eboMiddle.Unbind();

    vaoCover.Bind();
    vboCover = VBO(cuboidVertices, sizeof(cuboidVertices));
    eboCover = EBO(cuboidIndices, sizeof(cuboidIndices));
    vaoCover.LinkAttrib(vboCover, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoCover.LinkAttrib(vboCover, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoCover.LinkAttrib(vboCover, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoCover.Unbind(); vboCover.Unbind(); eboCover.Unbind();

    vaoSpine.Bind();
    vboSpine = VBO(cuboidVertices, sizeof(cuboidVertices));
    eboSpine = EBO(cuboidIndices, sizeof(cuboidIndices));
    vaoSpine.LinkAttrib(vboSpine, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoSpine.LinkAttrib(vboSpine, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoSpine.LinkAttrib(vboSpine, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoSpine.Unbind(); vboSpine.Unbind(); eboSpine.Unbind();

}

void Book::Draw(Shader& shader, Texture& baseTex, Texture& middleTex, Texture& coverTex) {
    float angle = glm::radians(45.0f);
    // Podstawa (tylna ok³adka)
    baseTex.Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(3.0, -0.59f, -0.5));
    model = glm::rotate(model, angle, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 0.01f, 1.0f));
    shader.SetMat4("model", model);
    vaoBase.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Œrodek (kartki)
    middleTex.Bind();
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.99f, -0.51f, -0.5f));
    model = glm::rotate(model, angle, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.96f, 0.15f, 0.95f));
    shader.SetMat4("model", model);
    vaoMiddle.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Przednia ok³adka – pe³ny prostopad³oœcian
    coverTex.Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(3.0, -0.43f, -0.5));
    model = glm::rotate(model, angle, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 0.01f, 1.0f));

    shader.SetMat4("model", model);
    vaoCover.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Grzbiet (zamykaj¹cy po lewej)
    baseTex.Bind(); 
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.72f, -0.51f, -0.78)); 
    model = glm::rotate(model, angle, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.01f, 0.15f, 1.0f));   // Cienki, wysoki, g³êboki
    shader.SetMat4("model", model);
    vaoSpine.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

}

void Book::Delete() {
    vaoBase.Delete(); vboBase.Delete(); eboBase.Delete();
    vaoMiddle.Delete(); vboMiddle.Delete(); eboMiddle.Delete();
    vaoCover.Delete(); vboCover.Delete(); eboCover.Delete();
    vaoSpine.Delete(); vboSpine.Delete(); eboSpine.Delete();

}
