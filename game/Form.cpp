#include "Form.h"
Form::Form()
{
	SetMainWindowText(CommonSettings::GAME_TITLE);//ウィンドウのタイトル
	select.LoadGameLists("Assets/filelists");
	hiddenGame2.SetGames(select.GetAllGameInfo());
	scene = Scene::SELECT;
}

Form::~Form()
{
}

bool Form::Update()
{
	//キーボード, マウスの状態を更新
	kInput.Update();
	mInput.Update();

	//終了
	/*
	if (kInput.GetPressFrame(KEY_INPUT_ESCAPE)) {
		return false;
	}
	*/
	//ここからプログラムを書く
	switch (scene)
	{
	case Form::Scene::SELECT:
		select.Draw();
		selectNo = select.SelectingPlace();
		//ゲームをクリック
		if (selectNo.second) {
			//hidden
			if (selectNo.first == -2) {
				scene = Scene::HIDDEN_GAME;
				hiddenGame2.Reset();
				break;
			}
			intro.SetGameInfo(select.GetGameInfo(selectNo.first));
			scene = Scene::INTRO;
		}
		break;
	case Form::Scene::INTRO:
		intro.Draw();
		if (intro.Update()) {
			//select.Shuffle();
			if (intro.GetIsPlay()) select.ResetHiddenMode();
			scene = Scene::SELECT;
		}
		break;
	case Form::Scene::HIDDEN_GAME:
		if (!hiddenGame2.Update()) {
			select.ResetPosition();
			scene = Scene::SELECT;
		}
		hiddenGame2.Draw();
		break;
	case Form::Scene::INVALID:
		break;
	default: break;
	}

	return true;
}