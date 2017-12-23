#pragma once
#include <string>

namespace moth
{

class Secret
{
public:
	Secret(std::string text, unsigned int _id);
	virtual ~Secret();

	std::string getText(){return text;};
	unsigned int getId(){return id;};

protected:
	std::string text;
	unsigned int id;
};

} /* namespace moth */
