#include "Sphere.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

Sphere::Sphere(float radius, unsigned int sectorCount, unsigned int stackCount)
{
    const float PI = 3.1415926f;
    for (unsigned int i = 0; i <= stackCount; ++i) {
        float stackAngle = PI / 2 - i * PI / stackCount;  // od pi/2 (biegun p�nocny) do -pi/2 (biegun po�udniowy)
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (unsigned int j = 0; j <= sectorCount; ++j) {
            float sectorAngle = j * 2 * PI / sectorCount;  // od 0 do 2pi (pe�ny obw�d)
            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            float s = (float)j / sectorCount;  // d�ugo�� geograficzna (U)
            float t = (float)i / stackCount;   // szeroko�� geograficzna (V)

            // Opcjonalnie, je�li tekstura ma odwrotn� orientacj� poziom�
            // s = 1.0f - s;

            vertices.push_back(y);
            vertices.push_back(x);
            vertices.push_back(z);
            vertices.push_back(1.0f);  // kolor
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(s);  // odwr�cenie poziome
            vertices.push_back(t);     // V (szeroko�� geograficzna)
        }
    }

    for (unsigned int i = 0; i < stackCount; ++i) {
        unsigned int k1 = i * (sectorCount + 1);
        unsigned int k2 = k1 + sectorCount + 1;
        for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    vao.Bind();
    vbo = VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = EBO(indices.data(), indices.size() * sizeof(unsigned int));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind(); vbo.Unbind(); ebo.Unbind();
}

void Sphere::Draw(Shader& shader)
{
    vao.Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.2f, -1.5f));

    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.3f, 0.0f));  // O� X
    // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // O� Y
    // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));  // O� Z

    float angle = (float)glfwGetTime() * 50.0f;  // 50 stopni na sekund�
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::Delete()
{
    vao.Delete(); vbo.Delete(); ebo.Delete();
}
