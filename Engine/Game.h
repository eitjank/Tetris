/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Field.h"
#include "Piece.h"
#include "FrameTimer.h"
#include <vector>
#include "Font.h"
#include <string>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Vei2 pieceStartingPosition = Vei2(4, 0);
	Field gameField;
	Piece piece;
	FrameTimer ft;
	Font font = Font("ConsolasFontPt6.bmp");
	static constexpr float PieceMovePeriod = 0.5f;
	float PieceMoveCounter = 0.0f;
	static constexpr float initialPieceFallPeriod = 1.0f;
	static constexpr float minPieceFallPeriod = 0.4f;
	static constexpr float pieceFallingAceleration= 0.05f;//per line cleared
	float pieceFallPeriod = initialPieceFallPeriod;
	float pieceFallCounter = 0.0f;
	static constexpr float lineDisapperTime = 0.4f;
	float lineTime = 0.0f;
	bool gameOver = false;
	std::vector<int> fullLineRow;
	Piece::Direction oldDir=Piece::Direction::None;
	static constexpr float nFasterAdd = 2.0f;
	static constexpr float nFasterConst = 1.00f;
	float nFaster = nFasterConst;
	static constexpr int lineScoreMultiplier = 2;
	static constexpr int lineScore = 100;
	static constexpr int fallingScoreMultiplier = 1;
	int score = 0;
	/********************************/
};