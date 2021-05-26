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
	piece(pieceStartingPosition),
	nextPiece(Vei2(0, 0)),
	holdPiece(Vei2(0, 0))
{
	srand(int(time(0)));
	piece.Reset(pieceStartingPosition);
	next = Field::Type(rand() % 7 + 2);
	nextPiece.Reset(Vei2(0, 0), next);
	holdPiece.Reset(Vei2(0, 0), Field::Type::None);
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
	if (!gameOver)
	{
		const float dt = ft.Mark();
		pieceFallCounter += dt;

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
				if (e.GetCode() == VK_RETURN && !usedHold)
				{
					if (holdPiece.GetType() == Field::Type::None)
					{
						holdPiece.Reset(Vei2(0, 0), piece.GetType());
						piece.Reset(pieceStartingPosition, next);
						next = Field::Type(rand() % 7 + 2);
						nextPiece.Reset(Vei2(0, 0), next);
						nFaster = nFasterConst;
					}
					else
					{
						Piece temp = piece;
						piece.Reset(pieceStartingPosition, holdPiece.GetType());
						holdPiece.Reset(Vei2(0, 0), temp.GetType());
						nFaster = nFasterConst;
					}
					usedHold = true;
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

		if (oldDir == dir)
		{
			if (PieceMoveCounter > 0)
			{
				PieceMoveCounter -= dt * nFaster;
				nFaster += nFasterAdd;
			}
			else
			{
				if (piece.Move(dir, gameField) && dir == Piece::Direction::Down)
				{
					pieceFallCounter = 0.0f;
					score += fallingScoreMultiplier;
				}
				PieceMoveCounter = PieceMovePeriod;
			}
		}
		else
		{
			if (piece.Move(dir, gameField) && dir==Piece::Direction::Down)
			{
				pieceFallCounter = 0.0f;
			}
			PieceMoveCounter = PieceMovePeriod;
			nFaster = nFasterConst;
		}
		oldDir = dir;


		if (pieceFallCounter >= pieceFallPeriod)
		{
			pieceFallCounter -= pieceFallPeriod;
			if (piece.FitsDownwards(gameField))
			{
				piece.Move(Piece::Direction::Down, gameField);
			}
			else
			{
				//Lock the piece in the field
				Vei2 pPos = piece.GetPos();
				for (int y = 0;y < 4;y++)
				{
					for (int x = 0;x < 4;x++)
					{
						if (piece.IsOccupied(x, y))
						{
							gameField.Lock(pPos.x + x, pPos.y + y, piece.GetType());
						}
					}
				}
				//Check for horizontal lines
				for (int y = 0;y < 4;y++)
				{
					if (gameField.FullLine(pPos.y + y))
					{
						fullLineRow.push_back(pPos.y + y);
						lineTime = lineDisapperTime;
					}
				}
				//Choose next piece
				piece.Reset(pieceStartingPosition, next);
				next = Field::Type(rand() % 7 + 2);
				nextPiece.Reset(Vei2(0, 0), next);
				nFaster = nFasterConst;
				usedHold = false;
				//Piece does not fit
				gameOver = !piece.FitsDownwards(gameField);
			}
		}

		if (lineTime > 0)
		{
			lineTime -= dt;
			if (lineTime <= 0)
			{
				pieceFallPeriod = std::max(pieceFallPeriod - fullLineRow.size() * pieceFallingAceleration, minPieceFallPeriod);
				if (fullLineRow.size() > 1)
				{
					score += int( pow( lineScoreMultiplier, int( fullLineRow.size() ) ) ) * lineScore;
				}
				else
				{
					score += lineScore;
				}
				for (auto& ry : fullLineRow)
				{
					for (int y = ry;y > 0;y--)
					{
						gameField.CopyAboveLine(y);
					}
				}
				gameField.ClearLine(0);
				fullLineRow.clear();
			}
		}

	}
}

void Game::ComposeFrame()
{
	gameField.Draw(gfx, drawPos);
	piece.Draw(gfx, drawPos);

	font.DrawText("Next:", Vei2(580, 10), gfx);
	nextPiece.Draw(gfx, Vei2(566, 39));

	font.DrawText("Hold:", Vei2(130, 10), gfx);
	holdPiece.Draw(gfx, Vei2(115, 39));

	font.DrawText("Score:" + std::to_string(score),Vei2(580, 155) , gfx);
	if (gameOver)
	{
		font.DrawText("Game over!", Vei2(345, 515), gfx, Colors::White);
	}
}
