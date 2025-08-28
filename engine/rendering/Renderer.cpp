#include "Renderer.h"

Renderer::Renderer(Window* window) : m_Window(window)
{
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    SetVariables();
    LoadShaders();
    SetupBuffers();
    SetCallbacks();
}

void Renderer::SetVariables()
{
    m_Data.m_Scene = std::make_unique<Scene>();
    m_Data.m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    m_Data.m_Cube = std::make_shared<Cube>("Cube");
    m_Data.m_ClearColor = glm::vec3(0.0f, 0.1f, 0.2f);

    m_Data.m_Scene->AddCube(m_Data.m_Cube);
}

void Renderer::LoadShaders()
{
    m_Data.m_Shader = std::make_unique<Shader>(ENGINE_RESOURCES_PATH"shaders/vertex.glsl", ENGINE_RESOURCES_PATH"shaders/fragment.glsl");
}

void Renderer::SetupBuffers()
{
    m_Data.m_VAO = std::make_unique<VertexArray>();
    m_Data.m_VBO = std::make_unique<VertexBuffer>();
    m_Data.m_IBO = std::make_unique<IndexBuffer>();

    m_Data.m_VAO->Bind();

    m_Data.m_VBO->SetData(static_cast<int>(sizeof(float) * Cube::GetVertices().size()), Cube::GetVertices().data());
    m_Data.m_IBO->SetData(static_cast<int>(sizeof(unsigned int) * Cube::GetIndices().size()), Cube::GetIndices().data());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    VertexArray::Unbind();
    VertexBuffer::Unbind();
    IndexBuffer::Unbind();

    m_Data.m_FBO = std::make_unique<FrameBuffer>();
    const WindowSize windowSize = m_Window->GetSize();
    m_Data.m_FBO->AttachTexture(windowSize.Width, windowSize.Height);
    FrameBuffer::Unbind();
}

void Renderer::SetCallbacks() const
{
    m_Window->SetResizeCallback([this](const int width, const int height) {
        OnWindowResize(width, height);
    });
    
    m_Window->SetScrollCallback([this](const float xOffset, const float yOffset) {
        OnMouseScroll(yOffset);
    });
}

void Renderer::OnWindowResize(const int width, const int height) const
{
    m_Window->SetSize(WindowSize{width, height});

    m_Data.m_FBO->Bind();
    m_Data.m_FBO->AttachTexture(width, height);
    FrameBuffer::Unbind();
}

void Renderer::OnMouseScroll(const float yOffset) const
{
    m_Data.m_Camera->ProcessMouseScroll(yOffset);
}

void Renderer::Render() {
    const auto currentFrame = static_cast<float>(glfwGetTime());
    m_DeltaTime = currentFrame - m_LastFrame;
    m_LastFrame = currentFrame;

    m_Data.m_FBO->Bind();

    glfwPollEvents();
    ProcessInput(m_Window->GetNativeWindow());

    glEnable(GL_DEPTH_TEST);

    glClearColor(m_Data.m_ClearColor.x, m_Data.m_ClearColor.y, m_Data.m_ClearColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Data.m_Shader->Use();

    m_Data.m_Cube->Draw();

    const glm::mat4& model = m_Data.m_Cube->GetModelMatrix();
    const glm::mat4& view = m_Data.m_Camera->GetViewMatrix();

    const WindowSize size = m_Window->GetSize();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(size.Width) / static_cast<float>(size.Height), 0.1f, 100.0f);

    glUniformMatrix4fv(m_Data.m_Shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(m_Data.m_Shader->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(m_Data.m_Shader->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(m_Data.m_Shader->GetUniformLocation("color"), 1, glm::value_ptr(m_Data.m_Cube->GetShaderColor()));

    m_Data.m_VAO->Bind();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glfwSwapBuffers(m_Window->GetNativeWindow());
}

void Renderer::ProcessInput(GLFWwindow* window)
{
    if(Input::IsMouseButtonPressed(window, ButtonRight))
    {
        const auto mousePos = Input::GetMousePosition(window);

        if(m_FirstMouse)
        {
            m_LastX = mousePos.x;
            m_LastY = mousePos.y;
            m_FirstMouse = false;
        }

        const float xOffset = mousePos.x - m_LastX;
        const float yOffset = m_LastY - mousePos.y;

        m_LastX = mousePos.x;
        m_LastY = mousePos.y;

        m_Data.m_Camera->ProcessMouseMovement(xOffset, yOffset);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (Input::IsKeyPressed(window, W))
        m_Data.m_Camera->ProcessKeyboard(FORWARD, m_DeltaTime);
    if (Input::IsKeyPressed(window, S))
        m_Data.m_Camera->ProcessKeyboard(BACKWARD, m_DeltaTime);
    if (Input::IsKeyPressed(window, A))
        m_Data.m_Camera->ProcessKeyboard(LEFT, m_DeltaTime);
    if (Input::IsKeyPressed(window, D))
        m_Data.m_Camera->ProcessKeyboard(RIGHT, m_DeltaTime);
    if (Input::IsKeyPressed(window, Q))
        m_Data.m_Camera->ProcessKeyboard(DOWN, m_DeltaTime);
    if (Input::IsKeyPressed(window, E))
        m_Data.m_Camera->ProcessKeyboard(UP, m_DeltaTime);
}