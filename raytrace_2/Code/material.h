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
    std::shared_ptr<Image> texture;
    bool isMirror;

    Material() = default;

    Material(Color const &color, double ka, double kd, double ks, double n, bool isMirror = false)
            :
            color(color),
            ka(ka),
            kd(kd),
            ks(ks),
            n(n),
            texture(nullptr), isMirror(isMirror) {}

    Material(Color const &color, double ka, double kd, double ks, double n, const std::string &texturePath, bool isMirror = false)
            :
            color(color),
            ka(ka),
            kd(kd),
            ks(ks),
            n(n),
            texture(nullptr), isMirror(isMirror) {
        texture = std::make_shared<Image>(texturePath);
    }

    bool hasTexture() const {
        return texture != nullptr;
    }
};

#endif
