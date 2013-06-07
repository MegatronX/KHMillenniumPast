/* Used to enforce cancelation/replacement
 *
 *
 *
 *
 */
#include <components/Component.h>
#include <boost/unordered_set.hpp>
namespace Game
{
	namespace Components
	{
		class CancelAndRemoveComponent : public Component
		{
		public:
		protected:
			boost::unordered_set<std::string> CancelList;
			boost::unordered_set<std::string> ReplaceList;
			int MaxCancel;
			int MaxReplace;
		private:

		};
	}

}