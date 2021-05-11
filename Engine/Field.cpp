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
