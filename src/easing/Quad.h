#pragma once

namespace PovisEngine{
namespace Easing{

class Quad{

public:

    static float easeIn(float t, float b, float c, float d);
    static float easeOut(float t, float b, float c, float d);
    static float easeInOut(float t, float b, float c, float d);
};

}
}