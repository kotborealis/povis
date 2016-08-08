/*
 * World.cpp
 *
 *  Created on: 8 рту. 2016 у.
 *      Author: kotborealis
 */

#include "World.h"

namespace PovisEngine {

World::World(Area* _map) {
	map = _map;
	background_texture = Game::i().g()->reserveTexture();
	terrain_texture = Game::i().g()->reserveTexture();
	foreground_texture = Game::i().g()->reserveTexture();

	auto g = Game::i().g();
	for(auto it = map->terrain_tiles.begin(); it != map->terrain_tiles.end(); it++){
		Zone r = *it;
		std::string file;
		if(r.type == 0){
			file="assets/textures/ground2.png";
		}
		else if(r.type == 1){
			file="assets/textures/ground1.png";
		}
		else{
			file="assets/textures/sky1.png";
		}
		textures.insert(std::pair<unsigned char, GLuint>(r.type,g->loadTexture(file)));
	}
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::draw(){

}

} /* namespace PovisEngine */
