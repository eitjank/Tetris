/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Vei2.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	piece(Field::Type::J, Vei2(4,0))
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	PieceMoveCounter += dt;
	PieceFallCounter += dt;

	Piece::Direction dir = Piece::Direction::None;
	
	while (!wnd.kbd.KeyIsEmpty())
	{
		// get an event from the queue
		const Keyboard::Event e = wnd.kbd.ReadKey();
		// check if it is a press event
		if (e.IsPress())
		{
			if (e.GetCode() == VK_UP)
			{
				piece.Rotate(gameField);
			}
		}
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir = Piece::Direction::Down;
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir = Piece::Direction::Left;
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir = Piece::Direction::Right;
	}

	if (PieceMoveCounter >= PieceMovePeriod)
	{
		PieceMoveCounter -= PieceMovePeriod;

		piece.Move(dir,gameField);
	}

	if (PieceFallCounter >= PieceFallPeriod)
	{
		PieceFallCounter -= PieceFallPeriod;
		if (piece.FitsDownwards(gameField))
		{
			piece.Move(Piece::Direction::Down, gameField);
		}
		else
		{
			//Lock the piece in the field

			//Check for horizontal lines
		}

	}

}

void Game::ComposeFrame()
{
	//gfx.DrawRect(RectI(Vei2(50, 50), 50, 50), Colors::Green);
	gameField.Draw(gfx, Vei2(100,25));
	piece.Draw(gfx, Vei2(100, 25));
}
