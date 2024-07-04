#pragma once

#include <Shader.hpp>
#include <memory>

class Material {
private:
    std::unique_ptr<Shader> shader;
public:
    Shader& getShader() {
        return *this->shader;
    }

    Material(const std::string &shaderName) : shader(std::make_unique<Shader>(shaderName)) {}

    Material(std::unique_ptr<Shader> shader) : shader(std::move(shader)) {}

    virtual void use() {
        this->shader->use();
    }

    virtual void applyUniforms() = 0;
};