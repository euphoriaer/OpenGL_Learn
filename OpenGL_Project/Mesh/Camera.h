#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
    Camera(glm::vec3 _position, glm::vec3 target, glm::vec3 worldup);
    Camera(glm::vec3 _position, float pitch, float yaw, glm::vec3 worldup);
    glm::mat4 GetViewMatrix();
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;

    float Pitch;
    float Yaw;
    float CameraSpeedX = 0.001f;
    float CameraSpeedY = 0.001f;
    /// <summary>
    ///  相机移动，X 前后，Y 左右 ,Z上下
    /// </summary>
    /// <param name="deltaX"></param>
    /// <param name="deltaY"></param>
    glm::vec3 cameraTranslate;

    void ProcessMouseMovement(float deltaX, float deltaY);
private:
    void UpdateCameraVectors();
};
