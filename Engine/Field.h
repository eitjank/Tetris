#pragma once

#include "Graphics.h"

class Field
{
public:
	enum class Type
	{
		None,
		Wall,
		I,
		J,
		L,
		O,
		S,
		T,
		Z
	};
public:
	Field();
	void Draw(Graphics& gfx, const Vei2& pos);
	int GetWidth()const;
	int GetHeight()const;
	Type GetField(int i)const;
	static constexpr int tileSize = 28;
private:
	static constexpr int width = 12;
	static constexpr int height = 18;
	static constexpr Color wallColor = Colors::LightGray;
	Type field[width * height];
};