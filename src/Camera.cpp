#include <Camera.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 eulerAngle) {
    this->position = position;
    this->worldUp = up;
    this->eulerAngle = eulerAngle;
    this->updateCameraVectors();
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

void Camera::setEulerAngle(glm::vec3 eulerAngle) {
    this->eulerAngle = eulerAngle;
    this->updateCameraVectors();
}

void Camera::move(glm::vec3 offset) {
    this->position += offset;
}

void Camera::rotate(float angle, glm::vec3 axis) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    glm::vec3 newFront = glm::vec3(rotation * glm::vec4(this->front, 1.0f));
    this->eulerAngle.y = glm::degrees(asin(newFront.y));
    this->eulerAngle.x = glm::degrees(atan2(newFront.z, newFront.x));
    this->updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::processKeyboard(GLFWwindow *window, float deltaTime) {
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraSpeed *= 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->position += cameraSpeed * this->front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->position -= cameraSpeed * this->front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        this->position -= cameraSpeed * this->right;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        this->position += cameraSpeed * this->right;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->position += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        this->position -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= 0.1f;
    yoffset *= 0.1f;

    this->eulerAngle.x += xoffset;
    this->eulerAngle.y += yoffset;

    if (constrainPitch) {
        if (this->eulerAngle.y > 89.0f) {
            this->eulerAngle.y = 89.0f;
        }
        if (this->eulerAngle.y < -89.0f) {
            this->eulerAngle.y = -89.0f;
        }
    }

    this->updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->eulerAngle.x)) * cos(glm::radians(this->eulerAngle.y));
    front.y = sin(glm::radians(this->eulerAngle.y));
    front.z = sin(glm::radians(this->eulerAngle.x)) * cos(glm::radians(this->eulerAngle.y));
    this->front = glm::normalize(front);

    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}