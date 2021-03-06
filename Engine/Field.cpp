#include "Field.h"

Field::Field()
{
	for (int y = 0;y < height;y++)
	{
		for (int x = 0;x < width;x++)
		{
			if (x == 0 || x == width - 1 || y == height - 1)
			{
				field[y * width + x] = Field::Type::Wall;
			}
			else
			{
				field[y * width + x] = Field::Type::None;
			}
		}
	}
}

void Field::Draw(Graphics& gfx, const Vei2& offset)
{
	for (int y = 0;y < height;y++)
	{
		for (int x = 0;x < width;x++)
		{
			if (field[y * width + x] == Field::Type::Wall)
			{
				gfx.DrawRect(RectI(offset + Vei2(x * tileSize, y * tileSize), tileSize, tileSize), pieceColor[int(field[y * width + x])]);
			}
			else if (int(field[y * width + x]) > int(Field::Type::Wall))
			{	
				gfx.DrawRect(RectI(offset + Vei2(x * tileSize, y * tileSize), tileSize, tileSize).GetExpanded(-1), pieceColor[int(field[y * width + x])]);
			}
		}
	}
}

void Field::Lock(int x, int y, Type type)
{
	field[y * width + x] = type;
}

bool Field::FullLine(int y)
{
	if (y < height - 1)
	{
		for (int x = 1;x < width - 1;x++)
		{
			if (field[y * width + x] == Field::Type::None)
				return false;
		}
		for (int x = 1;x < width - 1;x++)
		{
			field[y * width + x] = Field::Type::Full;
		}
		return true;
	}
	return false;
}

void Field::CopyAboveLine(int y)
{
	for (int x = 1;x < width - 1;x++)
	{
		field[y * width + x] = field[(y - 1) * width + x];
	}
}

void Field::ClearLine(int y)
{
	for (int x = 1;x < width - 1;x++)
	{
		field[y * width + x] = Field::Type::None;
	}
}

int Field::GetWidth() const
{
	return width;
}

int Field::GetHeight() const
{
	return height;
}

Field::Type Field::GetField(int i) const
{
	return field[i];
}
