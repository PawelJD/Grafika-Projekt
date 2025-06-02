#include "Lamp.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Dane prostopad³oœcianu
static GLfloat cuboidVertices[] = {
    -0.5f,-0.5f, 0.5f, 1,1,1, 0,0,
     0.5f,-0.5f, 0.5f, 1,1,1, 1,0,
     0.5f, 0.5f, 0.5f, 1,1,1, 1,1,
    -0.5f, 0.5f, 0.5f, 1,1,1, 0,1,
    -0.5f,-0.5f,-0.5f, 1,1,1, 0,0,
     0.5f,-0.5f,-0.5f, 1,1,1, 1,0,
     0.5f, 0.5f,-0.5f, 1,1,1, 1,1,
    -0.5f, 0.5f,-0.5f, 1,1,1, 0,1
};
static GLuint cuboidIndices[] = {
    0,1,2, 0,2,3,
    4,5,6, 4,6,7,
    0,1,5, 0,5,4,
    2,3,7, 2,7,6,
    0,3,7, 0,7,4,
    1,2,6, 1,6,5
};

Lamp::Lamp() {
    vao.Bind();
    vbo = VBO(cuboidVertices, sizeof(cuboidVertices));
    ebo = EBO(cuboidIndices, sizeof(cuboidIndices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind(); vbo.Unbind(); ebo.Unbind();
}

void Lamp::Draw(Shader& shader, Texture& lampTex) {
    // Podstawa
    lampTex.Bind(); lampTex.texUnit(shader, "tex0", 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.3f, -0.57f, -0.7f));
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(0.3f, 0.05f, 0.6f));
    shader.SetMat4("model", model);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Ramiê (lekko nachylone)
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.3f, -0.13f, -0.7f));
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(-1, 0, 0));
    model = glm::scale(model, glm::vec3(0.05f, 1.0f, 0.05f));
    shader.SetMat4("model", model);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Belka pozioma
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.15f, 0.28f, -0.28f));
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.4f));
    shader.SetMat4("model", model);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Lampka (Ÿród³o œwiat³a)
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.118f, 0.26f, -0.2f));
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.3f));
    shader.SetMat4("model", model);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Lamp::Delete() {
    vao.Delete(); vbo.Delete(); ebo.Delete();
}
