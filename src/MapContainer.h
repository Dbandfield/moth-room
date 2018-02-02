#pragma once
#include "TextContainer.h"
#include "MapText.h"

namespace VO
{

class MapContainer: public moth::TextContainer
{
public:
	MapContainer();
	virtual ~MapContainer();

	void setPosition(ofPoint _pt);

	void setText(std::string _txt, float _propX, float _propY);

protected:

	void recalcMapPos();


};

} /* namespace VO */
