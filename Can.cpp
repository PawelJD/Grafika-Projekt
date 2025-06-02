#include "Can.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

Can::Can(float radius, float height, unsigned int sectorCount) {
    const float PI = 3.1415926f;

    // ================= Œciany puszki =================
    for (unsigned int i = 0; i <= sectorCount; ++i) {
        float angle = i * 2 * PI / sectorCount;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);
        float nx = cosf(angle); // normalny x
        float nz = sinf(angle); // normalny z
        float s = 1.0f - (float)i / sectorCount;

        // Dolny i górny punkt œciany
        sideVertices.insert(sideVertices.end(), { x, -height / 2, z, nx, 0, nz, s, 0 });
        sideVertices.insert(sideVertices.end(), { x, height / 2, z, nx, 0, nz, s, 1 });
    }
    for (unsigned int i = 0; i < sectorCount; ++i) {
        unsigned int k1 = i * 2;
        unsigned int k2 = k1 + 1;
        unsigned int k3 = ((i + 1) % sectorCount) * 2;
        unsigned int k4 = k3 + 1;
        sideIndices.insert(sideIndices.end(), { k1,k3,k2, k2,k3,k4 });
    }

    vaoSide.Bind();
    vboSide = VBO(sideVertices.data(), sideVertices.size() * sizeof(float));
    eboSide = EBO(sideIndices.data(), sideIndices.size() * sizeof(unsigned int));
    vaoSide.LinkAttrib(vboSide, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // position
    vaoSide.LinkAttrib(vboSide, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // normal
    vaoSide.LinkAttrib(vboSide, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texcoord
    vaoSide.Unbind(); vboSide.Unbind(); eboSide.Unbind();

    // ================= Górna pokrywka =================
    unsigned int centerIndexTop = 0;
    topVertices.insert(topVertices.end(), { 0, height / 2, 0, 0, 1, 0, 0.5f, 0.5f });
    for (unsigned int i = 0; i <= sectorCount; ++i) {
        float angle = i * 2 * PI / sectorCount;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);
        float s = (cosf(angle) + 1) / 2;
        float t = (sinf(angle) + 1) / 2;
        topVertices.insert(topVertices.end(), { x, height / 2, z, 0, 1, 0, s, t });
    }
    for (unsigned int i = 1; i <= sectorCount; ++i) {
        topIndices.insert(topIndices.end(), { centerIndexTop, i, i + 1 });
    }

    vaoTop.Bind();
    vboTop = VBO(topVertices.data(), topVertices.size() * sizeof(float));
    eboTop = EBO(topIndices.data(), topIndices.size() * sizeof(unsigned int));
    vaoTop.LinkAttrib(vboTop, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoTop.LinkAttrib(vboTop, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoTop.LinkAttrib(vboTop, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoTop.Unbind(); vboTop.Unbind(); eboTop.Unbind();

    // ================= Dolna pokrywka =================
    unsigned int centerIndexBottom = 0;
    bottomVertices.insert(bottomVertices.end(), { 0, -height / 2, 0, 0, -1, 0, 0.5f, 0.5f });
    for (unsigned int i = 0; i <= sectorCount; ++i) {
        float angle = i * 2 * PI / sectorCount;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);
        float s = (cosf(angle) + 1) / 2;
        float t = (sinf(angle) + 1) / 2;
        bottomVertices.insert(bottomVertices.end(), { x, -height / 2, z, 0, -1, 0, s, t });
    }
    for (unsigned int i = 1; i <= sectorCount; ++i) {
        bottomIndices.insert(bottomIndices.end(), { centerIndexBottom, i + 1, i });
    }

    vaoBottom.Bind();
    vboBottom = VBO(bottomVertices.data(), bottomVertices.size() * sizeof(float));
    eboBottom = EBO(bottomIndices.data(), bottomIndices.size() * sizeof(unsigned int));
    vaoBottom.LinkAttrib(vboBottom, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoBottom.LinkAttrib(vboBottom, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoBottom.LinkAttrib(vboBottom, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoBottom.Unbind(); vboBottom.Unbind(); eboBottom.Unbind();
}

void Can::DrawSide(Shader& shader) {
    vaoSide.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0f, -0.335f, 0.5f));
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, sideIndices.size(), GL_UNSIGNED_INT, 0);
}

void Can::DrawTop(Shader& shader) {
    vaoTop.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0f, -0.34f, 0.5f));
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, topIndices.size(), GL_UNSIGNED_INT, 0);
}

void Can::DrawBottom(Shader& shader) {
    vaoBottom.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.5f, -0.1f, 0.5f));
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, bottomIndices.size(), GL_UNSIGNED_INT, 0);
}

void Can::Delete() {
    vaoSide.Delete(); vboSide.Delete(); eboSide.Delete();
    vaoTop.Delete(); vboTop.Delete(); eboTop.Delete();
    vaoBottom.Delete(); vboBottom.Delete(); eboBottom.Delete();
}
