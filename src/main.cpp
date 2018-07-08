#include <LK/AssetsManager.hpp>
#include <LK/Director.hpp>
using namespace lk;

#include <stdlib.h>

#include "Assets.h"
#include "MainMenu.hpp"

Vector2D windowSize(600, 700);

int main()
{
	srand(time(nullptr));
	AssetsManager::assetsPath = ASSETS;
	auto &director = Director::getInstance();
	director.create(sf::VideoMode(windowSize.x, windowSize.y), "sudoku", sf::Style::None);

	const auto &screenSize = sf::VideoMode::getDesktopMode();
	director.setPosition(sf::Vector2i(screenSize.width * 0.5 - windowSize.x * 0.5f, screenSize.height * 0.5 - windowSize.y * 0.5f));

	return director.startGame(new MainMenu);
}
