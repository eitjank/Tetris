#include "Piece.h"

Piece::Piece(Vei2 pos)
	:
	pos(pos)
{
	SetPiece();
}

void Piece::Reset(Vei2 pos)
{
	rot = Rotation::d0;
	this->pos = pos;
	SetPiece();
}

void Piece::Reset(Vei2 pos, const Field::Type type)
{
	rot = Rotation::d0;
	this->type = type;
	this->pos = pos;
	SetPiece(false);
}

bool Piece::Move(Direction dir, const Field& field)
{
	switch (dir)
	{
	case Piece::Direction::Right:
		if (PieceFits(pos + Vei2(1, 0), field))
		{
			pos.x++;
			return true;
		}
		break;
	case Piece::Direction::Down:
		if (PieceFits(pos + Vei2(0, 1), field))
		{
			pos.y++;
			return true;
		}
		break;
	case Piece::Direction::Left:
		if (PieceFits(pos + Vei2(-1, 0), field))
		{
			pos.x--;
			return true;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

void Piece::Draw(Graphics& gfx, const Vei2& offset)
{
	for (int y = 0;y < 4;y++)
	{
		for (int x = 0;x < 4;x++)
		{
			int pi = Rotate(x, y, rot);
			if(piece[pi]=='X')
				gfx.DrawRect(RectI(offset + Vei2((pos.x+x) * Field::tileSize, (pos.y + y) * Field::tileSize), Field::tileSize, Field::tileSize).GetExpanded(Field::padding), color);
		}
	}
}

void Piece::Rotate(const Field& field)
{
	if (rot == Rotation::d0)
	{
		rot = Rotation::d90;
		
		if (!PieceFits(pos, field))
		{
			if(PieceFits(pos+Vei2(-1,0),field))
			{
				pos += Vei2(-1, 0);
			}
			else if (PieceFits(pos + Vei2(1, 0), field))
			{
				pos += Vei2(1, 0);
			}
			else if (PieceFits(pos + Vei2(-2, 0), field))
			{
				pos += Vei2(-2, 0);
			}
			else if (PieceFits(pos + Vei2(2, 0), field))
			{
				pos += Vei2(2, 0);
			}
			else
			{
				rot = Rotation::d0;
			}
		}
	}
	else if (rot == Rotation::d90)
	{
		rot = Rotation::d180;
		if (!PieceFits(pos, field))
		{
			if (PieceFits(pos + Vei2(-1, 0), field))
			{
				pos += Vei2(-1, 0);
			}
			else if (PieceFits(pos + Vei2(1, 0), field))
			{
				pos += Vei2(1, 0);
			}
			else if (PieceFits(pos + Vei2(-2, 0), field))
			{
				pos += Vei2(-2, 0);
			}
			else if (PieceFits(pos + Vei2(2, 0), field))
			{
				pos += Vei2(2, 0);
			}
			else
			{
				rot = Rotation::d90;
			}
		}
	}
	else if (rot == Rotation::d180)
	{
		rot = Rotation::d270;
		if (!PieceFits(pos, field))
		{
			if (PieceFits(pos + Vei2(-1, 0), field))
			{
				pos += Vei2(-1, 0);
			}
			else if (PieceFits(pos + Vei2(1, 0), field))
			{
				pos += Vei2(1, 0);
			}
			else if (PieceFits(pos + Vei2(-2, 0), field))
			{
				pos += Vei2(-2, 0);
			}
			else if (PieceFits(pos + Vei2(2, 0), field))
			{
				pos += Vei2(2, 0);
			}
			else
			{
				rot = Rotation::d180;
			}
		}
	}
	else if (rot == Rotation::d270)
	{
		rot = Rotation::d0;
		if (!PieceFits(pos, field))
		{
			if (PieceFits(pos + Vei2(-1, 0), field))
			{
				pos += Vei2(-1, 0);
			}
			else if (PieceFits(pos + Vei2(1, 0), field))
			{
				pos += Vei2(1, 0);
			}
			else if (PieceFits(pos + Vei2(-2, 0), field))
			{
				pos += Vei2(-2, 0);
			}
			else if (PieceFits(pos + Vei2(2, 0), field))
			{
				pos += Vei2(2, 0);
			}
			else
			{
				rot = Rotation::d270;
			}
		}
	}
}

Vei2 Piece::GetPos() const
{
	return pos;
}

Field::Type Piece::GetType() const
{
	return type;
}

bool Piece::IsOccupied(int x, int y) const
{
	switch (rot)
	{
	case Rotation::d0:
		return piece[y * 4 + x] == 'X';
		break;
	case Rotation::d90:
		return piece[12 + y - 4 * x] == 'X';
		break;
	case Rotation::d180:
		return piece[15 - 4 * y - x] == 'X';
		break;
	case Rotation::d270:
		return piece[3 - y + 4 * x] == 'X';
		break;
	}
	return false;
}

bool Piece::PieceFits(Vei2 newPos, const Field& field)
{
	const int fieldWidth = field.GetWidth();
	const int fieldHeight = field.GetHeight();
	for (int y = 0;y < 4;y++)
	{
		for (int x = 0;x < 4;x++)
		{
			int pi = Rotate(x, y, rot);

			int fi = (newPos.y + y) * fieldWidth + newPos.x + x;

			if (newPos.x + x >= 0 && newPos.x + x < fieldWidth &&
				newPos.y + y >= 0 && newPos.y + y < fieldHeight)
			{
				if (piece[pi] == 'X' && field.GetField(fi) != Field::Type::None)
				{
					return false;
				}
			}
			
		}
	}
	return true;
}

void Piece::SetPiece(bool random)
{
	if (random)
	{
		type = Field::Type(rand() % 7 + 2);
	}
	switch (type)
	{
	case Field::Type::I:
		 piece[0] = ' ';  piece[1] = ' ';  piece[2] = 'X';  piece[3] = ' ';
		 piece[4] = ' ';  piece[5] = ' ';  piece[6] = 'X';  piece[7] = ' ';
		 piece[8] = ' ';  piece[9] = ' '; piece[10] = 'X'; piece[11] = ' ';
		piece[12] = ' '; piece[13] = ' '; piece[14] = 'X'; piece[15] = ' ';
		color = Colors::Cyan;
		break;
	case Field::Type::J:
		 piece[0] = ' ';  piece[1] = ' ';  piece[2] = 'X';  piece[3] = ' ';
		 piece[4] = ' ';  piece[5] = ' ';  piece[6] = 'X';  piece[7] = ' ';
		 piece[8] = ' ';  piece[9] = 'X'; piece[10] = 'X'; piece[11] = ' ';
		piece[12] = ' '; piece[13] = ' '; piece[14] = ' '; piece[15] = ' ';
		color = Colors::Blue;
		break;
	case Field::Type::L:
		 piece[0] = ' ';  piece[1] = ' ';  piece[2] = 'X';  piece[3] = ' ';
		 piece[4] = ' ';  piece[5] = ' ';  piece[6] = 'X';  piece[7] = ' ';
		 piece[8] = ' ';  piece[9] = ' '; piece[10] = 'X'; piece[11] = 'X';
		piece[12] = ' '; piece[13] = ' '; piece[14] = ' '; piece[15] = ' ';
		color = { 255,165,0 };
		break;
	case Field::Type::O:
		 piece[0] = ' ';  piece[1] = ' ';  piece[2] = ' ';  piece[3] = ' ';
		 piece[4] = ' ';  piece[5] = 'X';  piece[6] = 'X';  piece[7] = ' ';
		 piece[8] = ' ';  piece[9] = 'X'; piece[10] = 'X'; piece[11] = ' ';
		piece[12] = ' '; piece[13] = ' '; piece[14] = ' '; piece[15] = ' ';
		color = Colors::Yellow;
		break;
	case Field::Type::S:
		 piece[0] = ' ';  piece[1] = 'X';  piece[2] = ' ';  piece[3] = ' ';
		 piece[4] = ' ';  piece[5] = 'X';  piece[6] = 'X';  piece[7] = ' ';
		 piece[8] = ' ';  piece[9] = ' '; piece[10] = 'X'; piece[11] = ' ';
		piece[12] = ' '; piece[13] = ' '; piece[14] = ' '; piece[15] = ' ';
		color = { 63,255,0 };
		break;
	case Field::Type::T:
		 piece[0] = ' ';  piece[1] = ' ';  piece[2] = 'X';  piece[3] = ' ';
		 piece[4] = ' ';  piece[5] = 'X';  piece[6] = 'X';  piece[7] = ' ';
		 piece[8] = ' ';  piece[9] = ' '; piece[10] = 'X'; piece[11] = ' ';
		piece[12] = ' '; piece[13] = ' '; piece[14] = ' '; piece[15] = ' ';
		color = { 204,0,204 };
		break;
	case Field::Type::Z:
		 piece[0] = ' ';  piece[1] = ' ';  piece[2] = 'X';  piece[3] = ' ';
		 piece[4] = ' ';  piece[5] = 'X';  piece[6] = 'X';  piece[7] = ' ';
		 piece[8] = ' ';  piece[9] = 'X'; piece[10] = ' '; piece[11] = ' ';
		piece[12] = ' '; piece[13] = ' '; piece[14] = ' '; piece[15] = ' ';
		color = Colors::Red;
		break;
	default:
		break;
	}
}

int Piece::Rotate(int x, int y, Rotation rot)
{
	switch (rot)
	{
	case Rotation::d0:
		return y * 4 + x;
		break;
	case Rotation::d90:
		return 12 + y - 4 * x;
		break;
	case Rotation::d180:
		return 15 - 4 * y - x;
		break;
	case Rotation::d270:
		return 3 - y + 4 * x;
		break;
	}
	return 0;
}
