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

void MapContainer::addChild(Symbol* _child)
{
	unsigned int ndx = children.size();
	unsigned int id = static_cast<MapText*>(_child)->getId();
	idToIndex[id] = ndx;

	ofLog() << "[MAP_CONTAINER] - adding index " << ndx << " to id " << id;

	children.push_back(_child);
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
		ofDrawLine(children[idToIndex[it.first]]->getPosition(),
				children[idToIndex[it.second]]->getPosition());
	}
}

void MapContainer::addConnection(unsigned int _node1, unsigned int _node2)
{
	connections[_node1] = _node2;
	ofLog() << "[MAP_CONTAINER] - Adding connection from " << _node1 << " to " << _node2;
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

		txt->setPosition(
				ofPoint(position.x + marginLeft + (width * txt->getPropX()),
						position.y + marginRight + (height * txt->getPropY())));
	}
}

void MapContainer::setText(unsigned int _locId, std::string _str, float _propX, float _propY,
		Symbol* _label)
{
	MapText* frame = new MapText(_locId, width - (marginLeft + marginRight),
			height - (marginTop + marginBottom),
			ofPoint(position.x + marginLeft, position.y + marginTop), nullptr,
			_label, true);
	frame->setText(_str);
	frame->setPropPos(_propX, _propY);
	children.push_back(frame);
}

} /* namespace moth */
