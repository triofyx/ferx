#pragma once

#define GLFW_INCLUDE_NONE
#include "Engine.h"
#include "GUI.h"

class Editor
{
public:
    Editor();
    ~Editor() = default;

    void Run() const;
    
    Engine* GetEngine() const { return m_Engine.get(); };
    GUI* GetGUI() const { return m_GUI.get(); };

private:
    std::unique_ptr<Engine> m_Engine;
    std::unique_ptr<GUI> m_GUI;
};