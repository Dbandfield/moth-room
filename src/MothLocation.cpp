/*
 * MothLocation.cpp
 *
 *  Created on: 14 Jan 2018
 *      Author: daniel
 */

#include "MothLocation.h"

namespace moth
{

MothLocation::MothLocation(MothLocation* _loc):	Location(_loc)
{
	opinion = _loc->opinion;
	m_invalidSecrets = _loc->m_invalidSecrets;

}

MothLocation::MothLocation(std::string _description, unsigned int _id) :
		Location(_description, _id)
{
	m_type = LOCATION_MOTH;

	opinion = 50;
}

MothLocation::~MothLocation()
{
}

void MothLocation::addInvalidSecret(unsigned int _secret)
{
	m_invalidSecrets.push_back(_secret);
}

bool MothLocation::tellTheMothASecret(Secret* _secret)
{
	if (isValid(_secret))
	{
		opinion = std::min((int) 100, (int) (opinion + _secret->getPower()));
		_secret->useSecret();
		m_invalidSecrets.push_back(_secret->getId());
		return true;
	}
	else
	{
		return false;
	}
}

bool MothLocation::isValid(Secret* _secret)
{
	return std::find(m_invalidSecrets.begin(), m_invalidSecrets.end(),
			_secret->getId()) == m_invalidSecrets.end();
}

} /* namespace moth */
