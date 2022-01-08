#include <lighting/util/ReflectedNormalCalculator/ReflectedNormalCalculator.hpp>
#include "PhongShader.hpp"
#include "core/math/MathVector/MathVector.hpp"

ColorRGBf PhongShader::operator()(const std::shared_ptr<PointLight> &light, const PhongFragment &fragment,
                                  const Normal &viewN) {

    const auto &material = fragment.Material();
    const auto &fragPhongModel = material->PhongModel();
    const auto &lightPhongModel = light->PhongModel();

    auto ambient = lightPhongModel->Ambient() * fragPhongModel->Ambient();

    auto lightPos = light->Position();
    auto fragPos = fragment.Position();

    auto lightNormal = Normal(fragPos, lightPos);
    const auto &fragNormal = fragment.Normal();

    auto diffuseRatio = lightNormal * fragNormal;
    ColorRGBf diffuse(0, 0, 0);
    if (diffuseRatio > 0) {
        diffuse = diffuseRatio * lightPhongModel->Diffuse() * fragPhongModel->Diffuse();
    }

    ReflectedNormalCalculator reflect;
    auto reflectedVec = reflect(lightNormal, fragNormal);

    auto shineRatio = reflectedVec * viewN;

    ColorRGBf specular(0, 0, 0);
    if (shineRatio > 0) {
        auto shininess = material->Shininess();
        float specularRatio = std::pow(shineRatio, 128 * shininess);
        specular = specularRatio * lightPhongModel->Specular() * fragPhongModel->Specular();
    }

    auto fragColor = ambient + diffuse + specular;

    return fragColor;
}
