#pragma once

#include <algorithm>

#include "Location.h"

namespace moth
{

class MothLocation: public Location
{
public:
	MothLocation(MothLocation* _loc);
	MothLocation(std::string _description, unsigned int _id);
	virtual ~MothLocation();

	void addInvalidSecret(unsigned int _secret);

	bool tellTheMothASecret(Secret* _secret);

	unsigned int getOpinion(){return opinion;};

protected:
	bool isValid(Secret* _secret);

	unsigned int opinion;

	// If a secret id is here, that means that secret has no effect on this moth
	std::vector<unsigned int> m_invalidSecrets;
};

} /* namespace moth */
