#include "HighSpeedDodgeGame.h"

HighSpeedDodgeGame::HighSpeedDodgeGame()
{
	playerImg = LoadGraph("Assets/Images/Player/1.png");
	bgImg = LoadGraph("Assets/Images/System/l_091.png");
	howToPlayFont = CreateFontToHandle("Meiryo", 48, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	howToPlayWidth = GetDrawStringWidthToHandle("マウスで自機操作してね", std::string("マウスで自機操作してね").size(), howToPlayFont);
	gameOverImg = LoadGraph("Assets/Images/System/gameoverlauncher.png");
}

HighSpeedDodgeGame::~HighSpeedDodgeGame()
{
	DeleteGraph(playerImg);
}

void HighSpeedDodgeGame::Reset()
{
	playerPos << 0.f, 0.f;
	score = 0;
	deltaPos = CommonSettings::WINDOW_WIDTH * 3;
	spaces.clear();
	drawGames.clear();
	speed = 6;
	drawHowToPlay = 150;
	isGameOver = false;
	remaindGameOverTime = 180;
}

bool HighSpeedDodgeGame::Update()
{
	drawHowToPlay--;
	//移動と、移動量に応じたスコア加算
	deltaPos -= speed;
	if (!isGameOver) {
		score += static_cast<int>(speed * 1000);
	}
	else {
		remaindGameOverTime--;
	}
	//画面外のものを削除
	if (deltaPos <= -THUMB_SIZE && !spaces.empty()) {
		spaces.erase(spaces.begin());
		drawGames.erase(drawGames.begin());
		deltaPos += 180;
	}
	//右端に新しい場所を追加
	while (spaces.size() < NUM_OF_GAMES_X) {
		if (spaces.empty()) {
			spaces.push_back(2);
		}
		else spaces.push_back(spaces.back() + rand.Generate(-1, 1));
		if (spaces.back() < 0) spaces.back() = 0;
		else if (spaces.back() >= NUM_OF_GAMES_Y - 2) spaces.back() = NUM_OF_GAMES_Y - 2;

		drawGames.push_back(std::vector<int>());
		for (int i = 0; i < NUM_OF_GAMES_Y; i++) {
			//ソフト班orグラ班
			int side = rand.Generate(0, 1);
			//サムネのハンドルをランダムで取得
			drawGames.back().push_back(games[side][rand.Generate(0, games[side].size() - 1)]->GetThumb());
		}
	}
	speed += 0.005f;
	if (speed > static_cast<float>(THUMB_SIZE) / 2) {
		speed = static_cast<float>(THUMB_SIZE) / 2;
	}

	//当たり判定
	if (!isGameOver) {
		mInput.Update();
		for (int i = 0; i < spaces.size(); i++) {
			for (int j = 0; j < drawGames[i].size(); j++) {
				if (j != spaces[i] && j != spaces[i] + 1) {
					if (i * THUMB_SIZE + deltaPos <= mInput.GetPosition().first &&  mInput.GetPosition().first <= (i + 1) * THUMB_SIZE + deltaPos
						&& j * THUMB_SIZE - OFFSET_Y <= mInput.GetPosition().second &&  mInput.GetPosition().second <= (j + 1) * THUMB_SIZE - OFFSET_Y) {
						isGameOver = true;
						whenGameOverScore = score;
					}
				}
			}
		}
		//画面外はゲームオーバー
		if (mInput.GetPosition().first < 0 || CommonSettings::WINDOW_WIDTH < mInput.GetPosition().first
			|| mInput.GetPosition().second < 0 || CommonSettings::WINDOW_HEIGHT < mInput.GetPosition().second) {
			isGameOver = true;
			whenGameOverScore = score;
		}
	}
	if (remaindGameOverTime <= 0) {
		return false;
	}
	return true;
}

void HighSpeedDodgeGame::Draw()
{
	DrawGraph(0, 0, bgImg, true);
	for (int i = 0; i < spaces.size(); i++) {
		for (int j = 0; j < drawGames[i].size(); j++) {
			if (j != spaces[i] && j != spaces[i] + 1) {
				DrawExtendGraphF(i * THUMB_SIZE + deltaPos,
					static_cast<float>(j * THUMB_SIZE - OFFSET_Y), 
					i * THUMB_SIZE + deltaPos + 180,
					static_cast<float>(j * THUMB_SIZE - OFFSET_Y) + 180,
					drawGames[i][j],
					true);
			}
		}
	}
	//マウス座標に自機表示
	DrawGraph(mInput.GetPosition().first - 32, mInput.GetPosition().second - 32, playerImg, true);

	//マウス操作してね表示
	if (drawHowToPlay > 0) {
		DrawFormatStringToHandle((CommonSettings::WINDOW_WIDTH - howToPlayWidth) / 2, CommonSettings::WINDOW_HEIGHT / 2 - 24, 0xffffff, howToPlayFont, "マウスで自機操作してね");
	}

	//スコア
	DrawFormatStringToHandle(20, 20, 0xffffff, howToPlayFont, "%d", score / 1000);

	//ゲームオーバー
	if (isGameOver) {
		DrawGraph(0, 0, gameOverImg, true);
	}
}
