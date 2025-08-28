#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "KeyCodes.h"
#include "MouseCodes.h"

class Input
{
public:
    static bool IsKeyPressed(GLFWwindow* window, KeyCode key);

    static bool IsMouseButtonPressed(GLFWwindow* window, MouseCode button);
    static glm::vec2 GetMousePosition(GLFWwindow* window);
};