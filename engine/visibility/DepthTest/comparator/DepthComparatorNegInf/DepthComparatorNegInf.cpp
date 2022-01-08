#include "DepthComparatorNegInf.hpp"

bool DepthComparatorNegInf::operator()(float newDepth, float currentDepth) const {
    return newDepth < 0 && newDepth > currentDepth;
}

DepthComparatorNegInf::~DepthComparatorNegInf() = default;
