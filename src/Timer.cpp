#include "Timer.hpp"

///////////////////////////////////////////
Timer::Timer() : LinearLayout(5), totalSeconds(0), running(true)
{
	Color color("#c3c3c3");

	icon = new Text("c", "icon-font.ttf");
	icon->setColor(color);
	addChild(icon);

	time = new Text("0:00", "Raleway/Raleway-Regular.ttf");
	time->setColor(color);
	addChild(time);

	forceUpdate();
}

///////////////////////////////////////////
void Timer::onUpdate(float frameTime)
{
	if (! running)
		return;

	int prevSeconds = totalSeconds;
	totalSeconds += frameTime;

	if (prevSeconds < (int) totalSeconds)
	{
		int minutes = totalSeconds / 60;
		const auto &secondsString = std::to_string((int) (totalSeconds) - minutes * 60);
		time->setString(std::to_string(minutes) + ":" + ((secondsString.size() == 1) ? "0" + secondsString : secondsString));
	}
}

///////////////////////////////////////////
void Timer::toggleRunning()
{
	running = ! running;
}
