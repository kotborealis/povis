/*
 * World.h
 *
 *  Created on: 8 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include <map>
#include <string>

#include "Game.h"
#include "Area.h"
#include "GL/glu.h"

namespace PovisEngine{

class World{
public:
    World(Area *);

    ~World();

    void update();

    void draw();

private:
    Area *map;
    GLuint background_texture;
    GLuint terrain_texture;
    GLuint foreground_texture;

    std::map<unsigned char, GLuint> textures;

    void renderTexture();
};

} /* namespace PovisEngine */

#endif /* SRC_WORLD_H_ */
