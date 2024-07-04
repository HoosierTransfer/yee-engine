#pragma once

#include <App.hpp>

#include <Shader.hpp>
#include <memory>

class Material {
protected:
    std::unique_ptr<Shader> shader;

public:
    Shader& getShader() {
        return *this->shader;
    }

    Material(const std::string &shaderName) : shader(std::make_unique<Shader>(shaderName)) {
        this->shader->compile();
    }

    Material(std::unique_ptr<Shader> shader) : shader(std::move(shader)) {
        if (!this->shader->isCompiled()) {
            this->shader->compile();
        }
    }

    virtual void applyTransforms(glm::mat4 model) {
        this->shader->setMat4("model", model);
        this->shader->setMat4("view", App::getInstance()->getMainCamera().getViewMatrix());
        this->shader->setMat4("projection", App::getInstance()->getProjectionMatrix());
    }

    virtual void use() {
        this->shader->use();
    }

    virtual void applyUniforms() {}

    bool isLit() {
        return false;
    }
};