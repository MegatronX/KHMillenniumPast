#include "SoundSystem.h"
namespace Audio
{
	void ERRCHECK(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		}
	}

	SoundSystem::SoundSystem(int ChannelCount, const std::string &MusicRootDir, const std::string &SoundEffectRootDir) :
		PrimaryAudioDirectory(MusicRootDir), PrimarySoundEffectsDirectory(SoundEffectRootDir)
	{
		MaxChannels = ChannelCount;

		Channels = new FMOD::Channel*[MaxChannels];

		FMOD::System_Create(&BaseSystem);
		BaseSystem->init(ChannelCount, FMOD_INIT_NORMAL, 0);
		BaseSystem->setStreamBufferSize(128 * 1024, FMOD_TIMEUNIT_RAWBYTES);
	}
	SoundSystem::~SoundSystem()
	{
		for(auto it = SoundSet.begin(); it != SoundSet.end(); ++it)
		{
			if (it->second != NULL)
			{
				it->second->release();
				//delete it->second;
			}
		}
		delete [] Channels;
		BaseSystem->close();
		BaseSystem->release();
	}

	bool SoundSystem::AddSound(const std::string& filename, const std::string& indexName, bool overwriteExisting, bool useStoredPath, bool IsSoundEffect, const char* extension)
	{
		if (!overwriteExisting && SoundSet.find(indexName) != SoundSet.end())
			return false;
		std::string assembledPath;
		if (!useStoredPath)
			assembledPath = filename;
		else
		{
			if (IsSoundEffect)
			{
				assembledPath += PrimarySoundEffectsDirectory;
			}
			else
			{
				assembledPath += PrimaryAudioDirectory;
			}
			assembledPath += filename + extension;
		}

		if (boost::filesystem::exists(assembledPath))
		{
			if (overwriteExisting)
				RemoveSound(indexName);
			else if (SoundSet.find(indexName) != SoundSet.end())
			{

#ifdef _DEBUG
				std::cout << "Sound " << indexName << " Already Exists!" << std::endl;
#endif
				return false;
			}

			FMOD::Sound* newSound;// = new FMOD::Sound();
			//FMOD_RESULT res = BaseSystem->createSound(filename.c_str(), FMOD_HARDWARE, 0, &newSound);
			FMOD_RESULT res = BaseSystem->createStream(assembledPath.c_str(), FMOD_HARDWARE | FMOD_LOOP_NORMAL, 0, &newSound); 
			
			SoundSet[indexName] = newSound; 
			return true;
		}
#ifdef _DEBUG
		std::cout << "Sound " << assembledPath << " could not be found!" << std::endl;
#endif
		return false;
	}
	FMOD::Sound* SoundSystem::GetSound(std::string& soundName)
	{
		if (SoundSet.find(soundName) != SoundSet.end())
		{
			return SoundSet[soundName];
		}
		return NULL;
	}
	FMOD::Sound* SoundSystem::GetSoundFromFile(std::string& fileName, std::string& soundname)
	{
		if (boost::filesystem::exists(fileName))
		{
			FMOD::Sound* newSound;// = new FMOD::Sound();
			FMOD_RESULT res = BaseSystem->createStream(fileName.c_str(), FMOD_HARDWARE, 0, &newSound);
			SoundSet[soundname] = newSound; 
			return newSound;
		}
		return NULL;
	}
	void SoundSystem::Play(const std::string &soundName, int channel, bool loop, float Volume)
	{
		auto PlayableSound = SoundSet.find(soundName);
		if (PlayableSound != SoundSet.end())
		{
			if (channel > MaxChannels - 1)
				channel %= MaxChannels;
			
			//SoundSet[soundName].setLo
			//auto PlayableSound = SoundSet[soundName];
			 
			if (!loop)
				PlayableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_OFF);
			else
				PlayableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_NORMAL);
			FMOD_RESULT res = BaseSystem->playSound(FMOD_CHANNEL_FREE, PlayableSound->second, false, &Channels[channel]);
			res = Channels[channel]->setVolume(Volume);
			BaseSystem->update();
		}
	}
	void SoundSystem::PlaySection(const std::string &soundName, int channel, bool loop, int StartMilliseconds, int EndMilliseconds, float Volume)
	{
		auto PlayableSound = SoundSet.find(soundName);
		if (PlayableSound != SoundSet.end())
		{
			if (channel > MaxChannels - 1)
				channel %= MaxChannels;
			//SoundSet[soundName].setLo
			//auto PlayableSound = SoundSet[soundName];
			if (!loop)
				PlayableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_OFF);
			else
				PlayableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_NORMAL);
	
			
			if (StartMilliseconds >= 0 || EndMilliseconds >= 0)
			{
				int startTime;
				int endTime;
				unsigned int SongLength;
				PlayableSound->second->getLength(&SongLength, FMOD_TIMEUNIT_MS);
				if (StartMilliseconds >= 0)
				{
					if (StartMilliseconds > SongLength)
					{
#ifdef _DEBUG
						std::cerr << "Attempted to set song loop start point to longer then song length StartMS " << StartMilliseconds << " | Song Length MS " << SongLength << std::endl;
#endif
						startTime = SongLength;
					}
					else
					{
						startTime = StartMilliseconds;
					}
					if (EndMilliseconds > SongLength)
					{
#ifdef _DEBUG
						std::cerr << "Attempted to set song loop end point to longer then song length StartMS " << StartMilliseconds << " | Song Length MS " << SongLength << std::endl;
#endif
						endTime = SongLength;
					}
					else
					{
						endTime = EndMilliseconds;
					}
					PlayableSound->second->setLoopPoints(startTime, FMOD_TIMEUNIT_MS, endTime, FMOD_TIMEUNIT_MS);
				}
			}
			FMOD_RESULT res = BaseSystem->playSound(FMOD_CHANNEL_FREE, PlayableSound->second, false, &Channels[channel]);
			res = Channels[channel]->setVolume(Volume);
			BaseSystem->update();
		}
	}
	void SoundSystem::PlaySectionWithStart(const std::string &soundName, int channel, bool loop, int initialMilliseconds, int LoopStartMilliseconds, int LoopEndMilliseconds, float Volume)
	{
		auto PlayableSound = SoundSet.find(soundName);
		if (PlayableSound != SoundSet.end())
		{
			if (channel > MaxChannels - 1)
				channel %= MaxChannels;
			//SoundSet[soundName].setLo
			//auto PlayableSound = SoundSet[soundName];
			if (!loop)
				PlayableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_OFF);
			else
				PlayableSound->second->setMode(FMOD_HARDWARE | FMOD_LOOP_NORMAL);


			if (LoopStartMilliseconds >= 0 || LoopEndMilliseconds >= 0)
			{
				int startTime;
				int endTime;
				unsigned int SongLength;
				PlayableSound->second->getLength(&SongLength, FMOD_TIMEUNIT_MS);
				if (LoopStartMilliseconds >= 0)
				{
					if (LoopStartMilliseconds > SongLength)
					{
#ifdef _DEBUG
						std::cerr << "Attempted to set song loop start point to longer then song length StartMS " << LoopStartMilliseconds << " | Song Length MS " << SongLength << std::endl;
#endif
						startTime = SongLength;
					}
					else
					{
						startTime = LoopStartMilliseconds;
					}
					if (LoopEndMilliseconds > SongLength)
					{
#ifdef _DEBUG
						std::cerr << "Attempted to set song loop end point to longer then song length StartMS " << LoopEndMilliseconds << " | Song Length MS " << SongLength << std::endl;
#endif
						endTime = SongLength;
					}
					else
					{
						endTime = LoopEndMilliseconds;
					}
					PlayableSound->second->setLoopPoints(startTime, FMOD_TIMEUNIT_MS, endTime, FMOD_TIMEUNIT_MS);
				}
			}
			FMOD_RESULT res = BaseSystem->playSound(FMOD_CHANNEL_FREE, PlayableSound->second, false, &Channels[channel]);
			res = Channels[channel]->setVolume(Volume);
			BaseSystem->update();
		}
	}
	void SoundSystem::StopChannel(int ChannelNum)
	{
		if (ChannelNum < MaxChannels && Channels[ChannelNum] != NULL)
		{
			Channels[ChannelNum]->stop();
		}
	}
	void SoundSystem::SetChannelPause(int ChannelNum, bool ChannelPause)
	{
		if (ChannelNum < MaxChannels && Channels[ChannelNum] != NULL)
		{
			Channels[ChannelNum]->setPaused(ChannelPause);
		}
	}
	void SoundSystem::MultiplyPlaybackSpeed(int ChannelID, float PlaybackMult)
	{
		if (ChannelID < MaxChannels && Channels[ChannelID] != NULL)
		{
			float freq = 0.0f;
			Channels[ChannelID]->getFrequency(&freq);
			Channels[ChannelID]->setFrequency(freq * PlaybackMult);
		}
	}
	bool SoundSystem::GetPausedStatus(int ChannelNum)
	{
		bool Status = false;
		if (ChannelNum < MaxChannels && Channels[ChannelNum] != NULL)
		{
			 Channels[ChannelNum]->getPaused(&Status);
		}
		return Status;
	}
	void SoundSystem::MakeGroups(int groupCount)
	{
	}
	void SoundSystem::RemoveSound(const std::string &soundName)
	{
		auto it = SoundSet.find(soundName);
		if (it != SoundSet.end())
		{
			it->second->release();
			SoundSet.erase(it);
		}
	}
	void SoundSystem::ClearSounds()
	{
		for(auto it = SoundSet.begin(); it != SoundSet.end(); ++it)
		{
			if (it->second != NULL)
			{
				it->second->release();
				//SoundSet.erase(it);
				//delete it->second;
			}
		}
		SoundSet.clear();
	}

	void SoundSystem::PlayRawSound(FMOD::Sound* sound, int channel)
	{

	}
	void SoundSystem::SetAudioDirectory(const std::string &directory)
	{
		PrimaryAudioDirectory = directory;
	}
	void SoundSystem::SetSoundEffectsDirectory(const std::string &directory)
	{
		PrimarySoundEffectsDirectory = directory;
	}
}