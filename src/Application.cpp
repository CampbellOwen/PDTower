#include "Application.h"

extern "C"
{
#include "pd_api.h"
}

static constexpr char* fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";

int Playdate::Application::onEvent(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg) noexcept
{
  if (event == kEventInit) {
    const char* err;
    m_font = pd->graphics->loadFont(fontpath, &err);

    if (m_font == nullptr)
      pd->system->error(
        "%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);

    m_assets = std::make_unique<TD::Assets>(pd);
    m_assets->Load();
  }

  return 0;
}

int Playdate::Application::update(void* userdata) noexcept
{
  m_pd->graphics->clear(kColorWhite);
  m_pd->graphics->setFont(m_font);

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
  m_assets->DrawBitmap(TD::Sprites::GRASS, 0, 224);

  m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 0);
  m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 32);
  m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 64);
  m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 96);
  m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 128);
  m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 160);
  m_assets->DrawBitmap(TD::Sprites::GRASS, 64, 224);

  m_assets->DrawBitmap(TD::Sprites::GHOST, 32, m_ghostOffset);
  m_assets->DrawBitmap(TD::Sprites::GHOST, 48, m_ghostOffset);
  m_assets->DrawBitmap(TD::Sprites::GHOST, 40, m_ghostOffset + 16);

  m_ghostOffset += m_ghostDy;
  if (m_ghostOffset + 32 >= 240 || m_ghostOffset == 0)
  {
     m_ghostDy *= -1;
  }


  m_pd->system->drawFPS(0, 0);

  return 1;
}
