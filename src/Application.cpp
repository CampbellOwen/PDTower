#include "Application.h"

extern "C"
{
#include "pd_api.h"
}


static constexpr char* fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";

int Playdate::Application::onEvent(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg) noexcept
{
	if (event == kEventInit)
	{
		const char* err;
		m_font = pd->graphics->loadFont(fontpath, &err);

		if (m_font == nullptr)
			pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);

		m_road = pd->graphics->loadBitmap("road", &err);
		if (m_road == nullptr)
		{
			pd->system->error("%s:%i Couldn't load bitmap road: %s", __FILE__, __LINE__, err);
		}

		m_ghost = pd->graphics->loadBitmap("ghost", &err);
		if (m_ghost == nullptr)
		{
			pd->system->error("%s:%i Couldn't load bitmap road: %s", __FILE__, __LINE__, err);
		}

		m_assets = std::make_unique<TD::Assets>(pd);
		m_assets->Load();
	}

	return 0;
}


int Playdate::Application::update(void* userdata) noexcept
{

	m_pd->graphics->clear(kColorWhite);
	m_pd->graphics->setFont(m_font);
	//m_pd->graphics->drawText("Hello World!", strlen("Hello World!"), kASCIIEncoding, x, y);

	//float crank_angle = m_pd->system->getCrankAngle();
	//m_pd->graphics->drawRotatedBitmap(m_road, 64, 64, crank_angle, 0.5, 0.5, 2.0, 2.0);
	//m_pd->graphics->drawBitmap(m_road, 10, 10, kBitmapUnflipped);
	//m_pd->graphics->drawScaledBitmap(m_road, 64, 96, 2.0, 2.0);
	//m_pd->graphics->drawScaledBitmap(m_road, 64, 128, 2.0, 2.0);
	//m_pd->graphics->drawScaledBitmap(m_road, 64, 160, 2.0, 2.0);
	//m_pd->graphics->drawScaledBitmap(m_road, 64, 192, 2.0, 2.0);

	//m_pd->graphics->drawBitmap(m_ghost, 72, 96, kBitmapUnflipped);


	m_assets->DrawBitmap(TD::Sprites::ROAD_TOP_DOWN, 32, 0);
	m_assets->DrawBitmap(TD::Sprites::ROAD_TOP_DOWN, 32, 32);
	m_assets->DrawBitmap(TD::Sprites::ROAD_TOP_DOWN, 32, 64);
	m_assets->DrawBitmap(TD::Sprites::ROAD_TOP_DOWN, 32, 96);
	m_assets->DrawBitmap(TD::Sprites::ROAD_TOP_DOWN, 32, 128);
	m_assets->DrawBitmap(TD::Sprites::ROAD_TOP_DOWN, 32, 160);
	m_assets->DrawBitmap(TD::Sprites::ROAD_TOP_RIGHT, 32, 192);

	m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 0);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 32);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 64);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 96);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 128);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 160);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 192);

	m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 0);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 32);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 64);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 96);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 128);
	m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 160);

	m_assets->DrawBitmap(TD::Sprites::GHOST, 32, 96);
	m_assets->DrawBitmap(TD::Sprites::GHOST, 48, 96);
	m_assets->DrawBitmap(TD::Sprites::GHOST, 40, 112);

	m_pd->graphics->drawBitmap(m_ghost, x, y, kBitmapUnflipped);
	m_pd->graphics->drawScaledBitmap(m_ghost, y, x, 2.0, 2.0);

	x += dx;
	y += dy;

	if (x < 0 || x > LCD_COLUMNS - TEXT_WIDTH)
		dx = -dx;

	if (y < 0 || y > LCD_ROWS - TEXT_HEIGHT)
		dy = -dy;

	m_pd->system->drawFPS(0, 0);

	return 1;
}
