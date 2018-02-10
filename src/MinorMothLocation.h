#pragma once

#include <ofMain.h>

#include "Location.h"
#include "enums.h"


namespace moth
{

class MinorMothLocation: public Location
{
public:
	MinorMothLocation(MinorMothLocation* _other);
	MinorMothLocation(std::string _description, unsigned int _id, float _x, float _y);
	virtual ~MinorMothLocation();

	bool useSocial(SOCIAL _soc);
	unsigned int getSecret();

	inline std::vector<PERSONALITY> getAllTraits(){return m_traits;};
	inline std::vector<PERSONALITY> getRevTraits(){return m_revTraits;};
	inline int getOpinion(){return m_opinion;};

	static std::vector<std::string>mothNames;

protected:

	std::string m_name;

	std::vector<unsigned int> m_secrets;

	std::vector<PERSONALITY> m_traits; // all traits
	std::vector<PERSONALITY> m_revTraits; // revealed traits

	int m_opinion;
};

} /* namespace moth */
