#include "ScalableClock.h"

ScalableClock::ScalableClock(const float scale, sf::Uint32 resolution) 
	: TimeScaler(scale), TimeBuffer(0), Scaled(!(scale >= 0.99 && scale <= 1.01)), UpdaterThread(boost::bind(&ScalableClock::UpdateFunction, this)), Resolution(sf::milliseconds(resolution))
{

}
void ScalableClock::SetScale(const float scale)
{
	Scaled = scale >= 0.99f && scale <= 1.01f;
	TimeScaler = scale;
}
sf::Uint32 ScalableClock::GetElapsedGameTime()
{
	if (Scaled)
	{
		LockUpdater.lock();
		sf::Uint32 time = GameClock.getElapsedTime().asMilliseconds();
		sf::Uint32 Elapsed =  time - LastUpdate;
		TimeBuffer += static_cast<sf::Uint32>(static_cast<float>(Elapsed) * (TimeScaler - 1.0f));
		LastUpdate = time;
		LockUpdater.unlock();
		
	}
	//else
	{
		if (TimeBuffer != 0)
			return GameClock.getElapsedTime().asMilliseconds() + static_cast<sf::Uint32>(TimeBuffer);
		return GameClock.getElapsedTime().asMilliseconds();
	}
}
sf::Uint32 ScalableClock::GetElapsedRealTime() const
{
	return GameClock.getElapsedTime().asMilliseconds();
}
void ScalableClock::Reset()
{
	LockUpdater.lock();
	TimeBuffer = 0;
	Scaled = false;
	TimeScaler = 1.0f;
	LockUpdater.unlock();
}
bool ScalableClock::IsScaled()
{
	return Scaled;
}
void ScalableClock::UpdateFunction()
{
	//I forget what goes here
	sf::sleep(Resolution);
}
ScalableClock::~ScalableClock()
{
	UpdaterThread.terminate();
	//UpdaterThread.Terminate();
}