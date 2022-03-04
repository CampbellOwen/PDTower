//
//  main.c
//  Extension
//
//  Created by Dave Hayden on 7/30/14.
//  Copyright (c) 2014 Panic, Inc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include <memory>

#include "Application.h"

static std::unique_ptr<Playdate::Application> s_application;
static PlaydateAPI* _pd;
void *operator new(size_t s) {
	void* const p = _pd->system->realloc(nullptr, s);
	return p;
}

void operator delete(void *p) noexcept {
	_pd->system->realloc(p, 0);
}

extern "C"
{
	static int update(void* userdata);
	const char* fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
	LCDFont* font = NULL;

#ifdef _WINDLL
	__declspec(dllexport)
#endif
	int eventHandler(PlaydateAPI * pd, PDSystemEvent event, uint32_t arg)
	{
		if (event == kEventInit)
		{
			_pd = pd;

			s_application = std::make_unique<Playdate::Application>(pd);

			pd->system->setUpdateCallback(update, pd);
		}

		return s_application->onEvent(pd, event, arg);
	}

	static int update(void* userdata)
	{
		return s_application->update(userdata);
	}
}
