#pragma once

#include "core/primitives/Normal/Normal.hpp"

struct ReflectedNormalCalculator {
    Normal operator() (const Normal &incident, const Normal &axis) const;
};

Normal reflectedNormalCalculator(const Normal &incident, const Normal &axis);
