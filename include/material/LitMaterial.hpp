#pragma once

#include <material/Material.hpp>
#include <ShaderType.hpp>
#include <glad/glad.h>
#include <App.hpp>

class LitMaterial : public Material {
private:
    unsigned int loadTexture(char const * path) {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        
        int width, height, nrComponents;
        unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        } else {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    std::string diffuseTexturePath;
    unsigned int diffuseTexture = 0;

    std::string roughnessTexturePath;
    unsigned int roughnessTexture = 0;
public:
    LitMaterial() : Material("lit") {}
    LitMaterial(std::string diffuseTexturePath) {
        this->shader = std::make_unique<Shader>("lit");
        this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::FRAGMENT);
        this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::VERTEX);
        this->diffuseTexturePath = diffuseTexturePath;
        this->getShader().compile();
        this->diffuseTexture = loadTexture(diffuseTexturePath.c_str());
    }

    LitMaterial(std::string diffuseTexturePath, std::string roughnessTexturePath) {
        this->shader = std::make_unique<Shader>("lit");
        this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::FRAGMENT);
        this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::VERTEX);
        this->getShader().addDefine("ROUGHNESS_TEXTURE", "", ShaderType::FRAGMENT);
        this->getShader().addDefine("ROUGHNESS_TEXTURE", "", ShaderType::VERTEX);
        this->diffuseTexturePath = diffuseTexturePath;
        this->roughnessTexturePath = roughnessTexturePath;
        this->getShader().compile();
        this->diffuseTexture = loadTexture(diffuseTexturePath.c_str());
        this->roughnessTexture = loadTexture(roughnessTexturePath.c_str());
    }

    void applyUniforms() override {

        this->getShader().setVec3("viewPos", App::getInstance()->getMainCamera().getPosition());
        this->getShader().setVec3("material.ambient", this->ambient);
        this->getShader().setVec3("material.diffuse", this->diffuse);
        this->getShader().setVec3("material.specular", this->specular);
        this->getShader().setFloat("material.shininess", this->shininess);
        if (!this->diffuseTexturePath.empty()) {
            this->getShader().setInt("material.diffuse", 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->diffuseTexture);
        }

        if (!this->roughnessTexturePath.empty()) {
            this->getShader().setInt("material.roughness", 1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this->roughnessTexture);
        }
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

    LitMaterial& setDiffuseTexture(std::string diffuseTexturePath) {
        this->shader = std::make_unique<Shader>("lit");
        this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::FRAGMENT);
        this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::VERTEX);
        if (!this->roughnessTexturePath.empty()) {
            this->getShader().addDefine("SPECULAR_TEXTURE", "", ShaderType::FRAGMENT);
            this->getShader().addDefine("SPECULAR_TEXTURE", "", ShaderType::VERTEX);
        }
        this->diffuseTexturePath = diffuseTexturePath;
        this->getShader().compile();
        this->diffuseTexture = loadTexture(diffuseTexturePath.c_str());
        return *this;
    }

    LitMaterial& setSpecularTexture(std::string roughnessTexturePath) {
        this->shader = std::make_unique<Shader>("lit");
        if (!this->diffuseTexturePath.empty()) {
            this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::FRAGMENT);
            this->getShader().addDefine("DIFFUSE_TEXTURE", "", ShaderType::VERTEX);
        }
        this->getShader().addDefine("SPECULAR_TEXTURE", "", ShaderType::FRAGMENT);
        this->getShader().addDefine("SPECULAR_TEXTURE", "", ShaderType::VERTEX);
        this->roughnessTexturePath = roughnessTexturePath;
        this->getShader().compile();
        this->roughnessTexture = loadTexture(roughnessTexturePath.c_str());
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