/*
 * MapContainer.cpp
 *
 *  Created on: 26 Jan 2018
 *      Author: daniel
 */

#include "MapContainer.h"

namespace VO
{

MapContainer::MapContainer()
{
	// TODO Auto-generated constructor stub

}

MapContainer::~MapContainer()
{
	// TODO Auto-generated destructor stub
}

void MapContainer::setPosition(ofPoint _pt)
{
	position = ofPoint(_pt);
}

void MapContainer::recalcMapPos()
{
	for(auto&& it : children)
	{
		MapText& txt = static_cast<MapText&>(it);
		txt.setPos(position.x + (width*txt.getPropX()), position.y + (height*txt.getPropY()));
	}
}

void MapContainer::setText(std::string _str, float _propX, float _propY)
{
	MapText* frame = new MapText(width - (marginLeft + marginRight),
			height - (marginTop + marginBottom),
			ofPoint(position.x + marginLeft, position.y + marginTop), false,
			false);
	frame->setText(_str);
	frame->setPropPos(_propX, _propY);
	children.push_back(frame);
}

} /* namespace VO */
