#include <Scene.hpp>

#include <light/DirectionalLight.hpp>
#include <ShaderType.hpp>
#include <material/LitMaterial.hpp>

#include <iostream>

void Scene::addMaterial(std::shared_ptr<Material> material) {
    this->materials.push_back(material);
}

void Scene::addLight(std::shared_ptr<Light> light) {
    this->lights.push_back(light);
}

void Scene::addMaterial(Material *material) {
    this->materials.push_back(std::shared_ptr<Material>(material));
}

void Scene::addLight(Light *light) {
    this->lights.push_back(std::shared_ptr<Light>(light));
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

void Scene::applyLighting() {
    for (int i = 0; i < this->lights.size(); i++) {
        for (auto &material : this->materials) {
            if (material->isLit()) {
                if (instanceof<DirectionalLight>(this->lights[i].get())) {
                    if (std::stoi(material->getShader().getDefine("DIRECTIONAL_LIGHTS", ShaderType::FRAGMENT)) < i) {
                        continue;
                    }
                }
                this->lights[i]->applyLighting(*material, i);
            }
        }
    }
}

void Scene::applyLighting(Material &material) {
    for (int i = 0; i < this->lights.size(); i++) {
        if (instanceof<DirectionalLight>(this->lights[i].get())) {
            if (instanceof<DirectionalLight>(this->lights[i].get())) {
                if (std::stoi(material.getShader().getDefine("DIRECTIONAL_LIGHTS", ShaderType::FRAGMENT)) < i) {
                    continue;
                }
            }
            // std::cout << "Applying lighting for light " << i << std::endl;
            this->lights[i]->applyLighting(material, i);
        }
    }
}

void Scene::applyMaterials() {
    for (auto &material : this->materials) {
        material->applyUniforms();
    }
}