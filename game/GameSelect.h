#pragma once
#include "DxLib.h"
#include "CommonSettings.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <memory>
#include <algorithm>
#include <random>
#include <numeric>
#include <cassert>
#include "Random.h"
#include "GameInfo.h"
#include "InputDevice.h"
#include "Button.h"

class GameSelect {
public:
	GameSelect();
	~GameSelect();

	bool LoadGameLists(std::string filePath);
	void Draw();
	void Shuffle(int groups) { std::shuffle(shuffled[groups].begin(), shuffled[groups].end(), mt); };
	std::shared_ptr<GameInfo> GetGameInfo(int no) { 
		if (hidden.isItMode) return hiddenGame;
		return games[isGraphicGroups][shuffled[isGraphicGroups][no]];
	};
	void ResetPosition() { for (auto& x : gamePosOffsetX) { for (auto& y : x) y = 0; } };
	const std::array<std::vector<std::shared_ptr<GameInfo>>, 2>& GetAllGameInfo() { return games; };
	const std::pair<int, bool>& SelectingPlace();
	static constexpr int GetThumbSize() { return THUMB_SIZE; };
	static constexpr int GetInterval() { return INTERVAL; };
	const bool& IsHiddenMode() { return hidden.isItMode; };
	void ResetHiddenMode() { hidden.isItMode = false; hidden.time = hidden.INIT_TIME; };
	bool UpdateInputBuffer();
	void SaveGameInfo();
private:
	InputDevice::Keyboard kInput;
	std::shared_ptr<InputDevice::Mouse> mInput;
	std::mt19937 mt;
	
	Random rand;
	/*
	サムネは180x180
	*/
	std::array<std::vector<std::shared_ptr<GameInfo>>, 2> games;
	std::array<std::vector<float>, 2> gamePosOffsetX;
	bool isGraphicGroups;
	std::shared_ptr<GameInfo> hiddenGame;
	std::vector<int> shuffled[2];
	int overrideThumbImg;
	static constexpr int NUM_OF_ROWS = 5;
	static constexpr int THUMB_SIZE = CommonSettings::WINDOW_WIDTH / NUM_OF_ROWS;
	static constexpr int INTERVAL = 6;
	static constexpr int TITLE_HEIGHT = 128;
	std::pair<int, bool> selectingNo; //位置,クリック

	struct Hidden {
		bool isItMode;
		static constexpr int INIT_TIME = 60 * 23;
		int time = INIT_TIME;
		static constexpr int PLACE = 2 + NUM_OF_ROWS * 2;
		int process[2];
		int bg;
		int blended;
		int se;
		int frameToChange;
		bool isChanging;
	}hidden;
	int nameFont;
	int titleImg;
	int titleKonamiImg;
	int bgImg;
	int switchFont;

	int thisScreen;

	std::unique_ptr<Button> randomBtn, shuffleBtn, switchDisplay;
	
	std::string gamesInfoFilePath;

	int inputBuf[10];
};