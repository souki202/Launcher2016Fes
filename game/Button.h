#pragma once
#include "DxLib.h"
#include <string>
#include <memory>
#include "InputDevice.h"
class Button {
public:
	Button(std::shared_ptr<InputDevice::Mouse> mouse);
	~Button();

	void SetImage(const std::string& filePath, bool isSwitch = false, bool isDivHorizonal = false, bool isOn = false);
	void Draw();
	void Transfar(int posX, int posY) { pos.first = posX; pos.second = posY; };
	bool OnMouse();
	bool OnClick();
	const std::pair<int, int>& GetSize() { return size; };
	const std::pair<int, int>& GetPosition() { return pos; };
private:
	std::shared_ptr<InputDevice::Mouse> mInput;
	bool isExternal;
	int img[2];
	std::pair<int, int> pos;
	std::pair<int, int> size;
	bool isSwitch;
	bool isOn;
};