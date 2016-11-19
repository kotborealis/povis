#pragma once

namespace pse{
namespace Easing{

class Linear{

public:

    static float easeNone(float t, float b, float c, float d); // ??
    static float easeIn(float t, float b, float c, float d);
    static float easeOut(float t, float b, float c, float d);
    static float easeInOut(float t, float b, float c, float d);

};

}
}