#pragma once

#include "Surface.h"
#include "Graphics.h"
#include "Vei2.h"

class Font
{
public:
	Font(const std::string& filename, Color chroma = Colors::White);
	void DrawText(const std::string& text, const Vei2& pos, Graphics& gfx, Color color = Colors::White)const;
private:
	RectI GetCharRect(char c)const;
private:
	Surface surface;
	int charWidth;
	int charHeight;
	static constexpr int nChars = int('~' - ' ') + 1;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
	Color chroma;

};