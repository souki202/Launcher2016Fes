#pragma once
#include <memory>
#include "InputDevice.h"
#include "Timer.h"
#include "CommonSettings.h"
#include "GameInfo.h"
#include "Button.h"

class GameIntroduction {
public:
	GameIntroduction();
	~GameIntroduction();

	void SetGameInfo(std::shared_ptr<GameInfo> game);
	void Draw();
	bool Update();
	void UpdateGameInfo();
	void ExecuteGame();
	bool GetIsPlay() { return isPlay; };
private:
	Timer timer;
	std::shared_ptr<InputDevice::Mouse> mInput;
	std::shared_ptr<GameInfo> game;

	std::unique_ptr<Button> start, back;
	std::unique_ptr<Button> good, bad, voted, notPlay;
	std::string currentDir;
	bool isPlay;
	bool isVoted;
	int nextCanVoteRemaindTime;

	int playTime;
};