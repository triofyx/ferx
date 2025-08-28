#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "FrameBuffer.h"
#include "Window.h"
#include "Input.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Cube.h"

class Window;

struct RendererData
{
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<FrameBuffer> m_FBO;
    std::unique_ptr<Scene> m_Scene;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Camera> m_Camera;
    std::shared_ptr<Cube> m_Cube;

    glm::vec3 m_ClearColor;
};

class Renderer
{
public:
    explicit Renderer(Window* window);
    ~Renderer() = default;

    void Render();
    void Shutdown();

    RendererData& GetData() { return m_Data; };

private:
    Window* m_Window;
    RendererData m_Data;

    void SetVariables();
    void LoadShaders();
    void SetupBuffers();
    void SetCallbacks() const;
    void ProcessInput(GLFWwindow* window);

    void OnWindowResize(int width, int height) const;
    void OnMouseScroll(float yOffset) const;

    float m_DeltaTime = 0.0f;
    float m_LastFrame = 0.0f;

    bool m_FirstMouse = true;
    float m_LastX = 0.0f;
    float m_LastY = 0.0f;
};