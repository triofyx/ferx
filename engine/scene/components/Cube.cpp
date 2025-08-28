#include "Cube.h"

std::vector<float> Cube::s_Vertices = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f
};

std::vector<unsigned int> Cube::s_Indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    0, 1, 5, 5, 4, 0,
    2, 3, 7, 7, 6, 2,
    0, 3, 7, 7, 4, 0,
    1, 2, 6, 6, 5, 1
};

Cube::Cube(const std::string& cubeName)
{
    name = cubeName;
}

void Cube::Draw()
{
    m_ModelMatrix = glm::mat4(1.0f);

    if(length(m_Position) != 0)
        m_ModelMatrix = translate(m_ModelMatrix, m_Position);

    if(length(m_Rotation) != 0)
        m_ModelMatrix = rotate(m_ModelMatrix, glm::radians(length(m_Rotation)), normalize(m_Rotation));

    if(length(m_Scale) != 0)
        m_ModelMatrix = scale(m_ModelMatrix, m_Scale);
}

