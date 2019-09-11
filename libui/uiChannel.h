#pragma once
#include "uiPad.h"
#include "ui/UIScrollView.h"

class uiChannel : public Node
{
public:
	static uiChannel* create(eFont eFnt) { CREATE(uiChannel, eFnt); }
protected:
	bool init(eFont eFnt);

public:
	void add(const std::string& name, const std::string& text);

protected:
	eFont _eFont;
	Vec2 _v;
	Size _s;
	std::list<cText*> _texts;
};

class uiChat : public uiPad
{
public:
	static uiChat* create(eFont eFnt) { CREATE(uiChat, eFnt); }

protected:
	bool init(eFont eFnt);

public:
	void add(const std::string& name, const std::string& text);

	void show();
protected:
	eFont _eFont;
	float _h = 0;
	ui::ScrollView* _scrollView = nullptr;
};