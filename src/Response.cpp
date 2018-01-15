/*
 * Response.cpp
 *
 *  Created on: 14 Jan 2018
 *      Author: daniel
 */

#include "Response.h"

namespace moth
{

Response::Response(RESPONSE _type, unsigned int _id, std::string _text,
		int _threshold, unsigned int _skill, std::string _desc)
{
	m_type = _type;
	m_id = _id;
	m_text = _text;
	m_threshold = _threshold;
	m_skill = _skill;
	m_description = _desc;

}

Response::~Response()
{
	// TODO Auto-generated destructor stub
}

std::string Response::getDescription()

{
	return m_description;
}

RESPONSE Response::getType()
{
	return m_type;
}
unsigned int Response::getSkill()
{
	return m_skill;
}
int Response::getThreshold()
{
	return m_threshold;
}
unsigned int Response::getId()
{
	return m_id;
}
std::string Response::getText()
{
	return m_text;
}

} /* namespace moth */
