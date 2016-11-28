#include "GameInfo.h"
#include "GameSelect.h"

GameInfo::GameInfo(int font)
{
	this->font = font;
}

GameInfo::~GameInfo()
{
	DeleteGraph(thumbImg);
	DeleteGraph(infoImg);
}

void GameInfo::Load(const std::vector<std::string>& info)
{
	grade = std::stoi(info[0]);
	name = info[1];
	title = info[2];
	exeName = info[3];
	thumbImg = LoadGraph((std::string("Assets/Images/") + std::to_string(grade) + "/" + name + "/" + "thumb.png").c_str());
	std::string folderPath = std::string("Assets/Images/") + std::to_string(grade) + "/" + name + "/";
	
	isMovie = false;
	bool loaded = false;;
	//推奨は 拡張子AVI,コーデックMPEG4
	namespace sys = std::tr2::sys;
	sys::path p(folderPath); // 列挙の起点
	std::for_each(sys::directory_iterator(p), sys::directory_iterator(),
		[&](const sys::path& p) {
		if (!loaded) {
			if (sys::is_regular_file(p)) {
				std::string s = p.filename().string();
				//文字数が5未満は"info."が含まれていない
				if (s.size() >= 5) {
					if (s.substr(0, 5) == "info.") {
						infoImg = LoadGraph((folderPath + s).c_str());
						loaded = true;

						//拡張子を調べる
						std::string ext;
						size_t extPos = s.find_last_of('.');
						if (extPos != std::string::npos && s.back() != '.') {
							ext = s.substr(extPos);
							//動画なら動画フラグon
							if (ext == "avi" || ext == "wmv" || ext == "mpg" || ext == "mpeg" || ext == "mp4"
								|| ext == "mov" || ext == "asf") {
								isMovie = true;
							}
						}
					}
				}
			}
		}
	});
	playTime = std::stoi(info[4]);
	playCount = std::stoi(info[5]);
	if (info.size() >= 7) player = info[6];
	else player = "";

	int titleWidth = GetDrawFormatStringWidthToHandle(font, title.c_str());
	titleBox = MakeScreen(titleWidth > GameSelect::GetThumbSize() - GameSelect::GetInterval() * 2 ? titleWidth : GameSelect::GetThumbSize() - GameSelect::GetInterval() * 2, 48, 1);
	SetDrawScreen(titleBox);
	DrawStringToHandle(0, 0, title.c_str(), 0xffffff, font);
	SetDrawScreen(DX_SCREEN_BACK);
}

void GameInfo::Save(std::ofstream & ofs)
{
	ofs << grade << "\t" << name << "\t" << title << "\t" << exeName << "\t"
		<< playTime << "\t" << playCount << "\t" << player << std::endl;
}
