#ifndef SUDOKU_SCENE_HPP
#define SUDOKU_SCENE_HPP

#include "Sudoku.hpp"

#include <LK/Scene.hpp>
using namespace lk;

class SudokuScene : public Scene
{
public:
	SudokuScene(Sudoku::Level difficultyLevel);
	void onCreate() override;
	void onClose(int scene) override;

private:
	Sudoku::Level difficultyLevel;
};

#endif // SUDOKU_SCENE_HPP
