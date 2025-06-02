#include "Stand.h"

// Dane dla stojaka
GLfloat standVertices[] =
{
    -0.2f, -0.5f,  0.2f,   0.6f, 0.3f, 0.1f,  0.0f, 0.0f,
    -0.2f, -0.5f, -0.2f,   0.6f, 0.3f, 0.1f,  0.0f, 1.0f,
     0.2f, -0.5f, -0.2f,   0.6f, 0.3f, 0.1f,  1.0f, 1.0f,
     0.2f, -0.5f,  0.2f,   0.6f, 0.3f, 0.1f,  1.0f, 0.0f,
    -0.15f, -0.3f,  0.15f,  0.6f, 0.3f, 0.1f,  0.0f, 0.0f,
    -0.15f, -0.3f, -0.15f,  0.6f, 0.3f, 0.1f,  0.0f, 1.0f,
     0.15f, -0.3f, -0.15f,  0.6f, 0.3f, 0.1f,  1.0f, 1.0f,
     0.15f, -0.3f,  0.15f,  0.6f, 0.3f, 0.1f,  1.0f, 0.0f
};

GLuint standIndices[] = {
    0,1,2, 0,2,3, 4,5,6, 4,6,7,
    0,1,5, 0,5,4, 1,2,6, 1,6,5,
    2,3,7, 2,7,6, 3,0,4, 3,4,7
};

Stand::Stand() {
    vao.Bind();
    vbo = VBO(standVertices, sizeof(standVertices));
    ebo = EBO(standIndices, sizeof(standIndices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind(); vbo.Unbind(); ebo.Unbind();
}

void Stand::Draw(Shader& shader) {
    vao.Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, -0.1f, -1.5f));
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, sizeof(standIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);;
}

void Stand::Delete() {
    vao.Delete(); vbo.Delete(); ebo.Delete();
}
