#include "Editor.h"

Editor::Editor()
{
    m_Engine = std::make_unique<Engine>();

    m_GUI = std::make_unique<GUI>(m_Engine.get());

    Run();
}

void Editor::Run() const
{
    while (!glfwWindowShouldClose(m_Engine->GetWindow()->GetNativeWindow())) {
        m_Engine->Run();
        GUI::Run();
        m_GUI->Render(m_Engine.get());
    }
}
