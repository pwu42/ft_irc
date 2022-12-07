#include "ft_irc.hpp"

bool caseInsensEqual(const std::string & a, const std::string & b)
{
	size_t size = a.size();
	if (size != b.size())
		return false;
	for (size_t i = 0; i < size; i++)
		if (std::tolower(a[i]) != std::tolower(b[i]))
			return false;
	return true;
}

std::string strlower(const std::string &str)
{
	std::string ret = str;

	for (std::string::iterator it = ret.begin(); it!=ret.end(); ++it)
		*it = std::tolower(*it);
    return ret;
}