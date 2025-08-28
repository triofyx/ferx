#pragma once

#define GLFW_INCLUDE_NONE
#include <memory>
#include "Window.h"
#include "Renderer.h"

class Engine
{
public:
    Engine();
    ~Engine() = default;

    Window* GetWindow() const { return m_Window.get(); }
    Renderer* GetRenderer() const { return m_Renderer.get(); }
    
    void Run() const;
    void Shutdown();

private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;
    bool m_IsRunning = true;
};