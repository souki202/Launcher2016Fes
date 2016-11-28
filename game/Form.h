#pragma once

#include "DxLib.h" //�b��������ł��肢�@|�ցE`�j�ׯ
#include "CommonSettings.h"
#include "InputDevice.h"

#include "HighSpeedDodgeGame.h"
#include "GameSelect.h"
#include "GameInfo.h"
#include "GameIntroduction.h"

class Form
{
public:
	enum struct Scene {
		SELECT, INTRO, HIDDEN_GAME, INVALID,
	}scene;
public:
	Form();
	~Form();

	bool Update();

private:
	InputDevice::Keyboard kInput;
	InputDevice::Mouse mInput;

	HighSpeedDodgeGame hiddenGame2;
	GameSelect select;
	std::pair<int, int> selectNo;
	std::shared_ptr<GameInfo> selectedGame;
	GameIntroduction intro;
	bool isSetGamesToHiddenGame;
};
//---------------------------------------------------------------------------