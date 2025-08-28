#include "Input.h"

bool Input::IsKeyPressed(GLFWwindow* window, const KeyCode key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(GLFWwindow* window, const MouseCode button)
{
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition(GLFWwindow* window)
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    return { static_cast<float>(xPos), static_cast<float>(yPos) };
}