#include "Scene.hpp"

Scene &Scene::Instance() {
    static Scene scene;
    return scene;
}

Scene::Scene()  {
    Point3f eye(0,0,4);
    Point3f lookAt(0,0,0);
    Normal up(0,1,0);
    camera = std::make_shared<class Camera>(up, eye, lookAt);
    ColorRGBf white(1, 1, 1);
    auto phongModel = std::make_shared<PhongModel>(white, white, white);
    light = std::make_shared<PointLight>(eye, phongModel);
}

std::vector<std::shared_ptr<Model>> &Scene::Models() {
    return models;
}

const std::vector<std::shared_ptr<Model>> &Scene::Models() const {
    return models;
}

std::vector<bool> &Scene::WireFramed() {
    return wireFramed;
}

const std::vector<bool> &Scene::WireFramed() const {
    return wireFramed;
}

std::shared_ptr<PointLight> &Scene::Light() {
    return light;
}

const std::shared_ptr<PointLight> &Scene::Light() const {
    return light;
}

std::shared_ptr<class Camera> &Scene::Camera() {
    return camera;
}

const std::shared_ptr<class Camera> &Scene::Camera() const {
    return camera;
}
