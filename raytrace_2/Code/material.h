#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "triple.h"
#include "image.h"

class Material {
public:
    Color color;        // base color
    double ka;          // ambient intensity
    double kd;          // diffuse intensity
    double ks;          // specular intensity
    double n;           // exponent for specular highlight size
    std::unique_ptr<Image> texture;

    Material() = default;

    Material(Color const &color, double ka, double kd, double ks, double n)
            :
            color(color),
            ka(ka),
            kd(kd),
            ks(ks),
            n(n),
            texture(nullptr) {}

    Material(Color const &color, double ka, double kd, double ks, double n, const std::string &texturePath)
            :
            color(color),
            ka(ka),
            kd(kd),
            ks(ks),
            n(n),
            texture(nullptr) {
        texture = std::make_unique<Image>(texturePath);
    }

    bool hasTexture() const {
        return texture != nullptr;
    }
};

#endif
