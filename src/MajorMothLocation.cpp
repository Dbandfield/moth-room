/*
 * MothLocation.cpp
 *
 *  Created on: 14 Jan 2018
 *      Author: daniel
 */

#include <MajorMothLocation.h>

namespace moth
{

MajorMothLocation::MajorMothLocation(MajorMothLocation* _loc):	Location(_loc)
{
	opinion = _loc->opinion;
	m_invalidSecrets = _loc->m_invalidSecrets;

}

MajorMothLocation::MajorMothLocation(std::string _description, unsigned int _id, float _x, float _y) :
		Location(_description, _id, _x, _y)
{
	m_type = LOCATION_MAJ_MOTH;

	opinion = 50;
}

MajorMothLocation::~MajorMothLocation()
{
}

void MajorMothLocation::addInvalidSecret(unsigned int _secret)
{
	m_invalidSecrets.push_back(_secret);
}

bool MajorMothLocation::tellTheMothASecret(Secret* _secret)
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

bool MajorMothLocation::isValid(Secret* _secret)
{
	return std::find(m_invalidSecrets.begin(), m_invalidSecrets.end(),
			_secret->getId()) == m_invalidSecrets.end();
}

} /* namespace moth */
