#include "Button.h"

Button::Button(std::shared_ptr<InputDevice::Mouse> mouse)
{
	isExternal = false;
	mInput = mouse;
	img[0] = 0; img[1] = 0;
	isOn = false;
}

Button::~Button()
{
	if (!isExternal) {
		if (img[0] > 0) DeleteGraph(img[0]);
		if (img[1] > 0) DeleteGraph(img[1]);
	}
}

void Button::SetImage(const std::string & filePath, bool isSwitch, bool isDivHorizonal, bool isOn)
{
	if (!isSwitch) {
		img[0] = LoadGraph(filePath.c_str());
		GetGraphSize(img[0], &size.first, &size.second);
	}
	else {
		GetImageSize_File(filePath.c_str(), &size.first, &size.second);
		if (isDivHorizonal) { //‰¡‚É•ªŠ„
			size.first /= 2;
			LoadDivGraph(filePath.c_str(), 2, 1, 2, size.first, size.second, img);
		}
		else { //c‚É•ªŠ„
			size.second /= 2;
			LoadDivGraph(filePath.c_str(), 2, 1, 2, size.first, size.second, img);
		}
		this->isOn = isOn;
		this->isSwitch = isSwitch;
	}
}

void Button::Draw()
{
	if (!OnMouse()) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}
	DrawGraph(pos.first, pos.second, img[isOn], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Button::OnMouse()
{
	if (pos.first <= mInput->GetPosition().first && mInput->GetPosition().first <= pos.first + size.first
		&& pos.second <= mInput->GetPosition().second && mInput->GetPosition().second <= pos.second + size.second) {
		return true;
	}
	return false;
}

bool Button::OnClick()
{
	if (OnMouse() && mInput->GetLeftPressFrame() == 1) {
		if (isSwitch) isOn = !isOn;
		return true;
	}
	return false;
}
