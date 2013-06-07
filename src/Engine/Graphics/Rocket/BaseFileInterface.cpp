#include "BaseFileInterface.h"
#include <stdio.h>
#include <boost/filesystem.hpp>
namespace Graphics
{
	namespace RocketInterface
	{
		BaseFileInterface::BaseFileInterface(const Rocket::Core::String& root) : root(root)
		{
		}

		BaseFileInterface::~BaseFileInterface()
		{
		}

		// Opens a file.
		Rocket::Core::FileHandle BaseFileInterface::Open(const Rocket::Core::String& path)
		{
			// Attempt to open the file relative to the application's root.
			//bool exists = boost::filesystem::exists(path.CString());
			FILE* fp = fopen((root + path).CString(), "rb");
			if (fp != NULL)
				return (Rocket::Core::FileHandle) fp;

			// Attempt to open the file relative to the current working directory.
			fp = fopen(path.CString(), "rb");
			return (Rocket::Core::FileHandle) fp;
		}

		// Closes a previously opened file.
		void BaseFileInterface::Close(Rocket::Core::FileHandle file)
		{
			fclose((FILE*) file);
		}

		// Reads data from a previously opened file.
		size_t BaseFileInterface::Read(void* buffer, size_t size, Rocket::Core::FileHandle file)
		{
			return fread(buffer, 1, size, (FILE*) file);
		}

		// Seeks to a point in a previously opened file.
		bool BaseFileInterface::Seek(Rocket::Core::FileHandle file, long offset, int origin)
		{
			return fseek((FILE*) file, offset, origin) == 0;
		}

		// Returns the current position of the file pointer.
		size_t BaseFileInterface::Tell(Rocket::Core::FileHandle file)
		{
			return ftell((FILE*) file);
		}

		void BaseFileInterface::SetRootDirectory(const Rocket::Core::String& root)
		{
			this->root = root;
		}

		const Rocket::Core::String& BaseFileInterface::GetRootDirectory() const
		{
			return root;
		}

		std::string BaseFileInterface::GetRootDirectoryStr() const
		{
			return std::string(root.CString());
		}
	}
}