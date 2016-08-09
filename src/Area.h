/*
 * RegionMap.h
 *
 *  Created on: 8 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef SRC_AREA_H_
#define SRC_AREA_H_

#include <vector>
#include "Zone.h"

namespace PovisEngine{

class Area{
public:
    Area(std::vector<Zone>);

    ~Area();

    std::vector<Zone> background_tiles;
    std::vector<Zone> foreground_tiles;
    std::vector<Zone> terrain_tiles;

    std::vector<Zone> collision_tiles;
    std::vector<Zone> trigger_tiles;
    std::vector<Zone> entities_tiles;
};

} /* namespace PovisEngine */

#endif /* SRC_AREA_H_ */
