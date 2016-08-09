/*
 * RegionMap.cpp
 *
 *  Created on: 8 ���. 2016 �.
 *      Author: kotborealis
 */

#include "Area.h"

namespace PovisEngine{

Area::Area(std::vector<Zone> _z){
    for(auto it=_z.begin();it!=_z.end();it++){
        Zone z=*it;

        switch(z.type){
            case 255:
                trigger_tiles.push_back(z);
                break;
            case 254:
                collision_tiles.push_back(z);
                break;
            case 253:
                entities_tiles.push_back(z);
                break;
            default:
                switch(z.zindex){
                    case 0:
                        background_tiles.push_back(z);
                        break;
                    case 1:
                        terrain_tiles.push_back(z);
                        break;
                    default:
                        foreground_tiles.push_back(z);
                }
        }
    }
}

Area::~Area(){

}

} /* namespace PovisEngine */
