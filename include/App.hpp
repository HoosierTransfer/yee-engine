#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Camera.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

class App {
private:
    int SCR_WIDTH;
    int SCR_HEIGHT;

    bool firstMouse = true;
    float lastX, lastY;

    Camera mainCamera;

    glm::mat4 projectionMatrix;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glm::vec3 lightPos;

    glm::vec3 lightColor;
    glm::vec3 objectColor;

    static App* instance;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void processInput(GLFWwindow *window);

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);

public:
    App(int SCR_WIDTH, int SCR_HEIGHT);

    static App* getInstance();

    Camera& getMainCamera() {
        return mainCamera;
    }

    glm::mat4 getProjectionMatrix() {
        return projectionMatrix;
    }

    int run();
};
