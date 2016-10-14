#include "Linear.h"

namespace PovisEngine{
namespace Easing{

float Linear::easeNone(float t, float b, float c, float d){
    return c * t / d + b;
}

float Linear::easeIn(float t, float b, float c, float d){
    return c * t / d + b;
}

float Linear::easeOut(float t, float b, float c, float d){
    return c * t / d + b;
}

float Linear::easeInOut(float t, float b, float c, float d){
    return c * t / d + b;
}

}
}