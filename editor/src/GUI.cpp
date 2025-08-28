#include "GUI.h"

class Engine;

GUI::GUI(const Engine* engine)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    LoadConfigs(engine);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(engine->GetWindow()->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init();
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::LoadConfigs(const Engine* engine)
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    io.IniFilename = EDITOR_RESOURCES_PATH"imgui.ini";

    m_WindowScale = engine->GetWindow()->GetScale();

    const float baseFontSize = 14.0f * m_WindowScale.X;
    const float iconFontSize = baseFontSize * 2.0f / 2.4f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

    io.Fonts->AddFontFromFileTTF(ENGINE_RESOURCES_PATH"fonts/Ruda-Bold.ttf", baseFontSize);

    static constexpr ImWchar iconsRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;
    iconsConfig.PixelSnapH = true;
    iconsConfig.GlyphMinAdvanceX = iconFontSize;
    io.Fonts->AddFontFromFileTTF(ENGINE_RESOURCES_PATH"fonts/" FONT_ICON_FILE_NAME_FAS, iconFontSize, &iconsConfig, iconsRanges );

    ImGui::StyleColorsDark();

    ImGuiStyle* style = &ImGui::GetStyle();
    m_StyleColors = style->Colors;

    style->WindowMenuButtonPosition = ImGuiDir_None;
    style->WindowBorderSize = 0.0f * m_WindowScale.X;
    style->GrabRounding = 4.0f * m_WindowScale.X;
    style->WindowRounding = 6.0f * m_WindowScale.X;
    style->FrameRounding = 4.0f * m_WindowScale.X;
    style->FramePadding = ImVec2(5.0f * m_WindowScale.X, 5.0f * m_WindowScale.X);
    style->PopupBorderSize = 0.0f * m_WindowScale.X;
    style->PopupRounding = 4.0f * m_WindowScale.X;
    style->SeparatorTextPadding = ImVec2(5.0f * m_WindowScale.X, 5.0f * m_WindowScale.X);
    style->TabBarBorderSize = 2.0f * m_WindowScale.X;
    style->TabBarOverlineSize = 1.5f * m_WindowScale.X;

    m_StyleColors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_DockingEmptyBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    m_StyleColors[ImGuiCol_Border] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    m_StyleColors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    m_StyleColors[ImGuiCol_FrameBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.0f);
    m_StyleColors[ImGuiCol_FrameBgHovered] = ImVec4(0.03f, 0.03f, 0.03f, 0.8f);
    m_StyleColors[ImGuiCol_FrameBgActive] = ImVec4(0.03f, 0.03f, 0.03f, 1.0f);
    m_StyleColors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    m_StyleColors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    m_StyleColors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.0f);
    m_StyleColors[ImGuiCol_Header] = ImVec4(0.08f, 0.08f, 0.08f, 1.0f);
    m_StyleColors[ImGuiCol_HeaderHovered] = ImVec4(0.08f, 0.42f, 0.14f, 0.8f);
    m_StyleColors[ImGuiCol_HeaderActive] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_Separator] = ImVec4(0.08f, 0.42f, 0.14f, 0.3f);
    m_StyleColors[ImGuiCol_SeparatorHovered] = ImVec4(0.08f, 0.42f, 0.14f, 0.8f);
    m_StyleColors[ImGuiCol_SeparatorActive] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_ResizeGrip] = ImVec4(0.08f, 0.42f, 0.14f, 0.2f);
    m_StyleColors[ImGuiCol_ResizeGripHovered] = ImVec4(0.08f, 0.42f, 0.14f, 0.8f);
    m_StyleColors[ImGuiCol_ResizeGripActive] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_Tab] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    m_StyleColors[ImGuiCol_TabHovered] = ImVec4(0.2f, 0.2f, 0.2f, 0.5f);
    m_StyleColors[ImGuiCol_TabActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    m_StyleColors[ImGuiCol_TabUnfocused] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    m_StyleColors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    m_StyleColors[ImGuiCol_TabSelectedOverline] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_DockingPreview] = ImVec4(0.08f, 0.42f, 0.14f, 0.8f);
    m_StyleColors[ImGuiCol_CheckMark] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_SliderGrab] = ImVec4(0.08f, 0.42f, 0.14f, 0.8f);
    m_StyleColors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    m_StyleColors[ImGuiCol_ButtonHovered] = ImVec4(0.08f, 0.42f, 0.14f, 0.5f);
    m_StyleColors[ImGuiCol_ButtonActive] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_TextSelectedBg] = ImVec4(0.08f, 0.42f, 0.14f, 0.35f);
    m_StyleColors[ImGuiCol_TextLink] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
    m_StyleColors[ImGuiCol_NavCursor] = ImVec4(0.08f, 0.42f, 0.14f, 1.0f);
}

void GUI::Run()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
}

void GUI::Render(const Engine* engine)
{
    ShowConsole();
    ShowEntities(engine);
    ShowProperties(engine);
    ShowMenu();
    ShowFiles();
    ShowScene(engine);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Print(const std::string& message)
{
    m_Log += message + '\n';
}

void GUI::ShowConsole(){
    ImGui::Begin(ICON_FA_TERMINAL" Console");

    if(ImGui::Button("Clear")){
        m_Log.clear();
    }

    ImGui::SameLine();

    if(ImGui::Button("Debug")){
        Print("Debug message");
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Text("%s", m_Log.c_str());

    ImGui::End();
}

void GUI::ShowEntities(const Engine* engine)
{
    ImGui::Begin(ICON_FA_CUBE" Entities");

    for(const auto& cube : engine->GetRenderer()->GetData().m_Scene->GetCubes())
    {
        ImGui::CollapsingHeader(cube->name.c_str());
    }

    ImGui::End();
}

void GUI::ShowProperties(const Engine* engine)
{
    ImGui::Begin(ICON_FA_BARS_STAGGERED" Properties");

    if(ImGui::CollapsingHeader("Transform"))
    {
        ImGui::BeginGroup();

        glm::vec3 position = engine->GetRenderer()->GetData().m_Cube->GetPosition();
        glm::vec3 rotation = engine->GetRenderer()->GetData().m_Cube->GetRotation();
        glm::vec3 scale = engine->GetRenderer()->GetData().m_Cube->GetScale();

        if (ImGui::DragFloat3("Position", glm::value_ptr(position), 0.2f)) {
            engine->GetRenderer()->GetData().m_Cube->SetPosition(position);
        }
        if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.4f)) {
            engine->GetRenderer()->GetData().m_Cube->SetRotation(rotation);
        }
        if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f)) {
            engine->GetRenderer()->GetData().m_Cube->SetScale(scale);
        }
        
        ImGui::EndGroup();
    }

    ImGui::NewLine();

    ImGui::BeginGroup();
    ImGui::Text("Colors");

    glm::vec3 shaderColor = engine->GetRenderer()->GetData().m_Cube->GetShaderColor();
    glm::vec3 clearColor = engine->GetRenderer()->GetData().m_ClearColor;

    // Check if colors changed and update
    if (ImGui::ColorEdit3("Shader Color", glm::value_ptr(shaderColor))) {
        engine->GetRenderer()->GetData().m_Cube->SetShaderColor(shaderColor);
    }
    if (ImGui::ColorEdit3("Background Color", glm::value_ptr(clearColor))) {
        engine->GetRenderer()->GetData().m_ClearColor = clearColor;
    }
    
    ImGui::EndGroup();

    ImGui::End();
}

void GUI::ShowMenu()
{
    if(ImGui::BeginMainMenuBar()){
        if(ImGui::BeginMenu("File")){
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void GUI::ShowFiles()
{
    ImGui::Begin(ICON_FA_FOLDER" Files");

    ImGui::End();
}

void GUI::ShowScene(const Engine* engine)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin(ICON_FA_CLAPPERBOARD" Scene");
    {
        ImGui::Image(
            engine->GetRenderer()->GetData().m_FBO->GetFrameTexture()->GetID(),
            ImGui::GetContentRegionAvail(),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );
    }
    ImGui::End();
    ImGui::PopStyleVar();
}



