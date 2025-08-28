#include "Engine.h"

Engine::Engine()
{
    const std::string name = "Ferx Engine";

    m_Window = std::make_unique<Window>(WindowData(name));
    m_Renderer = std::make_unique<Renderer>(m_Window.get());
}

void Engine::Run() const
{
    if (m_IsRunning) {
        m_Renderer->Render();
    }
}

void Engine::Shutdown()
{
    m_IsRunning = false;
}