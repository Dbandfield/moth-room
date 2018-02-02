/*
 * MapText.cpp
 *
 *  Created on: 26 Jan 2018
 *      Author: daniel
 */

#include "MapText.h"

namespace VO
{

MapText::MapText()
{
	// TODO Auto-generated constructor stub

}

MapText::~MapText()
{
	// TODO Auto-generated destructor stub
}

} /* namespace VO */

float MapText::getPropX()
{
	return propX;

}

float MapText::getPropY()
{
	return propY;
}

void MapText::setPropPos(float _x, float _y)
{
	propX = _x;
	propY = _y;
}
