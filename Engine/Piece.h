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
	Piece(Vei2 pos);
	void Reset(Vei2 pos);
	void Reset(Vei2 pos, const Field::Type type);
	bool Move(Direction dir, const Field& field);
	void Draw(Graphics& gfx, const Vei2& offset);
	void Rotate(const Field& field);
	bool FitsDownwards(const Field& field)
	{
		return PieceFits(pos + Vei2(0, 1), field);
	}
	Vei2 GetPos()const;
	Field::Type GetType()const;
	bool IsOccupied(int x, int y)const;
private:
	bool PieceFits(Vei2 newPos, const Field& field);
	void SetPiece(bool random = true);
	int Rotate(int x, int y, Rotation rot);
	char piece[16];
	Vei2 pos;
	Color color;
	Field::Type type;
	Rotation rot=Rotation::d0;
};