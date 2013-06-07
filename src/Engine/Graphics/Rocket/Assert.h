#pragma once
#include <Rocket/Core/Log.h>
#include <Rocket/Core.h>

namespace Rocket {
	namespace Core {
		bool Assert(const char* msg, const char* file, int line)
		{
			Rocket::Core::String message(1024, "%s\n%s:%d", msg, file, line);
			return GetSystemInterface()->LogMessage(Log::LT_ASSERT, message);
		}
	}
}