#pragma once
#ifndef _INPUTDEVICE_H_
#define _INPUTDEVICE_H_

namespace Input
{
	const int NUM_JOYSTICKS = 32;
	const int NUM_PUMPS = 2;

	enum InputDevice
	{
		DEVICE_KEYBOARD = 0,
		DEVICE_JOY1,
		DEVICE_JOY2,
		DEVICE_JOY3,
		DEVICE_JOY4,
		DEVICE_JOY5,
		DEVICE_JOY6,
		DEVICE_JOY7,
		DEVICE_JOY8,
		DEVICE_JOY9,
		DEVICE_JOY10,
		DEVICE_JOY11,
		DEVICE_JOY12,
		DEVICE_JOY13,
		DEVICE_JOY14,
		DEVICE_JOY15,
		DEVICE_JOY16,
		DEVICE_JOY17,
		DEVICE_JOY18,
		DEVICE_JOY19,
		DEVICE_JOY20,
		DEVICE_JOY21,
		DEVICE_JOY22,
		DEVICE_JOY23,
		DEVICE_JOY24,
		DEVICE_JOY25,
		DEVICE_JOY26,
		DEVICE_JOY27,
		DEVICE_JOY28,
		DEVICE_JOY29,
		DEVICE_JOY30,
		DEVICE_JOY31,
		DEVICE_JOY32,
		DEVICE_PUMP1,
		DEVICE_PUMP2,
		DEVICE_MIDI,
		DEVICE_MOUSE,
		NUM_InputDevice,		// leave this at the end
		InputDevice_Invalid		// means this is NULL
	};


}

#endif

/*
 * Copyright (c) 2001-2002 Chris Danford
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */