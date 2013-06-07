#pragma once
#ifndef _BASEFILEINTERFACE_H_
#define _BASEFILEINTERFACE_H_

#include <Rocket/Core/String.h>
#include <Rocket/Core/FileInterface.h>

namespace Graphics
{
	namespace RocketInterface
	{
		class BaseFileInterface : public Rocket::Core::FileInterface
		{
		public:
			BaseFileInterface(const Rocket::Core::String& root);
			virtual ~BaseFileInterface();

			/// Opens a file.		
			virtual Rocket::Core::FileHandle Open(const Rocket::Core::String& path);

			/// Closes a previously opened file.		
			virtual void Close(Rocket::Core::FileHandle file);

			/// Reads data from a previously opened file.		
			virtual size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file);

			/// Seeks to a point in a previously opened file.		
			virtual bool Seek(Rocket::Core::FileHandle file, long offset, int origin);

			/// Returns the current position of the file pointer.		
			virtual size_t Tell(Rocket::Core::FileHandle file);

			void SetRootDirectory(const Rocket::Core::String& root);

			const Rocket::Core::String& GetRootDirectory() const;

			std::string GetRootDirectoryStr() const;
		protected:
			Rocket::Core::String root;
		};
	}
}

#endif