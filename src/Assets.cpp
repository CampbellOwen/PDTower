#include "Assets.h"

extern "C" 
{
#include "pd_api.h"
}

namespace TD 
{

void Assets::Load() noexcept
{
	const char* err { nullptr };
	for (uint8_t i = 0; i < static_cast<uint8_t>(Sprites::NUM_SPRITES); ++i)
	{
		bitmaps[i] = m_pd->graphics->loadBitmap(paths[i], &err);
		if (bitmaps[i] == nullptr)
		{
			m_pd->system->error("%s:%i Couldn't load bitmap %s: %s", __FILE__, __LINE__, paths[i], err);
		}
	}
}

void Assets::DrawBitmap(Sprites sprite, int x, int y) noexcept
{
	m_pd->graphics->drawBitmap(bitmaps[static_cast<uint8_t>(sprite)], x, y, kBitmapUnflipped);
}

} // namespace TD