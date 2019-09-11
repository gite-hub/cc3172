#pragma once
#include "cChatManager.h"
#include "cLabel.h"
#include "ui/UIRichText.h"


class cText : public ui::RichText
{
public:
	static cText* create(eFont e, int width = 0){ CREATE(cText, e, width); }
	static cText* create(int width = 0);
protected:
	virtual bool init(eFont e, int width);

public:
	// #0~#119 ±íÇé
	// #W #Y #R #G #B #M #O ÑÕÉ«
	void setString(const std::string& text);
	void setString(const std::string& name, const std::string& text);
	void setString(const cChatManager::sLines& lines);

protected:
	eFont _efnt;
	int _index;
};

