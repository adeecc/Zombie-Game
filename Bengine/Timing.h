#pragma once

namespace Bengine {


class FpsLimiter {
public:
	FpsLimiter();
	~FpsLimiter();

	void init(float maxFPS);

	void setMaxFPS(float maxFPS);

	void begin();

	//Returns current FPS
	float end();

private:

	void calculateFPS();

	float _maxFPS;
	float _fps;
	float _frameTime;
	unsigned int _startTicks;

};
}