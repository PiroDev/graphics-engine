#pragma once

#include "visibility/DepthTest/IDepthComparator.hpp"

struct DepthComparatorNegInf : public IDepthComparator {
    bool operator() (float newDepth, float currentDepth) const override;

    ~DepthComparatorNegInf() override;
};



