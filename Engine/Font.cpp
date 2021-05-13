#include "Font.h"
#include <cassert>
#include "SpriteEffect.h"

Font::Font(const std::string& filename, Color chroma)
	:
	surface(filename),
	chroma(chroma),
	charWidth (surface.GetWidth() / nChars),
	charHeight (surface.GetHeight())
{
	assert(charWidth * nChars == surface.GetWidth());
}

void Font::DrawText(const std::string& text, const Vei2& pos, Graphics& gfx, Color color) const
{
	SpriteEffect::Substitution e{ chroma, color };
	Vei2 curPos = pos;
	for (auto c : text)
	{
		if (c == '\n')
		{
			curPos.x = pos.x;
			curPos.y += charHeight;
			continue;
		}
		else if (c >= ' ' && c <= '~')
		{
			gfx.DrawSprite(curPos.x, curPos.y, GetCharRect(c), surface, e);
		}
		curPos.x += charWidth;
	}
}

RectI Font::GetCharRect(char c) const
{
	assert(c >= ' ' && c <= '~');
	const int charIndex = c - ' ';
	return RectI({ charIndex * charWidth,0 },charWidth,charHeight);
}
