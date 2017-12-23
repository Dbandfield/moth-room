/*
 * Secret.cpp
 *
 *  Created on: 16 Dec 2017
 *      Author: daniel
 */

#include "Secret.h"

namespace moth
{

Secret::Secret(std::string _text, unsigned int _id)
{
	text = _text;
	id = _id;
}

Secret::~Secret()
{
}

} /* namespace moth */
