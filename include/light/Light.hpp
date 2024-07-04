#pragma once

#include <glm/glm.hpp>
#include <material/Material.hpp>

class Light {
public:
    Light() = default;
    virtual void applyLighting(Material &material, int index) {
    }
};
