#pragma once
namespace CommonSettings {
	//解像度
	constexpr int WINDOW_WIDTH = 960;
	constexpr int WINDOW_HEIGHT = 768;

	//fps(60以上は垂直同期を切ってください。)
	constexpr int FRAME_RATE = 60;

	constexpr char* GAME_TITLE = "Launcher"; //Unicode文字セット利用時はwchar_tに。
};