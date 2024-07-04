#pragma once

#include <material/Material.hpp>

class UnlitMaterial : public Material {
private:
    glm::vec3 color;
public:
    UnlitMaterial() : Material("unlit") {}

    void applyUniforms() override {
        this->getShader().setVec3("color", this->color);
    }

    UnlitMaterial& setColor(glm::vec3 color) {
        this->color = color;
        return *this;
    }

    glm::vec3 getColor() {
        return this->color;
    }

    void use() override {
        Material::use();
        this->applyUniforms();
    }

    bool isLit() {
        return false;
    }
};