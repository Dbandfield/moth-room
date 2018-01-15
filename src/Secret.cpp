/*
 * Secret.cpp
 *
 *  Created on: 16 Dec 2017
 *      Author: daniel
 */

#include "Secret.h"

namespace moth
{

Secret::Secret(std::string _short, std::string _text, unsigned int _id)
{
	m_short = _short;
	m_text = _text;
	m_id = _id;

	m_power = 100;
}

Secret::~Secret()
{
}

void Secret::useSecret()
{
	m_power = std::max(0, m_power - 25);
}

} /* namespace moth */
