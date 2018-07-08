#ifndef MAIN_SCEHE_HPP
#define MAIN_SCEHE_HPP

#include <LK/Scene.hpp>
#include <LK/ButtonGroup.hpp>
using namespace lk;

class MainMenu : public Scene
{
public:
	void onCreate() override;
	void onClose(int scene) override;
	void onToggleDifficultyButton(Button *difficultyButton);

private:
	ButtonGroup *difficultyButtonGroup;
};

#endif // MAIN_SCEHE_HPP
