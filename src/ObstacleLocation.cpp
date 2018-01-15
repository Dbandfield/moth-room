/*
 * ObstacleLocation.cpp
 *
 *  Created on: 14 Jan 2018
 *      Author: daniel
 */

#include "ObstacleLocation.h"

namespace moth
{

ObstacleLocation::ObstacleLocation(std::string _description, unsigned int _id,
		unsigned int _skillNeeded, unsigned int _skillGiven) :
		Location(_description, _id)
{
	m_skillNeeded = _skillNeeded;
	m_skillGiven = _skillGiven;

	m_solved = false;

	m_type = LOCATION_OBSTACLE;
}

ObstacleLocation::~ObstacleLocation()
{
}

void ObstacleLocation::addBlockedLink(unsigned int _link)
{
	m_blockedLinks.push_back(_link);
}

bool ObstacleLocation::solve(unsigned int _skill)
{
	if (_skill == m_skillNeeded)
	{
		m_solved = true;
		return true;
	}
	else
	{
		return false;
	}
}

unsigned int ObstacleLocation::getSkillNeeded()
{
	return m_skillNeeded;
}

unsigned int ObstacleLocation::getSkillGiven()
{
	return m_skillGiven;
}

} /* namespace moth */
