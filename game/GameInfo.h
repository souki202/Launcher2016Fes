#pragma once
#include "DxLib.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <fstream>
#include <filesystem>

class GameInfo {
public:
	GameInfo(int font);
	~GameInfo();

	void Load(const std::vector<std::string>& info);
	void Save(std::ofstream& ofs);
	void AddPlayTime(int delta = 1) { playTime += delta; };
	void AddPlayCount(int delta = 1) { playCount += delta; };
	std::string GetExePath() { return std::string("\\Assets\\Works\\") + std::to_string(grade) + "\\" + name + "\\"; };
	const std::string& GetExeName() { return exeName; };
	const int& GetThumb() { return thumbImg; };
	const std::string& GetTitle() { return title; };
	const int& GetTitleBox() { return titleBox; };
	const std::string& GetName() { return name; };
	const int& GetInfoImage() { return infoImg; };
	const int& GetIsMovie() { return isMovie; };
	const std::string& GetPlayer() { return player; };
	static const int& GetNumOfInfos() { return NUM_OF_INFOS; };
private:
	static constexpr int NUM_OF_INFOS = 7;
	int grade;
	std::string name;
	std::string title;
	std::string exeName;
	int thumbImg;
	int infoImg;
	int playTime;
	int playCount;
	int introImg;
	std::string player;

	bool isMovie;
	int titleBox;
	int font;
};