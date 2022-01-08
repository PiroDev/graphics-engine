#include "BrickGenerator.hpp"
#include "transform/MatrixTransformer/MatrixTransformer.hpp"
#include "transform/MatrixTransformer/operations/new_basis/MatrixToZXY.hpp"

GeometryModel BrickGenerator::operator()(const BrickGenerationParams &params) {
    reset();
    setParams(params);

    initNormals();
    buildBasement();

    float cylinderH = 2 * sectionLen / 9;
    float cylinderR = 23 * sectionLen / 80;

    /* Generate cylinders */
    for (unsigned wPos = 0; wPos < w; wPos++) {
        for (unsigned lPos = 0; lPos < l; lPos++) {
            buildCylinder(cylinderH, cylinderR, wPos, lPos);
        }
    }

    MatrixTransformer modelPointsTransformer;
    auto toZXY = std::make_shared<MatrixToZXY>();
    modelPointsTransformer.AddOperation(toZXY);
    MatrixTransformer normalsTransformer(modelPointsTransformer.GetMatrix().Transposed().Inversed());

    for (auto &p: points) {
        modelPointsTransformer.ApplyTransforms(p);
    }

    for (auto &n: normals) {
        normalsTransformer.ApplyTransforms(n);
    }

    return {points, normals, polygons};
}

void BrickGenerator::reset() {
    points.resize(0);
    polygons.resize(0);
    normals.resize(0);
}

void BrickGenerator::setParams(const BrickGenerationParams &params) {
    w = params.wSections;
    l = params.lSections;
    h = params.hSections;
    sectionLen = params.sectionLen;
    approxN = params.cylinderFacesCount;

    unsigned pointsCount = 8 + 2 * l * w * (2 * approxN + 1);
    unsigned polygonsCount = 2 * (6 + 3 * approxN * l * w);
    unsigned normalsCount = 6 + l * w * approxN;

    points.reserve(pointsCount);
    polygons.reserve(polygonsCount);
    normals.reserve(normalsCount);
}

void BrickGenerator::initNormals() {
    Normal xN(1, 0, 0); //0
    Normal xMinus(-xN); //1
    Normal yN(0, 1, 0); //2
    Normal yMinus(-yN); //3
    Normal zN(0, 0, 1); //4
    Normal zMinus(-zN); //5

    normals.insert(normals.end(), {xN, xMinus, yN, yMinus, zN, zMinus});
}

void BrickGenerator::buildBasement() {
    float width = sectionLen * (float) w;
    float length = sectionLen * (float) l;
    float height = sectionLen * (float) h;

    Point3f bottomBase1(0, 0, 0); //0
    Point3f bottomBase2(width, 0, 0); //1
    Point3f bottomBase3(width, length, 0); //2
    Point3f bottomBase4(0, length, 0); //3

    Point3f topBase1(0, 0, height); //4
    Point3f topBase2(width, 0, height); //5
    Point3f topBase3(width, length, height); //6
    Point3f topBase4(0, length, height); //7

    points.insert(points.end(),
                  {
                          bottomBase1, bottomBase2, bottomBase3, bottomBase4,
                          topBase1, topBase2, topBase3, topBase4
                  }
    );

    Polygon frontFace1({1, 5, 6}, {0, 0, 0});
    Polygon frontFace2({1, 6, 2}, {0, 0, 0});
    Polygon frontFace3({1, 5, 6}, {1, 1, 1});
    Polygon frontFace4({1, 6, 2}, {1, 1, 1});

    Polygon backFace1({0, 4, 7}, {1, 1, 1});
    Polygon backFace2({0, 7, 3}, {1, 1, 1});
    Polygon backFace3({0, 4, 7}, {0, 0, 0});
    Polygon backFace4({0, 7, 3}, {0, 0, 0});

    Polygon topFace1({4, 5, 6}, {4, 4, 4});
    Polygon topFace2({4, 6, 7}, {4, 4, 4});
    Polygon topFace3({4, 5, 6}, {5, 5, 5});
    Polygon topFace4({4, 6, 7}, {5, 5, 5});

    Polygon rightFace1({2, 6, 7}, {2, 2, 2});
    Polygon rightFace2({2, 7, 3}, {2, 2, 2});
    Polygon rightFace3({2, 6, 7}, {3, 3, 3});
    Polygon rightFace4({2, 7, 3}, {3, 3, 3});

    Polygon leftFace1({0, 4, 5}, {3, 3, 3});
    Polygon leftFace2({0, 5, 1}, {3, 3, 3});
    Polygon leftFace3({0, 4, 5}, {2, 2, 2});
    Polygon leftFace4({0, 5, 1}, {2, 2, 2});

    Polygon bottomFace1({0, 1, 2}, {5, 5, 5});
    Polygon bottomFace2({0, 2, 3}, {5, 5, 5});
    Polygon bottomFace3({0, 1, 2}, {4, 4, 4});
    Polygon bottomFace4({0, 2, 3}, {4, 4, 4});

    polygons.insert(polygons.end(),
                    {
                            frontFace1, frontFace2, frontFace3, frontFace4,
                            backFace1, backFace2, backFace3, backFace4,
                            leftFace1, leftFace2, leftFace3, leftFace4,
                            rightFace1, rightFace2, rightFace3, rightFace4,
                            topFace1, topFace2, topFace3, topFace4,
                            bottomFace1, bottomFace2, bottomFace3, bottomFace4
                    }
    );
}

void BrickGenerator::buildCylinder(float cylinderH, float cylinderR, unsigned wPos, unsigned lPos) {
    float height = sectionLen * (float) h;

    float xC = ((float) wPos + 0.5f) * sectionLen;
    float yC = ((float) lPos + 0.5f) * sectionLen;

    Point3f bottomCenter(xC, yC, height);
    Point3f topCenter(xC, yC, height + cylinderH);

    float angle = 0;
    float angleDelta = 2 * (float) M_PI / (float) approxN;

    std::vector<Point3f> bottomCirclePoints(approxN);
    std::vector<Point3f> topCirclePoints(approxN);
    std::vector<Normal> circleNormals(approxN);
    std::vector<Polygon> cylinderPolygons(approxN * 3);

    unsigned pointsCnt = points.size();
    unsigned normalsCnt = normals.size();
    unsigned topCenterPos = pointsCnt + 2 * approxN;

    unsigned bottomPos, normalPos, topPos;
    unsigned i = 0;
    for (; i < approxN; i++) {
        float x = xC + cylinderR * std::cos(angle);
        float y = yC + cylinderR * std::sin(angle);

        bottomCirclePoints[i] = Point3f(x, y, height);
        topCirclePoints[i] = Point3f(x, y, height + cylinderH);
        circleNormals[i] = Normal(bottomCenter, bottomCirclePoints[i]);

        bottomPos = pointsCnt + i;
        topPos = approxN + bottomPos;

        normalPos = normalsCnt + i;

        cylinderPolygons[2 * i] = Polygon({bottomPos, topPos, bottomPos + 1},
                                          {normalPos, normalPos, normalPos + 1});
        cylinderPolygons[2 * i + 1] = Polygon({topPos, bottomPos + 1, topPos + 1},
                                              {normalPos, normalPos + 1, normalPos + 1});

        angle += angleDelta;
    }
    i--;

    cylinderPolygons[2 * i] = Polygon({bottomPos, topPos, pointsCnt},{normalPos, normalPos, normalsCnt});
    cylinderPolygons[2 * i + 1] = Polygon({topPos, pointsCnt, pointsCnt + approxN},{normalPos, normalsCnt, normalsCnt});

    unsigned pos = approxN + pointsCnt; // topCircle
    for (i = 0; i < approxN; i++, pos++) {
        cylinderPolygons[approxN * 2 + i] = Polygon({pos, pos + 1, topCenterPos}, {4, 4, 4});
    }
    cylinderPolygons[approxN * 2 + i - 1] = Polygon({pos - 1, pos - approxN, topCenterPos}, {4, 4, 4});

    points.insert(points.end(), bottomCirclePoints.begin(), bottomCirclePoints.end());
    points.insert(points.end(), topCirclePoints.begin(), topCirclePoints.end());
    points.push_back(topCenter);
    normals.insert(normals.end(), circleNormals.begin(), circleNormals.end());
    polygons.insert(polygons.end(), cylinderPolygons.begin(), cylinderPolygons.end());
}

