#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include <iostream>
#include <utility>

class Renderer;

struct WindowSize
{
    int Width, Height;

    WindowSize() : Width(800), Height(600) {}
    WindowSize(const int width, const int height) : Width(width), Height(height){}
};

struct WindowScale
{
    float X, Y;

    WindowScale(): X(1), Y(1){}
};

struct WindowData
{
    std::string Title;
    WindowSize Size;
    WindowScale Scale;

    explicit WindowData(std::string title): Title(std::move(title)){};
};

class Window
{
public:
    using ResizeCallback = std::function<void(int width, int height)>;
    using ScrollCallback = std::function<void(float xOffset, float yOffset)>;

    explicit Window(WindowData data);
    ~Window();

    GLFWwindow* GetNativeWindow() const;
    const std::string& GetTitle() const;
    WindowSize GetSize();
    WindowScale GetScale();

    void SetWindowIcon() const;
    void SetTitle(const std::string& title);
    void SetSize(WindowSize size);
    void SetScale(WindowScale scale);
    void SetResizeCallback(const ResizeCallback& callback);
    void SetScrollCallback(const ScrollCallback& callback);

private:
    GLFWwindow* m_Window{};
    WindowData m_Data;

    ResizeCallback m_ResizeCallback;
    ScrollCallback m_ScrollCallback;

    void SetupCallbacks();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void WindowSizeCallback(GLFWwindow* window, int width, int height);
    static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};
