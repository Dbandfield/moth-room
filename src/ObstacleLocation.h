#pragma once

#include "Location.h"

#include "enums.h"

namespace moth
{

class ObstacleLocation: public Location
{
public:
	ObstacleLocation(ObstacleLocation* _loc);
	ObstacleLocation(std::string _description, unsigned int _id,
			unsigned int _skillNeeded, unsigned int _skillGiven);
	virtual ~ObstacleLocation();

	void addBlockedLink(unsigned int _id);

	bool solve(unsigned int _skill);

	unsigned int getSkillNeeded();
	unsigned int getSkillGiven();

protected:

	bool m_solved;
	unsigned int m_skillNeeded;

	unsigned int m_skillGiven;

	std::vector<unsigned int> m_blockedLinks;
};

} /* namespace moth */
