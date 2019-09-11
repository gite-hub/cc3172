#pragma once
#include "uiPad.h"
#include "ui/UITextField.h"

class uiInput : public uiPad
{
public:
	CREATE_FUNC(uiInput);

protected:
	bool init();

public:
	void setString(const std::string& text);
	void setDesc(const std::string& desc);
	void setPlaceHolder(const std::string& placeHolder);

protected:
	cLabel* _labelDesc = nullptr;
	ui::TextField* _textField = nullptr;

public:
	std::function<void(const std::string&)> onInput = nullptr;
};