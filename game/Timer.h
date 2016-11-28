#pragma once
#include <chrono>

class Timer {
public:
	Timer() {
		Reset();
	}
	~Timer() {}

	void Update() {
		lastTime = nowTime;
		nowTime = std::chrono::system_clock::now();
	}

	void Reset() {
		nowTime = std::chrono::system_clock::now();
		initTime = lastTime = nowTime;
	}

	int GetDeltaTime() {
		return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - lastTime).count());
	}

	int GetElapsedTime() {
		return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - initTime).count());
	}

private:
	std::chrono::system_clock::time_point nowTime, lastTime, initTime;
};