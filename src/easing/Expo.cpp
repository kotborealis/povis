#include "Expo.h"

namespace PovisEngine{
namespace Easing{

float Expo::easeIn(float t, float b, float c, float d){
    return (float)((t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b);
}

float Expo::easeOut(float t, float b, float c, float d){
    return (float)((t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b);
}

float Expo::easeInOut(float t, float b, float c, float d){
    if(t == 0) return b;
    if(t == d) return b + c;
    if((t /= d / 2) < 1) return (float)(c / 2 * pow(2, 10 * (t - 1)) + b);
    return (float)(c / 2 * (-pow(2, -10 * --t) + 2) + b);
}

}
}