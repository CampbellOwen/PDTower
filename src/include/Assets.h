#pragma once

#include <array>
#include <stdint.h>

struct PlaydateAPI;
struct LCDBitmap;

namespace TD 
{

enum class Sprites : uint8_t
{
	ROAD_TOP_DOWN,
	ROAD_TOP_RIGHT,
	GRASS,
	GHOST,
	NUM_SPRITES
};

static constexpr std::array paths {
	"road",
	"road_top_right",
	"grass",
	"ghost"
};

static std::array<LCDBitmap*, static_cast<uint8_t>(Sprites::NUM_SPRITES)> bitmaps;

class Assets
{
public:
	Assets(PlaydateAPI* pd) noexcept : m_pd(pd) {} 
	void Load() noexcept;

	void DrawBitmap(Sprites sprite, int x, int y) noexcept;
private:
	PlaydateAPI* m_pd;
};

} // namespace TD