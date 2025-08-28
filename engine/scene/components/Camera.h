#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

constexpr float YAW         = -90.0f;
constexpr float PITCH       =  0.0f;
constexpr float SPEED       =  2.5f;
constexpr float SENSITIVITY =  0.1f;
constexpr float ZOOM        =  45.0f;

class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Position(position), Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(up), Yaw(yaw), Pitch(pitch), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        UpdateCameraVectors();
    }
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Yaw(yaw), Pitch(pitch), MovementSpeed(SPEED), Position(glm::vec3(posX, posY, posZ)), WorldUp(glm::vec3(upX, upY, upZ)), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        UpdateCameraVectors();
    }

    glm::mat4 GetViewMatrix() const;
    glm::mat4 LookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up);

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yOffset);

private:
    void UpdateCameraVectors();
};