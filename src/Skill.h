#pragma once

#include <string>

#include "enums.h"

namespace moth
{

class Skill
{
public:
	Skill(std::string _text, unsigned int _id);
	virtual ~Skill();

	std::string getText();
	unsigned int getId();

protected:

	std::string m_text;
	unsigned int m_id;

};

} /* namespace moth */
