#include "GameIntroduction.h"

GameIntroduction::GameIntroduction()
{
	mInput = std::make_shared<InputDevice::Mouse>();

	//�n�߂�Ɩ߂�{�^��
	start = std::make_unique<Button>(mInput);
	back = std::make_unique<Button>(mInput);
	start->SetImage("Assets/Images/System/start.png");
	back->SetImage("Assets/Images/System/back.png");
	start->Transfar(CommonSettings::WINDOW_WIDTH - start->GetSize().first, CommonSettings::WINDOW_HEIGHT - start->GetSize().second);
	back->Transfar(-1, CommonSettings::WINDOW_HEIGHT - back->GetSize().second);

	//���[�{�^��
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
	mInput->Update(); //���d�N���b�N���
	isPlay = false;
	isVoted = false;
	timer.Reset();
	SeekMovieToGraph(game->GetInfoImage(), 0);
	PlayMovieToGraph(game->GetInfoImage(), DX_PLAYTYPE_LOOP);
}

void GameIntroduction::Draw()
{
	//���悪��u�r�؂��͎̂d�l�B DirectShow�ɕ��匾��.
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
	//�E�N���b�N�ł��I����ʂ֖߂�
	if (mInput->GetRightPressFrame() == 1 || back->OnClick()) {
		return true;
	}
	if (start->OnClick()) {
		isPlay = true;
		ExecuteGame(); //�Q�[���v���C
	}

	//���[
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
	//�v���C�񐔂Ǝ��Ԃ��X�V
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
	bool flg = true;	//�t�H���_�̈ړ��ɐ��������Ƃ��̃t���O
	bool flg2 = false;  //�A�v���̋N���������ǂ����̃t���O
	playTime = 0;

	//�t�H���_�ړ�
	auto folder = currentDir + game->GetExePath();
	flg = SetCurrentDirectory(folder.c_str()) != 0;

	//�A�v���P�[�V�����N��
	if (flg) {
		std::string str;
		if (game->GetPlayer().empty()) { //exe���ڋN��
			str = "\"" + folder + game->GetExeName() + "\"";
		}//�O���A�v���P�[�V�����Ɉ����𑗂��ċN��
		else str = "\"" + game->GetPlayer() + "\" \"" + folder + game->GetExeName() + "\"";
		char* c = new char[str.size() + 1];
		sprintf_s(c, str.size() + 1, str.c_str());
		flg2 = CreateProcess(NULL, c, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) != 0;
	}
	if (flg2) {
		//�ŏ���
		SetWindowMinimizeFlag(TRUE);
		//�A�v���P�[�V�����I���҂�
		timer.Update();
		WaitForSingleObject(pi.hProcess, INFINITE);
		timer.Update();
		//�Q�[���̃v���C�񐔂Ǝ��Ԃ��X�V
		playTime = timer.GetDeltaTime();
		UpdateGameInfo();
		//�E�B���h�E�����ɖ߂�
		SetWindowMinimizeFlag(FALSE);
		//���̃t�H���_�ɖ߂�
		SetCurrentDirectory(currentDir.c_str());
	}
}