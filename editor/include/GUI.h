#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <IconsFontAwesome6.h>
#include <string>
#include "Engine.h"
#include "Window.h"
#include "FrameBuffer.h"

class GUI
{
public:
    explicit GUI(const Engine* engine);
    ~GUI();

    void LoadConfigs(const Engine* engine);
    static void Run();
    void Render(const Engine* engine);

    void Print(const std::string& message);

    static void ShowMenu();
    static void ShowEntities(const Engine* engine);
    static void ShowProperties(const Engine* engine);
    static void ShowFiles();
    void ShowConsole();
    static void ShowScene(const Engine* engine);

private:
    std::string m_Log;
    ImVec4* m_StyleColors{};
    WindowScale m_WindowScale;
};
