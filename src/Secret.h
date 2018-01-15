#pragma once

#include <string>
#include <algorithm>

namespace moth
{

class Secret
{
public:
	Secret(std::string _short, std::string _text, unsigned int _id);
	virtual ~Secret();

	std::string getShort(){return m_short;};
	std::string getText(){return m_text;};
	unsigned int getId(){return m_id;};
	int getPower(){return m_power;};

	void useSecret();

protected:
	std::string m_short;
	std::string m_text;
	unsigned int m_id;

	int m_power; // decreases as used
};

} /* namespace moth */
