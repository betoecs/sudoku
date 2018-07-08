#ifndef TIMER_HPP
#define TIMER_HPP

#include <LK/LinearLayout.hpp>
#include <LK/Text.hpp>
using namespace lk;

class Timer : public LinearLayout
{
public:
	Timer();
	void onUpdate(float deltaTime) override;
	void toggleRunning();

private:
	bool running;
	float totalSeconds;
	Text *icon;
	Text *time;
};

#endif // TIMER_HPP
