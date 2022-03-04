#pragma once

#include <memory>
#include <stdint.h>

#include "Assets.h"

extern "C" {
#include "pd_api.h"
}

namespace Playdate 
{

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
	PlaydateAPI* m_pd { nullptr };

	std::unique_ptr<TD::Assets> m_assets {};

	uint32_t m_ghostOffset { 0 };
	int m_ghostDy { 1 };
};

}