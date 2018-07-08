#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP

#include "Sudoku.hpp"

#include <SFML/Window/Event.hpp>
#include <LK/TileMap.hpp>
using namespace lk;

class SudokuBoard : public TileMap
{
public:
	enum Tiles
	{
		Cursor = 9,
		InvalidNumber = 10,
		Clue = 11
	};

	SudokuBoard(Sudoku::Level level);
	~SudokuBoard();
	void onKeyPressed(const sf::Event &event);
	void toggleRunning();

private:
	bool running;
	Point cursorPosition;

	Sudoku *sudoku;
	TileLayer *contentLayer;
	TileLayer *cursorLayer;
	TileLayer *invalidLayer;
	TileLayer *cluesLayer;
};

#endif // SUDOKU_BOARD_HPP
