#include "GameIntroduction.h"

GameIntroduction::GameIntroduction()
{
	mInput = std::make_shared<InputDevice::Mouse>();

	//始めると戻るボタン
	start = std::make_unique<Button>(mInput);
	back = std::make_unique<Button>(mInput);
	start->SetImage("Assets/Images/System/start.png");
	back->SetImage("Assets/Images/System/back.png");
	start->Transfar(CommonSettings::WINDOW_WIDTH - start->GetSize().first, CommonSettings::WINDOW_HEIGHT - start->GetSize().second);
	back->Transfar(-1, CommonSettings::WINDOW_HEIGHT - back->GetSize().second);

	//投票ボタン
	good = std::make_unique<Button>(mInput);
	bad = std::make_unique<Button>(mInput);
	voted = std::make_unique<Button>(mInput);
	notPlay = std::make_unique<Button>(mInput);
	good->SetImage("Assets/Images/System/good.png");
	bad->SetImage("Assets/Images/System/bad.png");
	voted->SetImage("Assets/Images/System/voted.png");
	notPlay->SetImage("Assets/Images/System/notPlay.png");
	good->Transfar(0, CommonSettings::WINDOW_HEIGHT - good->GetSize().second - start->GetSize().second);
	bad->Transfar(good->GetSize().first + 1, CommonSettings::WINDOW_HEIGHT - bad->GetSize().second - start->GetSize().second);
	voted->Transfar(0, CommonSettings::WINDOW_HEIGHT - voted->GetSize().second - start->GetSize().second);
	notPlay->Transfar(0, CommonSettings::WINDOW_HEIGHT - notPlay->GetSize().second - start->GetSize().second);

	char current[256];
	GetCurrentDirectory(255, current);
	currentDir = current;
	SetCurrentDirectory(currentDir.c_str());
	isPlay = false;
	isVoted = false;
	nextCanVoteRemaindTime = 0;
}

GameIntroduction::~GameIntroduction()
{
}

void GameIntroduction::SetGameInfo(std::shared_ptr<GameInfo> game)
{
	this->game = game;
	mInput->Update(); //多重クリック回避
	isPlay = false;
	isVoted = false;
	timer.Reset();
	SeekMovieToGraph(game->GetInfoImage(), 0);
	PlayMovieToGraph(game->GetInfoImage(), DX_PLAYTYPE_LOOP);
}

void GameIntroduction::Draw()
{
	//動画が一瞬途切れるのは仕様。 DirectShowに文句言え.
	DrawExtendGraph(0, 0, CommonSettings::WINDOW_WIDTH, CommonSettings::WINDOW_HEIGHT, game->GetInfoImage(), true);

	start->Draw();
	back->Draw();
	good->Draw();
	bad->Draw();
	if (isVoted) voted->Draw();
	if (!isPlay) notPlay->Draw();
}

bool GameIntroduction::Update()
{
	mInput->Update();
	//右クリックでも選択画面へ戻る
	if (mInput->GetRightPressFrame() == 1 || back->OnClick()) {
		return true;
	}
	if (start->OnClick()) {
		isPlay = true;
		ExecuteGame(); //ゲームプレイ
	}

	//投票
	if (!isVoted && isPlay) {
		if (good->OnClick()) {
			isVoted = true;
			game->AddGood();
		}
		if (bad->OnClick()) {
			isVoted = true;
			game->AddBad();
		}
	}
	return false;
}

void GameIntroduction::UpdateGameInfo()
{
	//プレイ回数と時間を更新
	game->AddPlayCount();
	game->AddPlayTime(playTime);
}

void GameIntroduction::ExecuteGame()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	bool flg = true;	//フォルダの移動に成功したときのフラグ
	bool flg2 = false;  //アプリの起動したかどうかのフラグ
	playTime = 0;

	//フォルダ移動
	auto folder = currentDir + game->GetExePath();
	flg = SetCurrentDirectory(folder.c_str()) != 0;

	//アプリケーション起動
	if (flg) {
		std::string str;
		if (game->GetPlayer().empty()) { //exe直接起動
			str = "\"" + folder + game->GetExeName() + "\"";
		}//外部アプリケーションに引数を送って起動
		else str = "\"" + game->GetPlayer() + "\" \"" + folder + game->GetExeName() + "\"";
		char* c = new char[str.size() + 1];
		sprintf_s(c, str.size() + 1, str.c_str());
		flg2 = CreateProcess(NULL, c, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) != 0;
	}
	if (flg2) {
		//最小化
		SetWindowMinimizeFlag(TRUE);
		//アプリケーション終了待ち
		timer.Update();
		WaitForSingleObject(pi.hProcess, INFINITE);
		timer.Update();
		//ゲームのプレイ回数と時間を更新
		playTime = timer.GetDeltaTime();
		UpdateGameInfo();
		//ウィンドウを元に戻す
		SetWindowMinimizeFlag(FALSE);
		//元のフォルダに戻る
		SetCurrentDirectory(currentDir.c_str());
	}
}