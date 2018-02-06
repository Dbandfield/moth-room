/*
 * MapContainer.cpp
 *
 *  Created on: 26 Jan 2018
 *      Author: daniel
 */

#include "MapContainer.h"
#include "MapText.h"
namespace moth
{

MapContainer::MapContainer(float _width, float _height) :
		TextContainer(FLOW_HORIZONTAL)
{
	width = _width;
	height = _height;
	recalcMapPos();
}

MapContainer::~MapContainer()
{
	// TODO Auto-generated destructor stub
}

void MapContainer::setPosition(float _x, float _y)
{
	setPosition(ofPoint(_x, _y));
}
void MapContainer::setPosition(ofPoint _pt)
{
	position = ofPoint(_pt);
	recalcMapPos();
}

void MapContainer::setWidth(float _w)
{
	// nothing!
}

void MapContainer::display(LAYER _layer)
{
	TextContainer::display(_layer);

	ofSetColor(255, 255, 255);

	for (auto it : connections)
	{
		ofDrawLine(children[it.first]->getPosition(),
				children[it.second]->getPosition());
	}
}

void MapContainer::addConnection(unsigned int _node1, unsigned int _node2)
{
	connections[_node1] = _node2;
}

void MapContainer::clearConnections()
{
	connections.clear();
}

void MapContainer::recalcMapPos()
{
	for (auto it : children)
	{
		MapText* txt = static_cast<MapText*>(it);
		ofLog() << "[MAP_CONTAINER] - " << position.x << " " << position.y
				<< " " << width << " " << height << " " << txt->getPropX()
				<< " " << txt->getPropY();
		ofLog() << "[MAP_CONTAINER] - " << width * txt->getPropX();
		ofLog() << "[MAP_CONTAINER] - " << height * txt->getPropY();

		txt->setPosition(
				ofPoint(position.x + (width * txt->getPropX()),
						position.y + (height * txt->getPropY())));
	}
}

void MapContainer::setText(std::string _str, float _propX, float _propY,
		Symbol* _label)
{
	MapText* frame = new MapText(width - (marginLeft + marginRight),
			height - (marginTop + marginBottom),
			ofPoint(position.x + marginLeft, position.y + marginTop), nullptr,
			_label, true);
	frame->setText(_str);
	frame->setPropPos(_propX, _propY);
	children.push_back(frame);
}

} /* namespace moth */
