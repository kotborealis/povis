/*
 * Entity.h
 *
 *  Created on: 25 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Graphics.h"

namespace PovisEngine {

class Entity {
public:
	Entity(){};
	virtual ~Entity(){};
	virtual void draw()=0;
	virtual void update()=0;
};

} /* namespace PovisEngine */

#endif /* ENTITY_H_ */
