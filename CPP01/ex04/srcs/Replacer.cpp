#include "Replacer.hpp"
#include <fstream>
#include <sstream>

Replacer::Replacer(const std::string &filename, const std::string &s1,
	const std::string &s2) : _filename(filename), _s1(s1), _s2(s2)
{
}

Replacer::~Replacer()
{
}

bool Replacer::execute() const
{
	if (_s1.empty() || _filename.empty())
	{
		return (false);
	}

	std::ifstream inFile(_filename.c_str());
	if (!inFile.is_open() || inFile.fail())
	{
		return (false);
	}

	std::ostringstream oss;
	oss << inFile.rdbuf();

	if (inFile.fail() && !inFile.eof())
	{
		return (false);
	}

	std::string content = oss.str();
	std::string replacedContent = _replaceString(content);

	std::string outFilename = _filename + ".replace";
	std::ofstream outFile(outFilename.c_str());
	if (!outFile.is_open() || outFile.fail())
	{
		return (false);
	}

	outFile << replacedContent;
	if (outFile.fail())
	{
		return (false);
	}

	return (true);
}

std::string Replacer::_replaceString(const std::string &content) const
{
	std::string result;
	size_t pos = 0;
	size_t prevPos = 0;

	result.reserve(content.size());

	while ((pos = content.find(_s1, pos)) != std::string::npos)
	{
		result.append(content, prevPos, pos - prevPos);
		result.append(_s2);

		pos += _s1.length();
		prevPos = pos;
	}

	result.append(content, prevPos, std::string::npos);

	return (result);
}
