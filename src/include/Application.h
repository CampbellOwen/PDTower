#pragma once

#include <memory>
#include <stdint.h>

#include "Assets.h"

extern "C" {
#include "pd_api.h"
}

namespace Playdate 
{

#define TEXT_WIDTH 86
#define TEXT_HEIGHT 16

class Application
{
public:
	Application(PlaydateAPI* pd) : m_pd(pd)
	{
	}
	int onEvent(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg) noexcept;
	int update(void* userdata) noexcept;

private:
	LCDFont* m_font { };
	int x { (400 - TEXT_WIDTH) / 2 };
	int y { (240 - TEXT_HEIGHT) / 2 };
	int dx { 1 };
	int dy { 2 };
	PlaydateAPI* m_pd { nullptr };
	LCDBitmap* m_road { nullptr };


	LCDBitmap* m_ghost { nullptr };

	std::unique_ptr<TD::Assets> m_assets {};
};

}