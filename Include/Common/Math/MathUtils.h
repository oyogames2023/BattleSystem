#pragma once

#include "Common.h"
#include "Vector3.h"

#define SAFE_INCREASE(var, increase, max) \
    do { \
        if ((max) - (var) > (increase)) { \
            (var) += (increase); \
        } else { \
            (var) = (max); \
        } \
    } while(0)


#define SAFE_DECREASE(var, decrease) \
    do { \
        if ((var) > (decrease)) { \
            (var) -= (decrease); \
        } else { \
            (var) = 0; \
        } \
    } while(0)

namespace zeus::math
{



} // namespace zeus::math
