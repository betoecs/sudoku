#include "MainMenu.hpp"
#include "SudokuScene.hpp"
#include <LK/LinearLayout.hpp>

extern Vector2D windowSize;

///////////////////////////////////////////
void MainMenu::onCreate()
{
	connectToEvent(sf::Event::Closed, std::bind(&Scene::close, this, 0));
	setBackgroundColor(sf::Color::White);

	auto *font = AssetsManager::getFont("Raleway/Raleway-Regular.ttf");

	auto title = new Text("SUDOKU", font, 40);
	title->setColor(Color("#502a14"));
	title->setOriginCenter();
	title->setPosition(windowSize.x * 0.5f, windowSize.y * 0.1f);
	addChild(title);

	// Difficultyy buttons
	difficultyButtonGroup = new ButtonGroup(60);
	difficultyButtonGroup->setPosition(windowSize.x * 0.5, windowSize.y * 0.5);
	addChild(difficultyButtonGroup);

	auto easyDifficultyButton = new Button("EASY", font, 20, true);
	easyDifficultyButton->setData("level", std::to_string(Sudoku::Easy));
	easyDifficultyButton->setColor(Color("#aaa"));
	easyDifficultyButton->onToggled.connect(std::bind(&MainMenu::onToggleDifficultyButton, this, easyDifficultyButton));
	difficultyButtonGroup->addChild(easyDifficultyButton);

	auto mediumDifficultyButton = new Button("MEDIUM", font, 20, true);
	mediumDifficultyButton->setData("level", std::to_string(Sudoku::Medium));
	mediumDifficultyButton->setColor(Color("#aaa"));
	mediumDifficultyButton->onToggled.connect(std::bind(&MainMenu::onToggleDifficultyButton, this, mediumDifficultyButton));
	mediumDifficultyButton->toggle();
	difficultyButtonGroup->addChild(mediumDifficultyButton);

	auto hardDifficultyButton = new Button("HARD", font, 20, true);
	hardDifficultyButton->setData("level", std::to_string(Sudoku::Hard));
	hardDifficultyButton->setColor(Color("#aaa"));
	hardDifficultyButton->onToggled.connect(std::bind(&MainMenu::onToggleDifficultyButton, this, hardDifficultyButton));
	difficultyButtonGroup->addChild(hardDifficultyButton);

	// Main buttons
	auto mainButtonsLayout = new LinearLayout(0, LinearLayout::Vertical);
	mainButtonsLayout->setPosition(windowSize.x * 0.5f, windowSize.y * 0.7f);
	addChild(mainButtonsLayout);

	auto playButton = new Button("play-button.png", "PLAY", font, 30);
	playButton->onClick.connect(std::bind(&Scene::close, this, 1));
	mainButtonsLayout->addChild(playButton);

	auto quitButton = new Button("quit-button.png", "QUIT", font, 30);
	quitButton->onClick.connect(std::bind(&Scene::close, this, 0));
	mainButtonsLayout->addChild(quitButton);
}

///////////////////////////////////////////
void MainMenu::onClose(int scene)
{
	switch (scene)
	{
		case 1:
			directorAction.type = DirectorAction::PushScene;
			directorAction.scene = new SudokuScene((Sudoku::Level) std::stoi(difficultyButtonGroup->getToggledButton()->getData("level")));
		break;

		case 0:
			directorAction.type = DirectorAction::CloseGame;
	}
}

///////////////////////////////////////////
void MainMenu::onToggleDifficultyButton(Button *difficultyButton)
{
	difficultyButton->setColor(((difficultyButton->isToggled()) ? Color("#333") : Color("#aaa")));
}
