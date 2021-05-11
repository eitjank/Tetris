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
				gfx.DrawRect(RectI(offset + Vei2(x * tileSize, y * tileSize), tileSize, tileSize), wallColor);
			}
			else if (field[y * width + x] == Field::Type::Full)
			{
				gfx.DrawRect(RectI(offset + Vei2(x * tileSize, y * tileSize), tileSize, tileSize), Colors::White);
			}
			else if (field[y * width + x] != Field::Type::None)
			{
				gfx.DrawRect(RectI(offset + Vei2(x * tileSize, y * tileSize), tileSize, tileSize), Colors::Red);
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
