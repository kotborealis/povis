#pragma once

#include <math.h>

namespace pse{
namespace interp{

class Expo{

public:

    static float easeIn(float t, float b, float c, float d);
    static float easeOut(float t, float b, float c, float d);
    static float easeInOut(float t, float b, float c, float d);
};

}
}