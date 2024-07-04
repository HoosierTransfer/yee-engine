#pragma once

#include <material/Material.hpp>

class Light {
public:
    Light() = default;
    virtual void applyLighting(Material &material, int index) {
    }
};
