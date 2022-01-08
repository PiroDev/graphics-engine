#pragma once

struct IDepthComparator {
    virtual bool operator() (float newDepth, float currentDepth) const = 0;

    virtual ~IDepthComparator() = default;
};
