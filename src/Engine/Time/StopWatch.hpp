/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

/// @file
/// @brief Class thor::StopWatch

#ifndef THOR_STOPWATCH_HPP
#define THOR_STOPWATCH_HPP

//#include <Thor/Config.hpp>

#include <SFML/System/Clock.hpp>


//namespace thor
//{

/// @addtogroup Time
/// @{

/// @brief Pausable clock class that measures elapsed time.
/// @details Unlike sf::Clock, this clock can be paused and continued at any time.
class StopWatch
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Constructor: Sets up a new StopWatch with time zero.
		/// @param initiallyRunning Specifies whether the stopwatch immediately starts.
		explicit					StopWatch(bool initiallyRunning = false);
							
		/// @brief Returns the totally elapsed time, in milliseconds.
		///
		sf::Uint32					GetElapsedTime() const;
		
		void						SetElapsedTime(const sf::Uint32 time);
		/// @brief Checks if the stopwatch is currently running.
		///
		bool						IsRunning() const;
		
		/// @brief Starts or continues the stopwatch.
		/// @details If it is already running, nothing happens.
		void						Start();
		
		/// @brief Pauses the stopwatch.
		/// @details If it is already paused, nothing happens.
		void						Stop();
				
		/// @brief Resets the stopwatch's time to zero. 
		/// @param continueRunning Declares if the stopwatch is running further or waiting
		///  for the next Start() call.
		void						Reset(bool continueRunning = false);
		

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		sf::Clock					mClock;
		sf::Uint32					mTimeBuffer;
		bool						mRunning;
};

/// @}

//} // namespace thor

#endif // THOR_STOPWATCH_HPP
