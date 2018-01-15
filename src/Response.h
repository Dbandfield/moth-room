#pragma once

#include <string>

#include "enums.h"

namespace moth
{

class Response
{
public:

	Response(RESPONSE _type, unsigned int _id, std::string _text,
			int _threshold, unsigned int _skill = 0, std::string _desc="");
	virtual ~Response();

	RESPONSE getType();
	unsigned int getSkill();
	int getThreshold();
	unsigned int getId();
	std::string getText();
	std::string getDescription();

protected:

	RESPONSE m_type;
	unsigned int m_skill; // only valid if taught
	int m_threshold;

	unsigned int m_id;
	std::string m_text;
	std::string m_description;
};

} /* namespace moth */
