#pragma once
#include "TextContainer.h"
#include "enums.h"

namespace moth
{

class MapText;

class MapContainer: public TextContainer
{
public:
	MapContainer(float _width, float _height);
	virtual ~MapContainer();

	float getHeight(){return height;}
	float getWidth(){return width;}

	void display(LAYER _layer);

	void setPosition(ofPoint _pt);
	void setPosition(float _x, float _y);

	void setText(std::string _txt, float _propX, float _propY, Symbol* _label);

	void setWidth(float _w);

	void addConnection(unsigned int _node1, unsigned int _node2);
	void clearConnections();

protected:

	void recalcMapPos();
	std::map<unsigned int, unsigned int> connections;


};

} /* namespace moth */
