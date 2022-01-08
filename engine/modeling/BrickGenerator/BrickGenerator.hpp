#pragma once

#include "modeling/GeometryModel/GeometryModel.hpp"

struct BrickGenerationParams {
    unsigned wSections, lSections, hSections;
    float sectionLen;
    unsigned cylinderFacesCount;
};

class BrickGenerator {
public:
    GeometryModel operator()(const BrickGenerationParams &params);

private:
    std::vector<Point3f> points;
    std::vector<Polygon> polygons;
    std::vector<Normal> normals;
    unsigned w, l, h;
    float sectionLen;
    unsigned approxN;

private:
    void reset();
    void setParams(const BrickGenerationParams &params);
    void initNormals();
    void buildBasement();
    void buildCylinder(float cylinderH, float cylinderR, unsigned wPos, unsigned lPos);
};
