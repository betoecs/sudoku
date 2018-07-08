#include "SudokuScene.hpp"
#include "SudokuBoard.hpp"
#include "Timer.hpp"
#include <LK/Button.hpp>

extern Vector2D windowSize;

///////////////////////////////////////////
SudokuScene::SudokuScene(Sudoku::Level difficultyLevel) : difficultyLevel(difficultyLevel)
{
}

///////////////////////////////////////////
void SudokuScene::onCreate()
{
	connectToKeyPressed(sf::Keyboard::Escape, std::bind(&Scene::close, this, 0));
	setBackgroundColor(sf::Color::White);

	auto iconFont = AssetsManager::getFont("icon-font.ttf");
	Color buttonNormalColor("#d4d4d4");
	Color buttonHighlightColor("#2db5fc");

	auto sudokuBoard = new SudokuBoard(difficultyLevel);
	sudokuBoard->setOriginCenter();
	sudokuBoard->setPosition(windowSize.x * 0.5f, windowSize.y * 0.55);
	addChild(sudokuBoard);
	connectToEvent(sf::Event::KeyPressed, std::bind(&SudokuBoard::onKeyPressed, sudokuBoard, std::placeholders::_1));

	auto timer = new Timer;
	timer->setPosition(windowSize.x * 0.5f, windowSize.x * 0.075f);
	addChild(timer);

	auto pauseButton = new Button("P", iconFont);
	pauseButton->setColor(buttonNormalColor);
	pauseButton->setPosition(25, 25);
	pauseButton->onMouseOver.connect(std::bind(&Button::setColor, pauseButton, buttonHighlightColor));
	pauseButton->onMouseLeave.connect(std::bind(&Button::setColor, pauseButton, buttonNormalColor));
	pauseButton->onClick.connect(std::bind(&Timer::toggleRunning, timer));
	pauseButton->onClick.connect(std::bind(&SudokuBoard::toggleRunning, sudokuBoard));
	addChild(pauseButton);

	auto closeButton = new Button("C", iconFont);
	closeButton->setColor(buttonNormalColor);
	closeButton->setPosition(windowSize.x - 25, 25);
	closeButton->onClick.connect(std::bind(&Scene::close, this, 0));
	closeButton->onMouseOver.connect(std::bind(&Button::setColor, closeButton, Color("#f7475b")));
	closeButton->onMouseLeave.connect(std::bind(&Button::setColor, closeButton, buttonNormalColor));
	addChild(closeButton);
}

///////////////////////////////////////////
void SudokuScene::onClose(int scene)
{
	directorAction.type = DirectorAction::PopScene;
}
