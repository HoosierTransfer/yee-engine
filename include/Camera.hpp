#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    glm::vec3 eulerAngle;

    void updateCameraVectors();

public:
    Camera() = default;

    Camera(glm::vec3 position, glm::vec3 up, glm::vec3 eulerAngle);

    void setPosition(glm::vec3 position);
    void setEulerAngle(glm::vec3 eulerAngle);

    void move(glm::vec3 offset);
    void rotate(float angle, glm::vec3 axis);

    glm::mat4 getViewMatrix();
    void processKeyboard(GLFWwindow *window, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    glm::vec3 getPosition() {
        return this->position;
    }

    glm::vec3 getFront() {
        return this->front;
    }

    glm::vec3 getUp() {
        return this->up;
    }

    glm::vec3 getRight() {
        return this->right;
    }

    glm::vec3 getWorldUp() {
        return this->worldUp;
    }

    glm::vec3 getEulerAngle() {
        return this->eulerAngle;
    }
};