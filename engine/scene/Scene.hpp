#pragma once

#include <view/Camera/Camera.hpp>
#include <lighting/PointLight/PointLight.hpp>
#include <modeling/Model/Model.hpp>

struct Scene {
public:
    static Scene &Instance();

    std::vector<std::shared_ptr<Model>> &Models();
    [[nodiscard]] const std::vector<std::shared_ptr<Model>> &Models() const;

    std::vector<bool> &WireFramed();
    [[nodiscard]] const std::vector<bool> &WireFramed() const;

    std::shared_ptr<PointLight> &Light();
    [[nodiscard]] const std::shared_ptr<PointLight> &Light() const;

    std::shared_ptr<class Camera> &Camera();
    [[nodiscard]] const std::shared_ptr<class Camera> &Camera() const;

private:
    Scene();

private:
    std::vector<std::shared_ptr<Model>> models;
    std::vector<bool> wireFramed;
    std::shared_ptr<PointLight> light;
    std::shared_ptr<class Camera> camera;
};
