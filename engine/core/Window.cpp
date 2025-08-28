#include "Window.h"

#include <stb_image.h>
#include <utility>

Window::Window(WindowData  data) : m_Data(std::move(data))
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    std::cout << "GLFW Initialized" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
#if defined(_WIN32)
    // Add Windows-specific configuration if needed
#elif defined(__linux__)
    glfwWindowHintString(GLFW_X11_CLASS_NAME, "ferx");
    glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "Ferx");
#endif

    m_Window = glfwCreateWindow(m_Data.Size.Width, m_Data.Size.Height, m_Data.Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);

    SetWindowIcon();
    SetupCallbacks();
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
}

GLFWwindow* Window::GetNativeWindow() const
{
    return m_Window;
}

const std::string& Window::GetTitle() const
{
    return m_Data.Title;
}

WindowSize Window::GetSize()
{
    glfwGetWindowSize(m_Window, &m_Data.Size.Width, &m_Data.Size.Height);
    return m_Data.Size;
}

WindowScale Window::GetScale()
{
    glfwGetWindowContentScale(m_Window, &m_Data.Scale.X, &m_Data.Scale.Y);
    return m_Data.Scale;
}

void Window::SetTitle(const std::string& title)
{
    m_Data.Title = title;
    glfwSetWindowTitle(m_Window, m_Data.Title.c_str());
}

void Window::SetSize(const WindowSize size)
{
    m_Data.Size = size;
}

void Window::SetScale(const WindowScale scale)
{
    m_Data.Scale = scale;
}

void Window::SetupCallbacks() {
    glfwSetWindowUserPointer(m_Window, this);

    glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
    glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
    glfwSetScrollCallback(m_Window, MouseScrollCallback);
}

void Window::SetResizeCallback(const ResizeCallback& callback) {
    m_ResizeCallback = callback;
}

void Window::SetScrollCallback(const ScrollCallback& callback) {
    m_ScrollCallback = callback;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void Window::WindowSizeCallback(GLFWwindow* window, const int width, const int height) {
    const auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (windowInstance && windowInstance->m_ResizeCallback) {
        windowInstance->m_ResizeCallback(width, height);
    }
}

void Window::MouseScrollCallback(GLFWwindow* window, const double xOffset, const double yOffset) {
    const auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (windowInstance && windowInstance->m_ScrollCallback)
    {
        windowInstance->m_ScrollCallback(static_cast<float>(xOffset), static_cast<float>(yOffset));
    }
}

void Window::SetWindowIcon() const
{
    int width, height, channels;
    const auto iconPath = ENGINE_RESOURCES_PATH"icons/icon.png";

    unsigned char* pixels = stbi_load(iconPath, &width, &height, &channels, 4); // Force RGBA
    if (!pixels) {
        std::cerr << "Failed to load icon: " << iconPath << std::endl;
        return;
    }

    GLFWimage images[1];
    images[0].width = width;
    images[0].height = height;
    images[0].pixels = pixels;

    glfwSetWindowIcon(m_Window, 1, images);

    stbi_image_free(pixels);
}
