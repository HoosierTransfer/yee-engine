#pragma once

#include <light/Light.hpp>
#include <glm/glm.hpp>



class PointLight : public Light {
private:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;

public:
    PointLight() = default;

    void applyLighting(Material &material, int index) override {
        material.getShader().setVec3InStructArray("pointLights", "position", this->position, index);
        material.getShader().setVec3InStructArray("pointLights", "ambient", this->ambient, index);
        material.getShader().setVec3InStructArray("pointLights", "diffuse", this->diffuse, index);
        material.getShader().setVec3InStructArray("pointLights", "specular", this->specular, index);
        material.getShader().setFloatInStructArray("pointLights", "constant", this->constant, index);
        material.getShader().setFloatInStructArray("pointLights", "linear", this->linear, index);
        material.getShader().setFloatInStructArray("pointLights", "quadratic", this->quadratic, index);
        material.getShader().setBoolInStructArray("pointLights", "enabled", true, index);
    }

    PointLight& setPosition(glm::vec3 position) {
        this->position = position;
        return *this;
    }

    PointLight& setAmbient(glm::vec3 ambient) {
        this->ambient = ambient;
        return *this;
    }

    PointLight& setDiffuse(glm::vec3 diffuse) {
        this->diffuse = diffuse;
        return *this;
    }

    PointLight& setSpecular(glm::vec3 specular) {
        this->specular = specular;
        return *this;
    }

    PointLight& setConstant(float constant) {
        this->constant = constant;
        return *this;
    }

    PointLight& setLinear(float linear) {
        this->linear = linear;
        return *this;
    }

    PointLight& setQuadratic(float quadratic) {
        this->quadratic = quadratic;
        return *this;
    }

    glm::vec3 getPosition() {
        return this->position;
    }

    glm::vec3 getAmbient() {
        return this->ambient;
    }

    glm::vec3 getDiffuse() {
        return this->diffuse;
    }

    glm::vec3 getSpecular() {
        return this->specular;
    }

    float getConstant() {
        return this->constant;
    }

    float getLinear() {
        return this->linear;
    }
};