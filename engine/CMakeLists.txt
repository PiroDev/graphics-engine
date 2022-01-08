cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O3)

set(
        MODELING_SRC

        modeling/Model/Model.cpp
        modeling/Material/Material.cpp
        modeling/BrickGenerator/BrickGenerator.cpp
        modeling/GeometryModel/GeometryModel.cpp)

set(
        CORE_SRC

        core/math/interpolation/Lerp/Lerp.cpp
        core/math/interpolation/LerpXYZf/LerpXYZf.hpp

        core/primitives/color/convert/ColorRGBfToRGB.cpp
        core/primitives/color/ColorRGB.cpp
        core/primitives/color/ColorRGBf.cpp
        core/primitives/color/convert/ColorRGBfToRGB.cpp

        core/primitives/Normal/Normal.cpp
        core/primitives/Point3f/Point3f.cpp
        core/primitives/Polygon/Polygon.cpp
)

set(
        TRANSFORM_SRC

        transform/MatrixTransformer/MatrixTransformer.cpp

        transform/MatrixTransformer/operations/move/MatrixMoveX.cpp
        transform/MatrixTransformer/operations/move/MatrixMoveY.cpp
        transform/MatrixTransformer/operations/move/MatrixMoveZ.cpp

        transform/MatrixTransformer/operations/rotate/MatrixRotateX.cpp
        transform/MatrixTransformer/operations/rotate/MatrixRotateY.cpp
        transform/MatrixTransformer/operations/rotate/MatrixRotateZ.cpp

        transform/MatrixTransformer/operations/scale/MatrixScaleX.cpp
        transform/MatrixTransformer/operations/scale/MatrixScaleY.cpp
        transform/MatrixTransformer/operations/scale/MatrixScaleZ.cpp

        transform/MatrixTransformer/operations/new_basis/MatrixToZXY.cpp
        transform/MatrixTransformer/operations/MatrixArbitrary.cpp
        transform/MatrixTransformer/operations/rotate/MatrixRotateAroundNormal.cpp
        transform/MatrixTransformer/operations/new_basis/MatrixMoveOrigin.cpp
        transform/MatrixTransformer/operations/rotate/MatrixRotateEuler.cpp
        transform/MatrixTransformer/operations/scale/MatrixScaleXYZ.cpp
)

set(
        VIEW_SRC
        view/MatrixViewTransform/MatrixViewTransform.cpp
        view/Camera/Camera.cpp
        view/MatrixViewportToCanvas/MatrixViewportToCanvas.cpp
)

set(
        LIGHTNING_SRC

        lighting/PointLight/PointLight.cpp

        lighting/PhongModel/PhongModel.cpp
        lighting/PhongFragment/PhongFragment.cpp
        lighting/util/ReflectedNormalCalculator/ReflectedNormalCalculator.cpp
)

set(
        PROJECTION_SRC
        projection/MatrixPerspectiveProjection/MatrixPerspectiveProjection.cpp
        projection/MatrixCanvasToScreen/MatrixCanvasToScreen.cpp
)

set(
        VISIBILITY_SRC
        visibility/BackSurfaceCull/BackSurfaceCull.cpp
        visibility/DepthTest/DepthTest.cpp
        visibility/DepthTest/DepthBuffer/DepthBuffer.cpp
        visibility/DepthTest/ColorBuffer/ColorBuffer.cpp
        visibility/DepthTest/comparator/DepthComparatorNegInf/DepthComparatorNegInf.cpp
        visibility/DepthTest/ProjectedFragment/ProjectedFragment.cpp
)

set(
        RASTERIZATION_SRC
        rasterization/Rasterizer/Rasterizer.cpp
        rasterization/DrawLine/DrawLine.cpp
)

set(
        SHADING_SRC
        shading/PhongShader/PhongShader.cpp
)

set(
        COMMANDS_SRC
        backend.cpp
)

set(
        PIPELINE_SRC
        pipeline/RasterizationPipeline/RasterizationPipeline.cpp
)

set(
        OBJECTS_SRC
        scene/Scene.cpp
        scene/Scene.hpp
)

add_library(
        engine SHARED

        ${MODELING_SRC}
        ${CORE_SRC}
        ${TRANSFORM_SRC}
        ${VIEW_SRC}
        ${LIGHTNING_SRC}
        ${PROJECTION_SRC}
        ${VISIBILITY_SRC}
        ${RASTERIZATION_SRC}
        ${SHADING_SRC}
        ${COMMANDS_SRC}
        ${OBJECTS_SRC}
        ${PIPELINE_SRC}
)

target_include_directories(engine PUBLIC ./)