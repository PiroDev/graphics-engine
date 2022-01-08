#pragma once

#include <vector>
#include <string>
#include "modeling/Model/Model.hpp"
#include "visibility/DepthTest/ColorBuffer/ColorBuffer.hpp"
#include "scene/Scene.hpp"
#include "modeling/BrickGenerator/BrickGenerator.hpp"

struct Backend {
public:
    Backend() : scene(Scene::Instance()) {}

    bool LoadScene(const std::string& filename);
    void SaveScene(const std::string& filename);

    void Render(ColorBuffer &colorBuffer);

    void CameraScale(float delta);
    void CameraPitch(float angle) const;
    void CameraYaw(float angle) const;

    void CameraMoveRightAxis(float delta);
    void CameraMoveForwardAxis(float delta);

    unsigned AddModel(const BrickGenerationParams &generationParams);
    void RemoveModel(unsigned modelId);
    void AddWireFramed(unsigned modelId);
    void RemoveWireFramed(unsigned modelId);

    void ModelMoveForwardAxis(unsigned id, float delta);
    void ModelMoveRightAxis(unsigned id, float delta);
    void ModelMoveUpAxis(unsigned id, float delta);
    void ModelRotateAroundUpAxis(unsigned id, float angle);

    [[nodiscard]] std::vector<BrickGenerationParams> GetModelsGenerationParams() const;

private:
    Scene &scene;
};
