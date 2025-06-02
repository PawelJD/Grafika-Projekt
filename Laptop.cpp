#include "Laptop.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Dane dla prostopad�o�cian�w
static GLfloat cuboidVertices[] = {
    // positions            // colors       // texcoords
    -0.5f, -0.5f,  0.5f, 1,1,1, 0,0,
     0.5f, -0.5f,  0.5f, 1,1,1, 1,0,
     0.5f,  0.5f,  0.5f, 1,1,1, 1,1,
    -0.5f,  0.5f,  0.5f, 1,1,1, 0,1,

    -0.5f, -0.5f, -0.5f, 1,1,1, 0,0,
     0.5f, -0.5f, -0.5f, 1,1,1, 1,0,
     0.5f,  0.5f, -0.5f, 1,1,1, 1,1,
    -0.5f,  0.5f, -0.5f, 1,1,1, 0,1
};

static GLuint cuboidIndices[] = {
    0,1,2, 0,2,3,
    4,5,6, 4,6,7,
    0,1,5, 0,5,4,
    2,3,7, 2,7,6,
    0,3,7, 0,7,4,
    1,2,6, 1,6,5
};

// Klawiatura � tekstura tylko na g�rnej �cianie
GLfloat keyboardVertices[] = {
    // positions            // colors      // texcoords
    // G�rna �ciana (keyboard top face)
    -0.5f,  0.5f,  0.5f, 1,1,1, 0,0,
     0.5f,  0.5f,  0.5f, 1,1,1, 1,0,
     0.5f,  0.5f, -0.5f, 1,1,1, 1,1,
    -0.5f,  0.5f, -0.5f, 1,1,1, 0,1,

    // Pozosta�e wierzcho�ki � bez tekstur (UV = 0)
    -0.5f, -0.5f,  0.5f, 1,1,1, 0,0,
     0.5f, -0.5f,  0.5f, 1,1,1, 0,0,
     0.5f, -0.5f, -0.5f,1,1,1, 0,0,
    -0.5f, -0.5f, -0.5f,1,1,1, 0,0
};

Laptop::Laptop() : Laptop(1.0f, 0.05f, 0.6f, 1.0f, 0.7f, 0.05f, 0.1f) {}

Laptop::Laptop(float bw, float bh, float bd, float mw, float mh, float md, float screenInset) {
    vaoBase.Bind();
    vboBase = VBO(keyboardVertices, sizeof(keyboardVertices));
    eboBase = EBO(cuboidIndices, sizeof(cuboidIndices));
    vaoBase.LinkAttrib(vboBase, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoBase.LinkAttrib(vboBase, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoBase.LinkAttrib(vboBase, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoBase.Unbind(); vboBase.Unbind(); eboBase.Unbind();

    vaoMonitor.Bind();
    vboMonitor = VBO(cuboidVertices, sizeof(cuboidVertices));
    eboMonitor = EBO(cuboidIndices, sizeof(cuboidIndices));
    vaoMonitor.LinkAttrib(vboMonitor, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoMonitor.LinkAttrib(vboMonitor, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoMonitor.LinkAttrib(vboMonitor, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoMonitor.Unbind(); vboMonitor.Unbind(); eboMonitor.Unbind();

    vaoScreen.Bind();
    vboScreen = VBO(cuboidVertices, sizeof(cuboidVertices));
    eboScreen = EBO(cuboidIndices, sizeof(cuboidIndices));
    vaoScreen.LinkAttrib(vboScreen, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoScreen.LinkAttrib(vboScreen, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoScreen.LinkAttrib(vboScreen, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoScreen.Unbind(); vboScreen.Unbind(); eboScreen.Unbind();
}

void Laptop::Draw(Shader& shader, Texture& keyboardTex, Texture& monitorTex, Texture& screenTex) {
    // Klawiatura
    keyboardTex.Bind();
    keyboardTex.texUnit(shader, "tex0", 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.58f, 0.025f));
    model = glm::scale(model, glm::vec3(1.23f, 0.03f, 0.7f));
    shader.SetMat4("model", model);
    vaoBase.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Monitor
    monitorTex.Bind();
    monitorTex.texUnit(shader, "tex0", 0);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.25f, -0.395f)); 
    model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.23f, 0.7f, 0.02f));
    shader.SetMat4("model", model);
    vaoMonitor.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Ekran
    screenTex.Bind();
    screenTex.texUnit(shader, "tex0", 0);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.23f, -0.3925f));
    model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.2f, 0.59f, 0.005f));
    shader.SetMat4("model", model);
    vaoScreen.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Laptop::Delete() {
    vaoBase.Delete(); vboBase.Delete(); eboBase.Delete();
    vaoMonitor.Delete(); vboMonitor.Delete(); eboMonitor.Delete();
    vaoScreen.Delete(); vboScreen.Delete(); eboScreen.Delete();
}
