#include <filesystem>
namespace fs = std::filesystem;

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Sphere.h"
#include "Stand.h"
#include "Desk.h"
#include "Can.h"
#include "Book.h"
#include "Pad.h"
#include "RubiksCube.h"
#include "Laptop.h"
#include "Lamp.h"

const unsigned int width = 1912;
const unsigned int height = 1024;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Projekt Grafika", NULL, NULL);
    if (!window) { std::cout << "Failed to create GLFW window" << std::endl; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");
    Shader lightShader("shaders/light.vert", "shaders/light.frag");
    Shader postShader("shaders/postprocess.vert", "shaders/postprocess.frag");
    Shader blurShader("shaders/postprocess.vert", "shaders/rozmycie.frag");
    Shader bwShader("shaders/postprocess.vert", "shaders/czarnobialy.frag");

    Sphere sphere(0.65f, 36, 18);
    Stand stand; 
    Desk desk; 
    Can can(0.1f, 0.5f, 144);
    Book book;
    Pad pad; 
    RubiksCube rubik(0.2f); 
    Laptop laptop; 
    Lamp lamp;

    Texture sphereTex("textures/ziemia3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture woodTex("textures/wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture deskTex("textures/desk2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture legsTex("textures/nogi.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture canTex("textures/redbull.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture upside("textures/zawleczka.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture baseTex("textures/tyl.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture middleTex("textures/kartki.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture coverTex("textures/the_book.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture padTex("textures/Pad.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture rubikTex("textures/rubik.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture keyboardTex("textures/klawiatura.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture monitorTex("textures/dell.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture screenTex("textures/xp.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture lampTex("textures/nogi.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));

    GLfloat lightVertices[] = { -0.1f,-0.1f,-0.1f, 0.1f,-0.1f,-0.1f, 0.1f,0.1f,-0.1f, -0.1f,0.1f,-0.1f, -0.1f,-0.1f,0.1f, 0.1f,-0.1f,0.1f, 0.1f,0.1f,0.1f, -0.1f,0.1f,0.1f };
    GLuint lightIndices[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 0,1,5, 0,5,4, 1,2,6, 1,6,5, 2,3,7, 2,7,6, 3,0,4, 3,4,7 };
    VAO lightVAO; lightVAO.Bind(); VBO lightVBO(lightVertices, sizeof(lightVertices)); EBO lightEBO(lightIndices, sizeof(lightIndices));
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); lightVAO.Unbind();

    unsigned int framebuffer, texColorBuffer, rbo;
    glGenFramebuffers(1, &framebuffer); glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(1, &texColorBuffer); glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
    glGenRenderbuffers(1, &rbo); glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    unsigned int pingpongFBO[2], pingpongTex[2];
    glGenFramebuffers(2, pingpongFBO); glGenTextures(2, pingpongTex);
    for (int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongTex[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongTex[i], 0);
    }

    float quadVertices[] = { -1.0f,1.0f,0.0f,1.0f, -1.0f,-1.0f,0.0f,0.0f, 1.0f,-1.0f,1.0f,0.0f, 1.0f,1.0f,1.0f,1.0f };
    unsigned int quadIndices[] = { 0,1,2, 0,2,3 };
    VAO quadVAO; quadVAO.Bind(); VBO quadVBO(quadVertices, sizeof(quadVertices)); EBO quadEBO(quadIndices, sizeof(quadIndices));
    quadVAO.LinkAttrib(quadVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
    quadVAO.LinkAttrib(quadVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float))); quadVAO.Unbind();

    int filterMode = 0;

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) filterMode = 0;
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) filterMode = 1;
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) filterMode = 2;

        // Obliczenia światła i tła
        float time = glfwGetTime() * 0.4f;
        float lightX = cos(time) * 15.0f;
        float lightY = sin(time) * 15.0f;
        glm::vec3 lightPos(lightX, lightY, 0.0f);
        float brightness = glm::clamp((lightY / 15.0f + 1.0f) / 2.0f, 0.2f, 1.0f);
        glm::vec4 lightColor = glm::vec4(brightness * 10.0f);
        float lightIntensityDynamic = brightness * 20.0f;
        glm::vec3 backgroundColor = glm::vec3(0.9f, 0.9f, 0.9f) * brightness;

        glm::vec3 lampLightPos = glm::vec3(1.118f, 0.23f, -0.2f);
        glm::vec4 lampLightColor = glm::vec4(1.0f, 1.0f, 0.8f, 1.0f);

        // Render do framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST);
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();
        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        shaderProgram.setVec3("lightPos", lightPos);
        shaderProgram.setVec4("lightColor", lightColor);
        shaderProgram.setFloat("lightIntensity", lightIntensityDynamic);
        shaderProgram.setVec3("lampLightPos", lampLightPos);
        shaderProgram.setVec4("lampLightColor", lampLightColor);
        shaderProgram.setFloat("lampIntensity", 300.0f);

        // Rysowanie biurka
        deskTex.Bind(); desk.Draw(shaderProgram, deskTex, legsTex);
        woodTex.Bind(); stand.Draw(shaderProgram);

        //rysowanie globusa
        sphereTex.Bind(); sphere.Draw(shaderProgram);

        //rysowanie puszki 
        canTex.Bind(); can.DrawSide(shaderProgram); 

        //pokrywka
        upside.Bind(); can.DrawTop(shaderProgram);

        //rysowanie książki
        coverTex.Bind(); book.Draw(shaderProgram, baseTex, middleTex, coverTex);

        //rysowanie podkładki
        padTex.Bind(); pad.Draw(shaderProgram, padTex);

        //kostka rubika
        rubikTex.Bind(); rubik.Draw(shaderProgram, glm::vec3(-2.5f, -0.5f, 0.3f));

        //laptop
        laptop.Draw(shaderProgram, keyboardTex, monitorTex, screenTex);

        //lampka
        lamp.Draw(shaderProgram, lampTex);

        // Dynamiczne źródło światła
        lightShader.Activate();
        camera.Matrix(45.0f, 0.1f, 100.0f, lightShader, "camMatrix");
        //glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
        //sglUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), lampLightPos);
        model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
        model = glm::scale(model, glm::vec3(0.5f, 0.1f, 1.2f));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lampLightColor.r, lampLightColor.g, lampLightColor.b, lampLightColor.a);
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Blur (jeśli aktywny)
        bool horizontal = true, first_iteration = true;
        if (filterMode == 1) {
            blurShader.Activate();
            for (int i = 0; i < 10; i++) {
                glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
                glUniform2f(glGetUniformLocation(blurShader.ID, "blurDirection"), horizontal ? 1.0f : 0.0f, horizontal ? 0.0f : 1.0f);
                glBindTexture(GL_TEXTURE_2D, first_iteration ? texColorBuffer : pingpongTex[!horizontal]);
                quadVAO.Bind();
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                horizontal = !horizontal;
                if (first_iteration) first_iteration = false;
            }
        }

        // Postprocessing na ekran
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Shader* activeShader = (filterMode == 2) ? &bwShader : &postShader;
        activeShader->Activate();
        glBindTexture(GL_TEXTURE_2D, (filterMode == 1) ? pingpongTex[!horizontal] : texColorBuffer);
        quadVAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup zasobów
    sphere.Delete();
    stand.Delete();
    desk.Delete();
    can.Delete();
    book.Delete();
    pad.Delete();
    rubik.Delete();
    laptop.Delete();
    lamp.Delete();

    sphereTex.Delete(); woodTex.Delete(); deskTex.Delete(); legsTex.Delete();
    canTex.Delete(); upside.Delete(); baseTex.Delete(); middleTex.Delete();
    coverTex.Delete(); padTex.Delete(); rubikTex.Delete();
    keyboardTex.Delete(); monitorTex.Delete(); screenTex.Delete(); lampTex.Delete();

    shaderProgram.Delete();
    lightShader.Delete();
    postShader.Delete();
    blurShader.Delete();
    bwShader.Delete();

    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    quadVAO.Delete();
    quadVBO.Delete();
    quadEBO.Delete();

    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &texColorBuffer);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(2, pingpongFBO);
    glDeleteTextures(2, pingpongTex);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
