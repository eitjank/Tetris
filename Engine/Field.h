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
		Z,
		Full
	};
public:
	Field();
	void Draw(Graphics& gfx, const Vei2& pos);
	void Lock(int x, int y, Type type);
	bool FullLine(int y);
	void CopyAboveLine(int y);
	void ClearLine(int y);
	int GetWidth()const;
	int GetHeight()const;
	Type GetField(int i)const;
	static constexpr int tileSize = 22;
	static constexpr int padding = -1;
	static constexpr Color pieceColor[]{
		Colors::Black,   //None,
		Colors::Gray,    //Wall,
		{ 0,230,230 },   //I,
		{ 0,0,220 },     //J,
		{ 255,165,0 },   //L,
		{ 230,230,0},    //O,
		{ 63,215,0 },    //S,
		{ 204,0,204 },   //T,
		{ 220,0,0},      //Z,
		Colors::White,   //Full
	};
private:
	static constexpr int width = 12;
	static constexpr int height = 23;
	Type field[width * height];
};