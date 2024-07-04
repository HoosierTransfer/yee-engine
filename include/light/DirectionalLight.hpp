#pragma once

#include <light/Light.hpp>
#include <glm/glm.hpp>

class DirectionalLight : public Light {
private:
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    DirectionalLight() = default;

    void applyLighting(Material &material, int index) override {
        material.getShader().setVec3InStructArray("dirLight", "direction", this->direction, index);
        material.getShader().setVec3InStructArray("dirLight", "ambient", this->ambient, index);
        material.getShader().setVec3InStructArray("dirLight", "diffuse", this->diffuse, index);
        material.getShader().setVec3InStructArray("dirLight", "specular", this->specular, index);
        material.getShader().setBoolInStructArray("dirLight", "enabled", true, index);
    }

    DirectionalLight& setDirection(glm::vec3 direction) {
        this->direction = direction;
        return *this;
    }

    DirectionalLight& setAmbient(glm::vec3 ambient) {
        this->ambient = ambient;
        return *this;
    }

    DirectionalLight& setDiffuse(glm::vec3 diffuse) {
        this->diffuse = diffuse;
        return *this;
    }

    DirectionalLight& setSpecular(glm::vec3 specular) {
        this->specular = specular;
        return *this;
    }

    glm::vec3 getDirection() {
        return this->direction;
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
};