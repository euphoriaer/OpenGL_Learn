#include "Camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 target, glm::vec3 worldup)
{
    Position = _position;
    WorldUp = worldup;

    Forward = glm::normalize(target - _position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 _position, float pitch, float yaw, glm::vec3 worldup)
{
    Position = _position;
    WorldUp = worldup;
    Pitch = pitch;
    Yaw = yaw;
    Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::cos(Yaw);

    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}

glm::mat4 Camera::GetViewMatrix()
{
    UpdateCameraVectors();//每次返回视角变换矩阵  先更新相机
    return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
    Pitch -= deltaY * CameraSpeedX;
    Yaw -= deltaX * CameraSpeedY;
}

void Camera::UpdateCameraVectors()
{
    Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::cos(Yaw);

    //OpenGl 右手，三指,大拇指右侧，与食指forward cross,才是向上
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Right, Forward));

    Position += Forward * cameraTranslate.x * 0.1f;//前后移动
    Position -= Right * cameraTranslate.y * 0.1f;//左右移动
    Position += Up * cameraTranslate.z * 0.1f;//上下移动
}