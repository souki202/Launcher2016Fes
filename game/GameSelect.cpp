#include "GameSelect.h"

GameSelect::GameSelect()
{
	mInput = std::make_shared<InputDevice::Mouse>();
	mt.seed((unsigned)time(NULL));

	overrideThumbImg = LoadGraph("Assets/Images/System/overridethumb.png");
	titleImg = LoadGraph("Assets/Images/System/title.png");
	titleKonamiImg = LoadGraph("Assets/Images/System/titlec.png");
	bgImg = LoadGraph("Assets/Images/System/l_091.png");
	hidden.bg = LoadGraph("Assets/Images/System/bgh.png");
	hidden.process[0] = LoadGraph("Assets/Images/System/bgdodge.png");
	hidden.process[1] = LoadGraph("Assets/Images/System/bgdarker.png");

	//�t�H���g�Ǎ�
	nameFont = CreateFontToHandle("Yu Gothic UI Heavy", 18, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	assert(AddFontResourceEx("Assets/Fonts/YuGothL.ttc", FR_PRIVATE, NULL));
	switchFont = CreateFontToHandle("Yu Gothic UI Light", 32, 1, DX_FONTTYPE_ANTIALIASING_8X8);
	
	//�����_��, �V���b�t���{�^���̐ݒ�
	randomBtn = std::make_unique<Button>(mInput);
	shuffleBtn = std::make_unique<Button>(mInput);
	switchDisplay = std::make_unique<Button>(mInput);
	randomBtn->SetImage("Assets/Images/System/random.png");
	shuffleBtn->SetImage("Assets/Images/System/shuffle.png");
	switchDisplay->SetImage("Assets/Images/System/switch.png", true);
	randomBtn->Transfar(
		CommonSettings::WINDOW_WIDTH - randomBtn->GetSize().first - INTERVAL,
		CommonSettings::WINDOW_HEIGHT - randomBtn->GetSize().second - INTERVAL
	);
	shuffleBtn->Transfar(
		CommonSettings::WINDOW_WIDTH - randomBtn->GetSize().first * 2 - INTERVAL * 2 - 24,
		CommonSettings::WINDOW_HEIGHT - randomBtn->GetSize().second - INTERVAL
	);
	switchDisplay->Transfar(
		CommonSettings::WINDOW_WIDTH - static_cast<int>(randomBtn->GetSize().first * 1.8) - INTERVAL * 2,
		CommonSettings::WINDOW_HEIGHT - static_cast<int>(randomBtn->GetSize().second * 1.7) - INTERVAL * 3
	);

	//hidden mode
	thisScreen = MakeScreen(CommonSettings::WINDOW_WIDTH, CommonSettings::WINDOW_HEIGHT, true);
	hidden.isItMode = false;
	hidden.se = LoadSoundMem("Assets/Sounds/SE/hiddenmode.mp3");

	isGraphicGroups = false;

	for (int i = 0; i < 10; i++) {
		inputBuf[i] = 0;
	}
	hidden.frameToChange = 180;
	hidden.isChanging = false;
}

GameSelect::~GameSelect()
{
	//�Q�[������ۑ�
	std::ofstream ofs;
	for (int i = 0; i < 2; i++) {
		ofs.open(gamesInfoFilePath + std::to_string(i) + ".txt");
		for (auto& x : games[i]) {
			x->Save(ofs);
		}
		ofs.close();
	}

	//hidden
	ofs.open("Assets/hidden.txt");
	hiddenGame->Save(ofs);

	RemoveFontResourceEx("Assets/Fonts/YuGothL.ttc", FR_PRIVATE, NULL);
}

bool GameSelect::LoadGameLists(std::string filePath)
{
	gamesInfoFilePath = filePath;
	std::ifstream ifs;
	std::vector<std::string> info;
	std::string line;
	for (int i = 0; i < 2; i++) {
		ifs.open(filePath + std::to_string(i) + ".txt");
		if (ifs.fail()) return false; //�ǂݍ��ݎ��s
		info.reserve(GameInfo::GetNumOfInfos());
		while (std::getline(ifs, line)) {
			if (line.front() != '#') { //#�̓R�����g(�X�V�ŏ����邯��)
				info.clear();
				std::stringstream ss(line);
				std::string tmp;
				while (std::getline(ss, tmp, '\t')) { //�^�u��؂�œǂݍ���
					info.push_back(tmp);
				}
				//������z����|�C�[���ēK���ɏ���������
				//�I�u�W�F�N�g�w���Ȃ�1�s�܂邲�Ƒ���̂����z
				games[i].push_back(std::make_shared<GameInfo>(nameFont));
				games[i].back()->Load(info);
				gamePosOffsetX[i].push_back(0);
			}
		}
		ifs.close();
	}

	//hidden��p
	ifs.open("Assets/hidden.txt");
	info.clear();
	while (std::getline(ifs, line)) {
		std::stringstream ss(line);
		std::string tmp;
		while (std::getline(ss, tmp, '\t')) {
			info.push_back(tmp);
		}
		break;
	}
	hiddenGame = std::make_shared<GameInfo>(nameFont);
	hiddenGame->Load(info);

	for (int i = 0; i < 2; i++) {
		shuffled[i].resize(games[i].size(), 0);
		std::iota(shuffled[i].begin(), shuffled[i].end(), 0);
	}
	Shuffle(isGraphicGroups);
	return true;
}

void GameSelect::Draw()
{
	SetDrawScreen(thisScreen);
	ClearDrawScreen();

	//bg
	if (hidden.isItMode) {
		DrawGraph(0, 0, hidden.bg, true);
		if (hidden.time-- < 0) {
			ResetHiddenMode();
		}
	}
	else DrawGraph(0, 0, bgImg, true);

	//�^�C�g��
	if (0 <= mInput->GetPosition().second && mInput->GetPosition().second <= 128) {
		DrawGraph(gamePosOffsetX[isGraphicGroups].front(), 0, titleKonamiImg, true);
	}
	else DrawGraph(gamePosOffsetX[isGraphicGroups].front(), 0, titleImg, true);

	//�Q�[������
	for (std::size_t i = 0; i < shuffled[isGraphicGroups].size(); i++) {
		//�摜
		DrawExtendGraph(
			INTERVAL + (i % NUM_OF_ROWS) * THUMB_SIZE + gamePosOffsetX[isGraphicGroups][i],
			INTERVAL + TITLE_HEIGHT + (i / NUM_OF_ROWS) * THUMB_SIZE,
			(i % NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL + gamePosOffsetX[isGraphicGroups][i],
			TITLE_HEIGHT + (i / NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL,
			games[isGraphicGroups][shuffled[isGraphicGroups][i]]->GetThumb(),
			true
			);

		//�I�𒆂Ȃ班����������
		if (i == selectingNo.first) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 48);
			DrawBox(
				INTERVAL + (i % NUM_OF_ROWS) * THUMB_SIZE + gamePosOffsetX[isGraphicGroups][i],
				INTERVAL + TITLE_HEIGHT + (i / NUM_OF_ROWS) * THUMB_SIZE,
				(i % NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL + gamePosOffsetX[isGraphicGroups][i],
				TITLE_HEIGHT + (i / NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL,
				0xffffff,
				true
				);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		//���O�ƃ^�C�g�������Ԃ���
		//�^�C�g��
		DrawExtendGraph(
			INTERVAL + (i % NUM_OF_ROWS) * THUMB_SIZE + gamePosOffsetX[isGraphicGroups][i],
			INTERVAL + TITLE_HEIGHT + (i / NUM_OF_ROWS) * THUMB_SIZE,
			(i % NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL + gamePosOffsetX[isGraphicGroups][i],
			TITLE_HEIGHT + (i / NUM_OF_ROWS) * THUMB_SIZE - INTERVAL + 48,
			overrideThumbImg,
			true
			);
		SetDrawMode(DX_DRAWMODE_BILINEAR); //�����^�C�g���p
		DrawExtendGraph(
			INTERVAL + (i % NUM_OF_ROWS) * THUMB_SIZE + gamePosOffsetX[isGraphicGroups][i],
			INTERVAL + TITLE_HEIGHT + (i / NUM_OF_ROWS) * THUMB_SIZE,
			(i % NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL + gamePosOffsetX[isGraphicGroups][i],
			TITLE_HEIGHT + (i / NUM_OF_ROWS) * THUMB_SIZE + INTERVAL + 48,
			games[isGraphicGroups][shuffled[isGraphicGroups][i]]->GetTitleBox(),
			true
			);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		//���O
		DrawExtendGraph(
			INTERVAL + (i % NUM_OF_ROWS) * THUMB_SIZE + gamePosOffsetX[isGraphicGroups][i],
			TITLE_HEIGHT + (i / NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL,
			(i % NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL + gamePosOffsetX[isGraphicGroups][i],
			INTERVAL + TITLE_HEIGHT + (i / NUM_OF_ROWS + 1) * THUMB_SIZE - 48,
			overrideThumbImg,
			true
			);
		DrawFormatStringToHandle(
			INTERVAL + (i % NUM_OF_ROWS) * THUMB_SIZE + gamePosOffsetX[isGraphicGroups][i],
			INTERVAL + TITLE_HEIGHT + (i / NUM_OF_ROWS + 1) * THUMB_SIZE - 36,
			0xffffff,
			nameFont,
			games[isGraphicGroups][shuffled[isGraphicGroups][i]]->GetName().c_str()
			);
	}

	//hidden
	if (selectingNo.first == hidden.PLACE) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
		DrawBox(
			INTERVAL + (hidden.PLACE % NUM_OF_ROWS) * THUMB_SIZE,
			INTERVAL + TITLE_HEIGHT + (hidden.PLACE / NUM_OF_ROWS) * THUMB_SIZE,
			(hidden.PLACE % NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL,
			TITLE_HEIGHT + (hidden.PLACE / NUM_OF_ROWS + 1) * THUMB_SIZE - INTERVAL,
			0xffffff,
			true
		);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	randomBtn->Draw();
	shuffleBtn->Draw();
	switchDisplay->Draw();
	if (!switchDisplay->OnMouse()) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}
	DrawStringToHandle(
		switchDisplay->GetPosition().first + switchDisplay->GetSize().first,
		switchDisplay->GetPosition().second,
		"����",
		0xffffff, switchFont
		);
	DrawStringToHandle(
		switchDisplay->GetPosition().first + switchDisplay->GetSize().first,
		switchDisplay->GetPosition().second + 30,
		"3D���f��",
		0xffffff, switchFont
	);
	DrawStringToHandle(
		switchDisplay->GetPosition().first - 90,
		switchDisplay->GetPosition().second + 16,
		"�Q�[��",
		0xffffff, switchFont
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(DX_SCREEN_BACK);
	if (hidden.isItMode) {
		GraphBlend(thisScreen, hidden.process[0], 255, DX_GRAPH_BLEND_OVERLAY);
	}
	DrawGraph(0, 0, thisScreen, true);
	if(hidden.isItMode) DrawGraph(0, 0, hidden.process[1], true);
}

const std::pair<int, bool>& GameSelect::SelectingPlace()
{
	mInput->Update();
	if (hidden.isChanging) {
		hidden.frameToChange--;
		//�e���ڂ̈ړ�
		for (auto& x : gamePosOffsetX) {
			x.back() += 8 + x.back() / 15;
			for (int i = x.size() - 2; i >= 0; --i) {
				if (x[i + 1] - x[i] > THUMB_SIZE / 2) {
					x[i] += 8 + x[i] / 15;
				}
			}
		}

		if (hidden.frameToChange <= 0) {
			hidden.frameToChange = 180;
			hidden.isChanging = false;
			selectingNo.first = -2;
			selectingNo.second = true;
			return selectingNo;
		}
	}
	//��芸�������O��I�����Ă��邱�Ƃɂ���
	int x = -1, y = -1;
	//�}�E�X���W����A�I�����Ă���C���f�b�N�X���v�Z
	if (mInput->GetPosition().first >= 0) {
		x = mInput->GetPosition().first / THUMB_SIZE;
	}
	if (mInput->GetPosition().second - TITLE_HEIGHT >= 0) {
		y = (mInput->GetPosition().second - TITLE_HEIGHT) / THUMB_SIZE;
	}
	//�Q�[�������݂���s���܂ޏꍇ
	if (0 <= x && x < NUM_OF_ROWS && 0 <= y) {
		selectingNo.first = x + NUM_OF_ROWS * y;
		//�Q�[�������݂���Ȃ�I���t���O��on�ɂ���
		if (0 <= selectingNo.first && selectingNo.first < static_cast<int>(games[isGraphicGroups].size())
			&& mInput->GetLeftPressFrame() == 1) {
			selectingNo.second = true;
		} //hidden��I��
		else if (x + y * NUM_OF_ROWS == hidden.PLACE && mInput->GetLeftPressFrame() == 1) {
			if (!hidden.isItMode) {
				hidden.isChanging = true;
			}
			else {
				selectingNo.second = true;
			}
		} //�ǂ���I�����Ȃ�����
		else selectingNo.second = false;
	}
	else {
		selectingNo.first = -1;
		selectingNo.second = false;
	}

	//�����_���I��
	if (randomBtn->OnClick()) {
		selectingNo.first = rand.Generate(0, games[isGraphicGroups].size() - 1);
		selectingNo.second = true;
	} //�V���b�t��
	else if (shuffleBtn->OnClick()) {
		Shuffle(isGraphicGroups);
	} //�\�t�g<->�O���̃X�C�b�`
	else if (switchDisplay->OnClick()) { 
		isGraphicGroups = !isGraphicGroups;
	}

	//hidden
	if (UpdateInputBuffer() && !hidden.isItMode) {
		hidden.isItMode = true;
		hidden.time = hidden.INIT_TIME;
		PlaySoundMem(hidden.se, DX_PLAYTYPE_BACK);
		//���͗������N���A
		for (int i = 0; i < 10; i++) {
			inputBuf[i] = 0;
		}
	}

	return selectingNo;
}

bool GameSelect::UpdateInputBuffer()
{
	kInput.Update();
	for (int i = 0; i < 255; i++) {
		if (kInput.GetPressFrame(i) == 1) {
			//buf�̍X�V
			//���܂ł̓��͗�����1��ɂ��炷
			for (int i = 9; i >= 1; i--) {
				inputBuf[i] = inputBuf[i - 1];
			}
			inputBuf[0] = i;
		}
	}
	//K��NAMI�R�}���h
	if (inputBuf[9] == KEY_INPUT_UP && inputBuf[8] == KEY_INPUT_UP
		&& inputBuf[7] == KEY_INPUT_DOWN && inputBuf[6] == KEY_INPUT_DOWN
		&& inputBuf[5] == KEY_INPUT_LEFT && inputBuf[4] == KEY_INPUT_RIGHT
		&& inputBuf[3] == KEY_INPUT_LEFT && inputBuf[2] == KEY_INPUT_RIGHT
		&& inputBuf[1] == KEY_INPUT_B && inputBuf[0] == KEY_INPUT_A) {
		return true;
	}

	return false;
}
