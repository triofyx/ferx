#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>


class Shader
{
public:
    Shader() = default;
    Shader(const std::string& vPath, const std::string& fPath);
    ~Shader();

    void Use() const;
    int GetUniformLocation(const std::string& name);

private:
    unsigned int m_ID{};
    std::unordered_map<std::string, int> m_Uniforms{};
};