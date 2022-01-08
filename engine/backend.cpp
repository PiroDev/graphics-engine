#include "backend.hpp"

#include <fstream>

#include "modeling/Model/Model.hpp"

#include "transform/MatrixTransformer/MatrixTransformer.hpp"

#include "lighting/PointLight/PointLight.hpp"
#include "lighting/PhongModel/PhongModel.hpp"

#include <transform/MatrixTransformer/operations/MatrixArbitrary.hpp>
#include <transform/MatrixTransformer/operations/rotate/MatrixRotateY.hpp>
#include <transform/MatrixTransformer/operations/move/MatrixMoveZ.hpp>
#include <transform/MatrixTransformer/operations/move/MatrixMoveX.hpp>
#include <transform/MatrixTransformer/operations/move/MatrixMoveY.hpp>

#include "modeling/BrickGenerator/BrickGenerator.hpp"
#include "pipeline/RasterizationPipeline/RasterizationPipeline.hpp"

bool Backend::LoadScene(const std::string &filename) {
    std::ifstream file;
    file.open(filename);

    std::string line;
    std::vector<std::shared_ptr<Model>> models;
    std::vector<bool> wireFramed;
    std::shared_ptr<PointLight> light;
    std::shared_ptr<Camera> camera;
    while (getline(file, line)) {
        if (line == "camera") {
            float x, y, z;
            file >> x >> y >> z;
            Normal up(x, y, z);

            file >> x >> y >> z;
            Point3f eye(x, y, z);

            file >> x >> y >> z;
            Point3f lookAt(x, y, z);

            float pitch, yaw;
            file >> pitch >> yaw;

            camera = std::make_shared<Camera>(up, eye, lookAt, pitch, yaw);
        } else if (line == "light") {
            float x, y, z;
            file >> x >> y >> z;
            Point3f position(x, y, z);

            float r, g, b;
            file >> r >> g >> b;
            ColorRGBf ambient(r, g, b);

            file >> r >> g >> b;
            ColorRGBf diffuse(r, g, b);

            file >> r >> g >> b;
            ColorRGBf specular(r, g, b);

            auto phongModel = std::make_shared<PhongModel>(ambient, diffuse, specular);
            light = std::make_shared<PointLight>(position, phongModel);
        } else if (line == "model") {
            unsigned wSections, lSections, hSections;
            float sectionLen;
            unsigned cylinderFacesCount;
            file >> wSections >> lSections >> hSections >> sectionLen >> cylinderFacesCount;

            BrickGenerator brickGenerator;
            BrickGenerationParams generationParams{wSections, lSections, hSections, sectionLen, cylinderFacesCount};
            auto brick = brickGenerator(generationParams);

            float r, g, b, shininess;
            file >> r >> g >> b;
            ColorRGBf ambient(r, g, b);
            file >> r >> g >> b;
            ColorRGBf diffuse(r, g, b);
            file >> r >> g >> b;
            ColorRGBf specular(r, g, b);
            file >> shininess;

            auto phongModel = std::make_shared<PhongModel>(ambient, diffuse, specular);
            auto material = std::make_shared<Material>(phongModel, shininess);

            Matrix<float, 4, 4> modelMatrix{};
            for (auto i = 0; i < 4; i++)
                for (auto j = 0; j < 4; j++)
                    file >> modelMatrix.Element(i, j);

            auto model = std::make_shared<Model>(brick, material, modelMatrix, generationParams);

            models.push_back(model);
            wireFramed.push_back(false);
        }
    }

    file.close();

    scene.Camera() = camera;
    scene.Light() = light;
    scene.Models() = models;
    scene.WireFramed() = wireFramed;

    return true;
}

void Backend::SaveScene(const std::string &filename) {
    std::ofstream file;
    file.open(filename);

    auto camera = scene.Camera();

    auto up = camera->UpNormal();
    auto eye = camera->EyePosition();
    auto lookAt = camera->LookAtPosition();
    auto pitch = camera->PitchAngle();
    auto yaw = camera->YawAngle();
    file << "camera" << std::endl;
    file << up.X() << " " << up.Y() << " " << up.Z() << std::endl;
    file << eye.X() << " " << eye.Y() << " " << eye.Z() << std::endl;
    file << lookAt.X() << " " << lookAt.Y() << " " << lookAt.Z() << std::endl;
    file << pitch << " " << yaw << std::endl;

    auto lightPos = scene.Light()->Position();
    file << "light" << std::endl;
    file << lightPos.X() << " " << lightPos.Y() << " " << lightPos.Z() << std::endl;
    auto ambient = scene.Light()->PhongModel()->Ambient();
    auto diffuse = scene.Light()->PhongModel()->Diffuse();
    auto specular = scene.Light()->PhongModel()->Specular();
    file << ambient.R() << " " << ambient.G() << " " << ambient.B() << std::endl;
    file << diffuse.R() << " " << diffuse.G() << " " << diffuse.B() << std::endl;
    file << specular.R() << " " << specular.G() << " " << specular.B() << std::endl;

    for (const auto &m: scene.Models()) {
        const auto &matrix = m->ModelMatrix();
        file << "model" << std::endl;
        const auto &params = m->GenerationParams();
        file << params.wSections << " " << params.lSections << " " << params.hSections
             << " " << params.sectionLen << " " << params.cylinderFacesCount << std::endl;

        const auto &material = m->Material();
        const auto &phong = material->PhongModel();
        file << phong->Ambient().R() << " " << phong->Ambient().G() << " " << phong->Ambient().B() << std::endl;
        file << phong->Diffuse().R() << " " << phong->Diffuse().G() << " " << phong->Diffuse().B() << std::endl;
        file << phong->Specular().R() << " " << phong->Specular().G() << " " << phong->Specular().B() << std::endl;
        file << material->Shininess() << std::endl;

        for (auto i = 0; i < 4; i++) {
            for (auto j = 0; j < 4; j++) {
                file << matrix.Element(i, j);
                if (j != 3) {
                    file << " ";
                }
            }
            file << std::endl;
        }
    }

    file.close();
}


void Backend::Render(ColorBuffer &colorBuffer) {
    if (scene.Models().empty()) {
        return;
    }

    RasterizationPipeline pipeline;
    pipeline(colorBuffer, scene);
}

void Backend::CameraScale(float ratio) {
    auto &camera = scene.Camera();
    if (!camera) {
        return;
    }

    camera->Scale(ratio);
}

void Backend::CameraMoveRightAxis(float delta) {
    auto &camera = scene.Camera();
    if (!camera) {
        return;
    }

    camera->MoveRightAxis(delta);
}

void Backend::CameraMoveForwardAxis(float delta) {
    auto &camera = scene.Camera();
    if (!camera) {
        return;
    }

    camera->MoveForwardAxis(delta);
}

void Backend::CameraPitch(float angle) const {
    auto camera = scene.Camera();
    if (!camera) {
        return;
    }

    camera->Pitch(angle);
}

void Backend::CameraYaw(float angle) const {
    auto camera = scene.Camera();
    if (!camera) {
        return;
    }

    camera->Yaw(angle);
}

unsigned Backend::AddModel(const BrickGenerationParams &generationParams) {
    BrickGenerator brickGenerator;
    auto brick = brickGenerator(generationParams);

    auto cyanPlasticAmbient = ColorRGBf(0.0, 0.1, 0.06);
    auto cyanPlasticDiffuse = ColorRGBf(0.0, 0.50980392, 0.50980392);
    auto cyanPlasticSpecular = ColorRGBf(0.50196078, 0.50196078, 0.50196078);
    float cyanPlasticShininess = 0.25;
    auto cyanPlasticPhong = std::make_shared<PhongModel>(cyanPlasticAmbient, cyanPlasticDiffuse,
                                                         cyanPlasticSpecular);
    auto cyanPlasticMaterial = std::make_shared<Material>(cyanPlasticPhong, cyanPlasticShininess);

    Matrix<float, 4, 4> matrix(glm::mat4(1));
    auto model = std::make_shared<Model>(brick, cyanPlasticMaterial, matrix, generationParams);

    scene.Models().push_back(model);
    scene.WireFramed().push_back(false);
    return scene.Models().size() - 1;
}

void Backend::RemoveModel(unsigned modelId) {
    auto &models = scene.Models();
    auto &wireFramed = scene.WireFramed();
    if (modelId >= models.size()) {
        return;
    }

    models.erase(models.begin() + (int) modelId);
    wireFramed.erase(wireFramed.begin() + (int) modelId);
}

void Backend::AddWireFramed(unsigned modelId) {
    auto &wireFramed = scene.WireFramed();
    if (modelId >= wireFramed.size()) {
        return;
    }

    wireFramed[modelId] = true;
}

void Backend::RemoveWireFramed(unsigned modelId) {
    auto &wireFramed = scene.WireFramed();
    if (modelId >= wireFramed.size()) {
        return;
    }

    wireFramed[modelId] = false;
}

void Backend::ModelMoveForwardAxis(unsigned id, float delta) {
    if (id >= scene.Models().size()) {
        return;
    }

    auto model = scene.Models()[id];
    auto camera = scene.Camera();
    auto viewN = Normal(camera->EyePosition(), camera->LookAtPosition());
    Normal rightN(1, 0, 0);
    Normal forwardN(0, 0, -1);

    std::shared_ptr<IMatrixOperation> move;

    float cosRight = viewN * rightN;
    float cosForward = viewN * forwardN;
    if (std::abs(cosForward) >= std::abs(cosRight)) {
        if (cosForward < 0) {
            delta *= -1;
        }
        move = std::make_shared<MatrixMoveZ>(-delta);
    } else {
        if (cosRight < 0) {
            delta *= -1;
        }
        move = std::make_shared<MatrixMoveX>(delta);
    }

    auto &modelMatrix = model->ModelMatrix();
    modelMatrix = move->GetMatrix() * modelMatrix;
}

void Backend::ModelMoveRightAxis(unsigned id, float delta) {
    if (id >= scene.Models().size()) {
        return;
    }

    auto model = scene.Models()[id];
    auto camera = scene.Camera();
    auto viewN = Normal(camera->EyePosition(), camera->LookAtPosition());
    Normal rightN(1, 0, 0);
    Normal forwardN(0, 0, -1);

    std::shared_ptr<IMatrixOperation> move;

    float cosRight = viewN * rightN;
    float cosForward = viewN * forwardN;
    if (std::abs(cosForward) >= std::abs(cosRight)) {
        if (cosForward < 0) {
            delta *= -1;
        }
        move = std::make_shared<MatrixMoveX>(delta);
    } else {
        if (cosRight < 0) {
            delta *= -1;
        }
        move = std::make_shared<MatrixMoveZ>(delta);
    }

    auto &modelMatrix = model->ModelMatrix();
    modelMatrix = move->GetMatrix() * modelMatrix;
}

void Backend::ModelMoveUpAxis(unsigned id, float delta) {
    if (id >= scene.Models().size()) {
        return;
    }

    auto model = scene.Models()[id];
    auto move = std::make_shared<MatrixMoveY>(delta);

    auto &modelMatrix = model->ModelMatrix();
    modelMatrix = move->GetMatrix() * modelMatrix;
}

void Backend::ModelRotateAroundUpAxis(unsigned id, float angle) {
    if (id >= scene.Models().size()) {
        return;
    }

    auto model = scene.Models()[id];
    auto rotate = std::make_shared<MatrixRotateY>(angle);

    MatrixTransformer transformer;
    auto &modelMatrix = model->ModelMatrix();
    auto toLocalBasis = std::make_shared<MatrixArbitrary>(modelMatrix.Inversed());
    auto toWorldBasis = std::make_shared<MatrixArbitrary>(modelMatrix);

    transformer.AddOperation(toLocalBasis);
    transformer.AddOperation(rotate);
    transformer.AddOperation(toWorldBasis);

    modelMatrix = transformer.GetMatrix() * modelMatrix;
}

std::vector<BrickGenerationParams> Backend::GetModelsGenerationParams() const {
    const auto &models = scene.Models();
    std::vector<BrickGenerationParams> generationParams;
    generationParams.reserve(models.size());

    for (const auto &m : models) {
        generationParams.push_back(m->GenerationParams());
    }

    return generationParams;
}
