#pragma once

#include <math.h>

#ifndef PI
#define PI  3.14159265
#endif

namespace PovisEngine{
namespace Easing{

class Elastic{

public:

    static float easeIn(float t, float b, float c, float d);
    static float easeOut(float t, float b, float c, float d);
    static float easeInOut(float t, float b, float c, float d);
};

}
}