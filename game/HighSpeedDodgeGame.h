#pragma once
#include <array>
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include "CommonSettings.h"
#include "GameInfo.h"
#include "Random.h"
#include "InputDevice.h"

class HighSpeedDodgeGame {
public:
	HighSpeedDodgeGame();
	~HighSpeedDodgeGame();

	void Reset();
	void SetGames(const std::array<std::vector<std::shared_ptr<GameInfo>>, 2>& a) { games = a; };
	/*
	falseが返るとゲームオーバー
	*/
	bool Update();
	void Draw();
private:
	Random rand;
	InputDevice::Mouse mInput;
	static constexpr int THUMB_SIZE = 180;
	static constexpr int NUM_OF_GAMES_X = CommonSettings::WINDOW_WIDTH / THUMB_SIZE + 2;
	static constexpr int NUM_OF_GAMES_Y = CommonSettings::WINDOW_HEIGHT / THUMB_SIZE + 1;
	static constexpr int OFFSET_Y = (THUMB_SIZE - CommonSettings::WINDOW_HEIGHT % THUMB_SIZE) / 2;
	std::array<std::vector<std::shared_ptr<GameInfo>>, 2> games;
	std::vector<int> spaces;
	std::vector<std::vector<int>> drawGames;

	int bgImg;
	int playerImg;
	int score;
	float speed;
	float deltaPos;
	Eigen::Vector2f playerPos;

	int drawHowToPlay;
	int howToPlayFont;
	int howToPlayWidth;
	bool isGameOver;
	int gameOverImg;
	int remaindGameOverTime;
	int whenGameOverScore;
};