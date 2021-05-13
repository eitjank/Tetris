#pragma once

#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(Color c)
			:
			chroma(c)
		{}
		void operator()(Color srcC, int xDest, int yDest, Graphics& gfx)const
		{
			if (srcC != chroma)
			{
				gfx.PutPixel(xDest, yDest, srcC);
			}
		}
	private:
		Color chroma;
	};
	class Substitution
	{
	public:
		Substitution(Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}
		void operator()(Color srcC, int xDest, int yDest, Graphics& gfx)const
		{
			if (srcC != chroma)
			{
				gfx.PutPixel(xDest, yDest, sub);
			}
		}
	private:
		Color chroma;
		Color sub;
	};
	class Copy
	{
	public:
		void operator()(Color srcC, int xDest, int yDest, Graphics& gfx)const
		{
			gfx.PutPixel(xDest, yDest, srcC);
		}
	};
	class Ghost
	{
	public:
		Ghost(Color c)
			:
			chroma(c)
		{}
		void operator()(Color srcC, int xDest, int yDest, Graphics& gfx)const
		{ 
			if (srcC != chroma)
			{

				const Color dstPixel = gfx.GetPixel(xDest, yDest);
				const Color blended =
				{
					unsigned char((srcC.GetR() + dstPixel.GetR()) / 2),
					unsigned char((srcC.GetG() + dstPixel.GetG()) / 2),
					unsigned char((srcC.GetB() + dstPixel.GetB()) / 2)
				};
				gfx.PutPixel(xDest, yDest, blended);
			}
		}
	private:
		Color chroma;
	};
};