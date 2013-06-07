#pragma once
#ifndef _SOUNDSYSTEM_H_
#define _SOUNDSYSTEM_H_
#include <fmod/fmod.hpp>
#include <fmod/fmod_dsp.h>
#include <fmod/fmod_errors.h>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/filesystem.hpp>
#include <audio/SectionLoopableMusic.h>
class Engine;

namespace Audio
{
	enum SoundChannels
	{
		Music1 = 0,
		Music2 = 1,
		SoundEffects1 = 2,
		SoundEffects2 = 3,
		MenuSounds = 4,
		Voices = 5,
	};
	class SoundSystem
	{
	public:
		SoundSystem(int ChannelCount = 32, const std::string &MusicRootDir = std::string(), const std::string &SoundEffectRootDir = std::string());

		bool AddSound(const std::string& filename, const std::string& indexName, bool overwriteExisting = true, bool useStoredPath = true, bool IsSoundEffect = false, const char* extension = ".mp3");
		FMOD::Sound* GetSound (std::string& soundName);
		FMOD::Sound* GetSoundFromFile(std::string& fileName, std::string& soundname);
		void Play(const std::string &soundName, int channel = 0, bool loop = true, float Volume = 1.0);
		void PlaySection(const std::string &soundName, int channel = 0, bool loop = true, int StartMilliseconds = -1, int EndMilliseconds = -1, float Volume = 1.0);
		void PlaySectionWithStart(const std::string &soundName, int channel = 0, bool loop = true, int intialMilliseconds = 0, int LoopStartMilliseconds = -1, int LoopEndMilliseconds = -1, float Volume = 1.0);
		void StopChannel(int ChannelNum);
		void SetChannelPause(int ChannelNum, bool ChannelPause = true);
		void MultiplyPlaybackSpeed(int ChannelID = 0, float PlaybackMult = 1.0f);
		bool GetPausedStatus(int ChannelNum);
		void MakeGroups(int groupCount);
		void RemoveSound(const std::string &soundName);
		void ClearSounds();
		void PlayRawSound(FMOD::Sound* sound, int channel = 0);
		~SoundSystem();

		friend class Engine;
	protected:
		FMOD::System* BaseSystem;
		FMOD::Channel** Channels;
		void SetAudioDirectory(const std::string &directory);
		void SetSoundEffectsDirectory(const std::string &directory);
	private:
		int MaxChannels;
		int MaxActiveSounds;
		std::string PrimaryAudioDirectory;
		std::string PrimarySoundEffectsDirectory;
		boost::unordered_set<std::string> SoundIndexers;
		boost::unordered_map<std::string, FMOD::Sound*> SoundSet;
	};


}

#endif