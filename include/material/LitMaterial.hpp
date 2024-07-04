#pragma once

#include <material/Material.hpp>
#include <App.hpp>

class LitMaterial : public Material {
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
public:
    LitMaterial() : Material("lit") {}

    void applyUniforms() override {
        this->getShader().setVec3("viewPos", App::getInstance()->getMainCamera().getPosition());
        this->getShader().setVec3("material.ambient", this->ambient);
        this->getShader().setVec3("material.diffuse", this->diffuse);
        this->getShader().setVec3("material.specular", this->specular);
        this->getShader().setFloat("material.shininess", this->shininess);
    }

    LitMaterial& setAmbient(glm::vec3 ambient) {
        this->ambient = ambient;
        return *this;
    }

    LitMaterial& setDiffuse(glm::vec3 diffuse) {
        this->diffuse = diffuse;
        return *this;
    }

    LitMaterial& setSpecular(glm::vec3 specular) {
        this->specular = specular;
        return *this;
    }

    LitMaterial& setShininess(float shininess) {
        this->shininess = shininess;
        return *this;
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

    float getShininess() {
        return this->shininess;
    }

    void use() override {
        Material::use();
        this->applyUniforms();
    }

    bool isLit() {
        return true;
    }
};