/*
 * Tile.h
 *
 *  Created on: 8 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef SRC_ZONE_H_
#define SRC_ZONE_H_

namespace PovisEngine{

struct Zone{
    unsigned int x; //x-coord
    unsigned int y; //y-coord
    unsigned int w; //m_width of region
    unsigned int h; //m_height of region
    unsigned char type; //0-253 - tiles, 253 - entity, 254 - collision, 255 - trigger
    unsigned char zindex; //0 - background, 1 - terrain, 2 - foreground
    unsigned char data[2];
};

} /* namespace PovisEngine */

#endif /* SRC_ZONE_H_ */
