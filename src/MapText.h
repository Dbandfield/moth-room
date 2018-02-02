#pragma once

#include "TextFrame.h"

namespace VO
{

class MapText: public moth::TextFrame
{
public:
	MapText();
	virtual ~MapText();

	float getPropX();
	float getPropY();

	void setPropPos(float _x, float _y);

protected:

	float propX;
	float propY;
};

} /* namespace VO */
