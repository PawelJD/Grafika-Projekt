#include "RubiksCube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

RubiksCube::RubiksCube(float size) {
    float s = size / 2.0f;

    // Wspó³rzêdne UV dopasowane do T-shape (1024x768)
    const float scaleU = 1.0f / 4.0f;
    const float scaleV = 1.0f / 3.0f;

    struct UVOffset {
        float u, v;
    };
    UVOffset offsets[6] = {
        { scaleU, scaleV },     // back   (œrodek)
        { 2 * scaleU, scaleV },   // front  (prawa)
        { 0, scaleV },          // left   (lewa)
        { 3 * scaleU, scaleV },   // right  (skrajna prawa)
        { scaleU, 0 },          // bottom (dó³)
        { scaleU, 2 * scaleV }    // top    (góra)
    };

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    auto addFace = [&](glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int faceIndex) {
        UVOffset o = offsets[faceIndex];
        int base = vertices.size() / 8;
        glm::vec3 color(1, 1, 1);
        vertices.insert(vertices.end(), {
            v0.x,v0.y,v0.z, color.r,color.g,color.b, o.u, o.v + scaleV,
            v1.x,v1.y,v1.z, color.r,color.g,color.b, o.u + scaleU, o.v + scaleV,
            v2.x,v2.y,v2.z, color.r,color.g,color.b, o.u + scaleU, o.v,
            v3.x,v3.y,v3.z, color.r,color.g,color.b, o.u, o.v
            });
        indices.insert(indices.end(), {
            (GLuint)base, (GLuint)base + 1, (GLuint)base + 2,
            (GLuint)base, (GLuint)base + 2, (GLuint)base + 3
            });
    };

    // Kostka Rubika: 6 œcian
    addFace(glm::vec3(-s, -s, -s), glm::vec3(s, -s, -s), glm::vec3(s, s, -s), glm::vec3(-s, s, -s), 0); // back
    addFace(glm::vec3(-s, -s, s), glm::vec3(s, -s, s), glm::vec3(s, s, s), glm::vec3(-s, s, s), 1);    // front
    addFace(glm::vec3(-s, -s, -s), glm::vec3(-s, s, -s), glm::vec3(-s, s, s), glm::vec3(-s, -s, s), 2);// left
    addFace(glm::vec3(s, -s, -s), glm::vec3(s, s, -s), glm::vec3(s, s, s), glm::vec3(s, -s, s), 3);    // right
    addFace(glm::vec3(-s, -s, -s), glm::vec3(-s, -s, s), glm::vec3(s, -s, s), glm::vec3(s, -s, -s), 4);// bottom
    addFace(glm::vec3(-s, s, -s), glm::vec3(-s, s, s), glm::vec3(s, s, s), glm::vec3(s, s, -s), 5);    // top

    indexCount = (GLsizei)indices.size();

    vao.Bind();
    vbo = VBO(vertices.data(), vertices.size() * sizeof(GLfloat));
    ebo = EBO(indices.data(), indices.size() * sizeof(GLuint));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind(); vbo.Unbind(); ebo.Unbind();
}

void RubiksCube::Draw(Shader& shader, glm::vec3 position) {
    float angle = glm::radians(45.0f);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = glm::rotate(model, angle, glm::vec3(0.0f, -1.0f, 0.0f));
    shader.SetMat4("model", model);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void RubiksCube::Delete() {
    vao.Delete(); vbo.Delete(); ebo.Delete();
}
