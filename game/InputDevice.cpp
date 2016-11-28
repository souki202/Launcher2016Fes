#include "InputDevice.h"

InputDevice::Keyboard::Keyboard()
{
	for (auto &x : m_frame) {
		x = 0;
	}
	for (auto &x : m_time) {
		x = 0;
	}
	for (auto &x : m_lastUpdateTime) {
		x = 0;
	}
	m_interval = 100;
}

InputDevice::Keyboard::~Keyboard()
{
}

// キーの入力状態更新
void InputDevice::Keyboard::Update()
{             
	timer.Update();

	GetHitKeyStateAll(m_isPushKey);  // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++) {
		if (m_isPushKey[i]) { // i番のキーコードに対応するキーが押されていたら
			m_frame[i]++;   // 加算
			m_time[i] += timer.GetDeltaTime();
		}
		else {              // 押されていなければ
			m_frame[i] = 0; // 0にする
			m_time[i] = 0;
		}
	}
}

bool InputDevice::Keyboard::IsRelease(int keyCode)
{
	if (GetPressFrame(keyCode) > 0) {
		m_isPress[keyCode] = true;
		return false;
	}
	else if (GetPressFrame(keyCode) == 0 &&
		m_isPress[keyCode] == true) {
		m_isPress[keyCode] = false;
		return true;
	}

	return false;
}

bool InputDevice::Keyboard::GetIsUpdate(int keyCode)
{
	if (!m_time[keyCode]) {
		m_lastUpdateTime[keyCode] = 0;
		return false;
	}
	else if (m_time[keyCode] && m_lastUpdateTime[keyCode] == 0) { //初回フレーム
		m_lastUpdateTime[keyCode] += m_interval * 3;
		return true;
	}
	else if (m_time[keyCode] && //押していて、次にtrueが返るべき時間を超えている時
		m_time[keyCode] >= m_lastUpdateTime[keyCode] + m_interval) {
		m_lastUpdateTime[keyCode] += m_interval;
		return true;
	}

	return false;
}


//ここからマウス
InputDevice::Mouse::Mouse()
{
	m_leftPress.first = 0;
	m_leftPress.second = 0;
	m_rightPress.first = 0;
	m_rightPress.second = 0;
	m_middlePress.first = 0;
	m_middlePress.second = 0;
	m_position.first = 0;
	m_position.second = 0;
	m_lastPosition.first = 0;
	m_lastPosition.second = 0;
}

InputDevice::Mouse::~Mouse()
{
}

void InputDevice::Mouse::Update()
{
	timer.Update();

	//力技だけど仕方ない MOUSE_INPUT_8とか0x0080やで･･･
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		m_leftPress.first++;
		m_leftPress.second += static_cast<int>(timer.GetDeltaTime());
	}
	else {
		m_leftPress.first = 0;
		m_leftPress.second = 0;
	}

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		m_rightPress.first++;
		m_rightPress.second += static_cast<int>(timer.GetDeltaTime());
	}
	else {
		m_rightPress.first = 0;
		m_rightPress.second = 0;
	}


	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0) {
		m_middlePress.first++;
		m_middlePress.second += static_cast<int>(timer.GetDeltaTime());
	}
	else {
		m_middlePress.first = 0;
		m_middlePress.second = 0;
	}

	m_lastPosition = m_position;
	GetMousePoint(&m_position.first, &m_position.second);
}


InputDevice::JoyPad::JoyPad()
{
}

InputDevice::JoyPad::~JoyPad()
{
}
//JoyKeyに関する関数
/*
使い方
JOYPAD１＊使いたいボタンの名前を引数としてわたす
JOYPAD1　は　１p
JOYPAD2　は　 2p

例:もしJOYPAD1の左を押す判定がほしければ

	if(Joypad_Get(JOYPAD1*BUTTON_LEFT) == 0){
		//処理
	}

*/
void InputDevice::JoyPad::Update()
{
	//Joypad1を使う

	//左
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_LEFT] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_LEFT]++;
	}
	//上
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_UP] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_UP]++;
	}
	//右
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_RIGHT] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_RIGHT]++;
	}
	//下
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_DOWN] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_DOWN]++;
	}

	//1
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_1] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_1]++;
	}
	//2
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_2] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_2]++;
	}
	//3
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_3] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_3]++;
	}
	//4
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_4] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_4]++;
	}
	//5
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_5] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_5]++;
	}
	//6
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_6] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_6]++;
	}
	//7
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_7] = 0;
	}
	else {
		m_JoyKey[BUTTON_7]++;
	}
	//8
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_8] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_8]++;
	}
	//9
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_9) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_9] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_9]++;
	}
	//10
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_10) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_10] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_10]++;
	}
	//11
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_11) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_11] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_11]++;
	}
	//12
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_12) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_12] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_12]++;
	}
	//13
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_13) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_13] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_13]++;
	}
	//14
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_14) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_14] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_14]++;
	}
	//15
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_15) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_15] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_15]++;
	}
	//16
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_16) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_16] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_16]++;
	}
	//17
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_17) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_17] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_17]++;
	}
	//18
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_18) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_18] = 0;
	}
	else {
		m_JoyKey[BUTTON_18]++;
	}
	//19
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_19) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_19] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_19]++;
	}
	//20
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_20) == 0) {
		m_JoyKey[JOYPAD1*BUTTON_20] = 0;
	}
	else {
		m_JoyKey[JOYPAD1*BUTTON_20]++;
	}
	/*

	Joypad2コン

	*/

	//左
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_LEFT) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_LEFT] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_LEFT]++;
	}
	//上
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_UP) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_UP] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_UP]++;
	}
	//右
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_RIGHT) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_RIGHT] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_RIGHT]++;
	}
	//下
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_DOWN) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_DOWN] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_DOWN]++;
	}

	//1
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_1) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_1] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_1]++;
	}
	//2
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_2) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_2] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_2]++;
	}
	//3
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_3) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_3] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_3]++;
	}
	//4
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_4) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_4] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_4]++;
	}
	//5
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_5) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_5] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_5]++;
	}
	//6
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_6) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_6] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_6]++;
	}
	//7
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_7) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_7] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_7]++;
	}
	//8
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_8) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_8] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_8]++;
	}
	//9
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_9) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_9] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_9]++;
	}
	//10
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_10) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_10] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_10]++;
	}
	//11
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_11) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_11] = 0;
	}
	else {
		m_JoyKey[BUTTON_11]++;
	}
	//2
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_12) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_12] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_12]++;
	}
	//3
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_13) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_13] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_13]++;
	}
	//4
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_14) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_14] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_14]++;
	}
	//5
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_15) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_15] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_15]++;
	}
	//6
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_16) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_16] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_6]++;
	}
	//7
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_17) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_17] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_17]++;
	}
	//8
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_18) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_18] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_18]++;
	}
	//9
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_19) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_19] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_19]++;
	}
	//10
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_20) == 0) {
		m_JoyKey[JOYPAD2*BUTTON_20] = 0;
	}
	else {
		m_JoyKey[JOYPAD2*BUTTON_20]++;
	}
}
//Joypadのボタンが上がったら
bool InputDevice::JoyPad::Release(int KeyCode)
{
	if (GetPressFrame(KeyCode) > 0) {
		upon = true;
	}
	else if (GetPressFrame(KeyCode) == 0 &&
		upon == true) {
		upon = false;
		return true;
	}
	return false;
}
//ジョイパッドのボタンが押されている状態を返す
int InputDevice::JoyPad::GetPressFrame(int KeyCode)
{
	return m_JoyKey[KeyCode];
}

