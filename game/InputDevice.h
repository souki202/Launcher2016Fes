#pragma once
//----------------------------------------------------------
#include <array>
#include "DxLib.h"
#include "Timer.h"
//----------------------------------------------------------
namespace InputDevice {
	class Keyboard {
	public:
		Keyboard();
		~Keyboard();
		void Update();				// キーの入力状態を更新する
		int GetPressFrame(int keyCode)	{ return m_frame[keyCode]; }// 引数のキーコードのキーの入力フレーム数を返す
		int GetPressTime(int keyCode)	{ return m_time[keyCode]; }	// 引数のキーコードのキーの入力時間(リアルタイム)を返す
		bool IsRelease(int keyCode);	// ボタンが上がったとき

		void SetInterval(int time)	{ m_interval = time; };	//ミリ秒
		bool GetIsUpdate(int keyCode);	//フレーム基準なら余り求めてね★
	private:
		Timer timer;
		std::array<int, 256> m_frame;
		std::array<int, 256> m_time;
		std::array<int, 256> m_lastUpdateTime;
		std::array<bool, 256> m_isPress;
		char m_isPushKey[256];	//Update()でキーの入力状態を保持

		int m_interval;
	};

	class Mouse {
	public:
		Mouse();
		~Mouse();

		void Update();

		int GetLeftPressFrame()		{ return m_leftPress.first; };
		int GetLeftPressTime()		{ return m_leftPress.second; };
		int GetRightPressFrame()	{ return m_rightPress.first; };
		int GetRightPressTime()		{ return m_rightPress.second; };
		int GetMiddlePressFrame()	{ return m_middlePress.first; };
		int GetMiddlePressTime()	{ return m_middlePress.second; };
		int GetWheelRotateValue()	 { return GetMouseWheelRotVol(); };	//奥が正, 手前が負
		const std::pair<int, int>& GetPosition() { 
			return m_position;
		};
		const std::pair<int, int>& GetDeltaPosition() {
			return std::make_pair(m_position.first - m_lastPosition.first, m_position.second - m_lastPosition.second);
		};
	private:
		Timer timer;
		std::pair<int, int> m_leftPress; //フレーム, 時間
		std::pair<int, int> m_rightPress;
		std::pair<int, int> m_middlePress;
		std::pair<int, int> m_position;
		std::pair<int, int> m_lastPosition;
	};

	//これだけ殆ど前のテンプレのまま放置
	class JoyPad {
	public:
		JoyPad();
		~JoyPad();
		void Update();
		bool Release(int KeyCode);
		int GetPressFrame(int KeyCode);

	private:
		int m_JoyKey[68];
		bool upon;

		//Keyboard.h
		static constexpr int JOYPAD1 = 1;
		static constexpr int JOYPAD2 = 34 + 1;
		//JOYPAD設定
		static constexpr int BUTTON_LEFT = 0;
		static constexpr int BUTTON_UP = 1;
		static constexpr int BUTTON_RIGHT = 2;
		static constexpr int BUTTON_DOWN = 3;

		static constexpr int BUTTON_1 = 4; //z  PSコン ×
		static constexpr int BUTTON_2 = 5; //x  PSコン ○
		static constexpr int BUTTON_3 = 6; //c  PSコン □
		static constexpr int BUTTON_4 = 7; //a  PSコン △

		static constexpr int BUTTON_5 = 8; //s  PSコン L1
		static constexpr int BUTTON_6 = 9; //d  PSコン L2
		static constexpr int BUTTON_7 = 10; //q  PSコン R1
		static constexpr int BUTTON_8 = 11; //w  PSコン R2

		static constexpr int BUTTON_9 = 12; //esc PSコン　SELECT
		static constexpr int BUTTON_10 = 13; //space PSコン　START
		static constexpr int BUTTON_11 = 14; //
		static constexpr int BUTTON_12 = 15; //
		static constexpr int BUTTON_13 = 16; //
		static constexpr int BUTTON_14 = 17; //
		static constexpr int BUTTON_15 = 18; //
		static constexpr int BUTTON_16 = 19; //
		static constexpr int BUTTON_17 = 20; //
		static constexpr int BUTTON_18 = 21; //
		static constexpr int BUTTON_19 = 22; //
		static constexpr int BUTTON_20 = 23; //
		static constexpr int BUTTON_21 = 24; //
		static constexpr int BUTTON_22 = 25; //
		static constexpr int BUTTON_23 = 26; //
		static constexpr int BUTTON_24 = 27; //
		static constexpr int BUTTON_25 = 28; //
		static constexpr int BUTTON_26 = 29; //
		static constexpr int BUTTON_27 = 30; //
		static constexpr int BUTTON_28 = 31; //
		static constexpr int BUTTON_29 = 32; //
		static constexpr int BUTTON_30 = 33; //
	};
}