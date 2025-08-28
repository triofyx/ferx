#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/glm.hpp>

class Cube{
public:
  explicit Cube(const std::string& cubeName);

  void Draw();

  glm::vec3 GetPosition() const{ return m_Position; }
  glm::vec3 GetRotation() const{ return m_Rotation; }
  glm::vec3 GetScale() const{ return m_Scale; }
  glm::vec3 GetShaderColor() const{ return m_ShaderColor; }
  glm::mat4 GetModelMatrix() const{ return m_ModelMatrix; }
  static std::vector<float>& GetVertices() { return s_Vertices; }
  static std::vector<unsigned int>& GetIndices() { return s_Indices; }

  void SetPosition(const glm::vec3& newPosition) { m_Position = newPosition; }
  void SetRotation(const glm::vec3 newRotation) { m_Rotation = newRotation; }
  void SetScale(const glm::vec3 newScale) { m_Scale = newScale; }
  void SetShaderColor(const glm::vec3& color) { m_ShaderColor = color; }

  std::string name;

private:
  glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
  glm::vec3 m_ShaderColor = glm::vec3(1.0f, 1.0f, 1.0f);

  static std::vector<float> s_Vertices;
  static std::vector<unsigned int> s_Indices;
};
