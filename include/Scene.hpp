#pragma once

#include <material/Material.hpp>
#include <light/Light.hpp>
#include <memory>

class Scene {
private:
    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Light>> lights;
public:
    Scene() = default;

    void addMaterial(std::shared_ptr<Material> material);

    void addLight(std::shared_ptr<Light> light);

    void addMaterial(Material *material);

    void addLight(Light *light);

    void applyLighting();

    void applyLighting(Material &material);

    void applyMaterials();
};