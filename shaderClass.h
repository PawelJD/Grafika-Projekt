#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

std::string get_file_contents(const char* filename);

class Shader
{
public:
    // Reference ID of the Shader Program
    GLuint ID;

    // Constructor that builds the Shader Program from vertex and fragment shaders
    Shader(const char* vertexFile, const char* fragmentFile);

    // Activate the Shader Program
    void Activate();

    // Delete the Shader Program
    void Delete();

    // Utility uniform functions
    void SetMat4(const std::string& name, const glm::mat4& mat) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& vec) const;
    void setVec4(const std::string& name, const glm::vec4& vec) const;



private:
    // Check if shader compiled properly
    void compileErrors(unsigned int shader, const char* type);
};

#endif
