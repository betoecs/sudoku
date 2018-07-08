#include "SudokuBoard.hpp"
#include <LK/Director.hpp>
#include <LK/Scene.hpp>

///////////////////////////////////////////
SudokuBoard::SudokuBoard(Sudoku::Level level) : TileMap(Point(9, 9), Point(64, 64)), running(true)
{
	addTileset("board-tileset.png", "board");
	addTileset("content-tileset.png", "content");

	invalidLayer = addLayer("board");
	cluesLayer = addLayer("board");

	cursorLayer = addLayer("board");
	cursorLayer->set(0, 0, Cursor);

	auto boardLayer = addLayer("board");
	for (int row = 0; row < 9; row++)
	{
		int tilesetRow = row % 3;
		for (int column = 0; column < 9; column++)
		{
			int tilesetColumn = column % 3;
			boardLayer->set(column, row, tilesetRow * 3 + tilesetColumn);
		}
	}

	contentLayer = addLayer("content");
	sudoku = new Sudoku(level);
	for (int row = 0; row < 9; row++)
		for (int column = 0; column < 9; column++)
			contentLayer->set(column, row, sudoku->get(column, row) - 1);

	for (auto cluePosition : sudoku->getCluePositions())
		cluesLayer->set(cluePosition, Clue);
}

///////////////////////////////////////////
SudokuBoard::~SudokuBoard()
{
	delete sudoku;
}

///////////////////////////////////////////
void SudokuBoard::onKeyPressed(const sf::Event &event)
{
	if (! running)
		return;

	cursorLayer->set(cursorPosition, -1);

	switch (event.key.code)
	{
		case sf::Keyboard::Up:
			cursorPosition.y--;
			if (cursorPosition.y < 0)
				cursorPosition.y = 8;
		break;

		case sf::Keyboard::Down:
			cursorPosition.y++;
			if (cursorPosition.y > 8)
				cursorPosition.y = 0;
		break;

		case sf::Keyboard::Right:
			cursorPosition.x++;
			if (cursorPosition.x > 8)
				cursorPosition.x = 0;
		break;

		case sf::Keyboard::Left:
			cursorPosition.x--;
			if (cursorPosition.x < 0)
				cursorPosition.x = 8;
		break;

		case sf::Keyboard::Num1: case sf::Keyboard::Num2: case sf::Keyboard::Num3: case sf::Keyboard::Num4: case sf::Keyboard::Num5:
		case sf::Keyboard::Num6: case sf::Keyboard::Num7: case sf::Keyboard::Num8: case sf::Keyboard::Num9:
			if (sudoku->set(cursorPosition.x, cursorPosition.y, event.key.code - sf::Keyboard::Num0))
			{
				std::vector <int> invalidPositions;
				contentLayer->set(cursorPosition, event.key.code - sf::Keyboard::Num0 - 1);

				sudoku->getInvalidPositions(invalidPositions);
				invalidLayer->reset();
				for (auto invalidPosition : invalidPositions)
					invalidLayer->set(invalidPosition, InvalidNumber);

				if (sudoku->isSolved())
					Director::getScene()->close(0);
			}
		break;

		case sf::Keyboard::Num0: case sf::Keyboard::BackSpace:
			if (sudoku->set(cursorPosition.x, cursorPosition.y, 0))
			{
				std::vector <int> invalidPositions;
				contentLayer->set(cursorPosition, -1);

				sudoku->getInvalidPositions(invalidPositions);
				invalidLayer->reset();
				for (auto invalidPosition : invalidPositions)
					invalidLayer->set(invalidPosition, InvalidNumber);
			}
	}

	cursorLayer->set(cursorPosition, Cursor);
}

///////////////////////////////////////////
void SudokuBoard::toggleRunning()
{
	running = ! running;
}
