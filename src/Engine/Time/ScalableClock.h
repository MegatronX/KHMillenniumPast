#include <sfml/System/Clock.hpp>
#include <Time/StopWatch.hpp>
#include <boost/thread.hpp>
#include <sfml/System.hpp>
//Only supports positive scales
class ScalableClock
{
public:
	ScalableClock(const float scale = 1.0f, sf::Uint32 resolution = 15);
	void SetScale(const float scale);
	sf::Uint32 GetElapsedGameTime();
	sf::Uint32 GetElapsedRealTime() const;
	void Reset();
	bool IsScaled();
	virtual ~ScalableClock();
private:
	void UpdateFunction();
	float TimeBuffer;
	sf::Uint32 LastUpdate;
	sf::Time Resolution;
	sf::Clock GameClock;
	bool Scaled;
	float TimeScaler;
	//boost::thread UpdaterThread;
	sf::Thread UpdaterThread;
	sf::Mutex LockUpdater;
};

class ScalableClock_
{
public:
	void SetTimeScale(const float scale);
	const sf::Clock& GetPrimaryClock();
	const sf::Clock& GetSecondaryClock();
protected:
	float TimeScale;
	sf::Clock PrimaryClock;
	sf::Clock SecondaryClock;
};