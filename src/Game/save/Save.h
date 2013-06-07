#include <string>

namespace Game
{
	struct SaveFileHeader
	{
		std::string PartyLeader;
		std::string SaveTime;
		std::string AreaMajor;
		std::string AreaMinor;
		unsigned int Munny;
		unsigned int Hours;
		unsigned int Minutes;
		unsigned int Seconds;

	};
}