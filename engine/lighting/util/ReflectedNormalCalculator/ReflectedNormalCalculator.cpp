#include "ReflectedNormalCalculator.hpp"
#include "core/math/MathVector/MathVector.hpp"

Normal ReflectedNormalCalculator::operator()(const Normal &incident, const Normal &axis) const {
    auto incV = MathVector<float, 3>{{incident.X(), incident.Y(), incident.Z()}};
    auto axisV = MathVector<float, 3>{{axis.X(), axis.Y(), axis.Z()}};

    auto reflected = incV - 2 * (incV * axisV) * axisV;

    return {reflected[0], reflected[1], reflected[2]};
}
