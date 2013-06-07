#pragma once
#ifndef _SECTIONLOOPMUSIC_H_
#define _SECTIONLOOPMUSIC_H_
#include <fmod/fmod.hpp>

class SectionLoopableMusic : FMOD::Sound
{
public:
	void Update()
	{
	}
protected:
private:
	float LoopEnd;
	float LoopStart;
	bool LoopActive;
};

#endif