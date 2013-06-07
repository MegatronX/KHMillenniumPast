#include "StringConversionUtilities.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


sf::Vector2i ConvertStringToIntVec(const std::string& vecPos)
{
	sf::Vector2i ReturnVec(0,0);
	std::vector<std::string> posfrags;
	boost::split(posfrags, vecPos, boost::is_any_of(","));
	for (int i = 0; i < posfrags.size(); ++i)
		boost::trim(posfrags[i]);
	if (posfrags.size() > 0)
	{
		try
		{
			ReturnVec.x = boost::lexical_cast<int>(posfrags[0]);
			if (posfrags.size() > 1)
			{
				ReturnVec.y = boost::lexical_cast<int>(posfrags[1]);
			}
		}
		catch(boost::bad_lexical_cast bcast)
		{
			std::cerr << "Bad lexical cast " << bcast.what() << "\n";
		}
		
	}
	return ReturnVec;
}