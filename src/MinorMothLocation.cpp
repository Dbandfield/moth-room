/*
 * MinorMothLocation.cpp
 *
 *  Created on: 10 Feb 2018
 *      Author: daniel
 */

#include "MinorMothLocation.h"

namespace moth
{

std::vector<std::string> MinorMothLocation::mothNames = {"Anne", "George"};

MinorMothLocation::MinorMothLocation(MinorMothLocation* _other): Location(_other)
{
	m_opinion = _other->m_opinion;
	m_name= _other->m_name;
	m_traits = _other->m_traits;
	m_type = _other->m_type;
	m_secrets = _other->m_secrets;
}

MinorMothLocation::MinorMothLocation(std::string _description, unsigned int _id, float _x, float _y):
		Location(_description, _id, _x, _y)
{
	m_opinion = 50;
	int r = ofRandom(mothNames.size());
	m_name = mothNames[r];

	r = ofRandom(_PER_NUM);
	m_traits.push_back(static_cast<PERSONALITY>(r));

	m_type = LOCATION_MIN_MOTH;

}

MinorMothLocation::~MinorMothLocation()
{
	// TODO Auto-generated destructor stub
}

unsigned int MinorMothLocation::getSecret()
{
	int r = ofRandom(m_secrets.size());
	return m_secrets[r];
}

} /* namespace moth */
