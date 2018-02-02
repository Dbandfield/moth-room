/*
 * Skill.cpp
 *
 *  Created on: 14 Jan 2018
 *      Author: daniel
 */

#include "Skill.h"

namespace moth
{

Skill::Skill(std::string _text, unsigned int _id)
{
	m_text = _text;
	m_id = _id;
}

Skill::~Skill()
{
	// TODO Auto-generated destructor stub
}


std::string Skill::getText()
{
	return m_text;
}

unsigned int Skill::getId()
{
	return m_id;
}

} /* namespace moth */
