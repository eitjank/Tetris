#pragma once

#include "Field.h"

class Piece
{
public:

	enum class Direction
	{
		None,
		Up,
		Right,
		Down,
		Left
	};
	enum class Rotation
	{
		d0,
		d90,
		d180,
		d270
	};
public:
	Piece(Field::Type type, Vei2 pos);
	void Reset(Vei2 pos);
	void Move(Direction dir, const Field& field);
	void Draw(Graphics& gfx, const Vei2& offset);
	void Rotate(const Field& field);
	bool FitsDownwards(const Field& field)
	{
		return PieceFits(pos + Vei2(0, 1), field);
	}
	Vei2 GetPos()const;
	bool IsOccupied(int x, int y)const;
private:
	bool PieceFits(Vei2 newPos, const Field& field);
	int Rotate(int x, int y, Rotation rot);
	char piece[16];
	Vei2 pos;
	Rotation rot=Rotation::d0;
};