#pragma once
#include "_inc.h"
#include "ui/UIScrollView.h"

// 默认战斗点击无效
class uiDialog : public Node
{
public:
	struct sHeadName
	{
		ulong head = cSp::c0;
		std::string name;
	};

	CREATE_FUNC(uiDialog);
protected:
	virtual bool init();

public:
	typedef std::function<void(int)> CB;
	void load(ulong head, const std::string& name, const std::string& text, const std::vector<std::string>& selects = {}, const CB& cb = nullptr);
	void load(const sHeadName& headName, const std::string& text, const std::vector<std::string>& selects = {}, const CB& cb = nullptr);

protected:
	void loadInner(ulong head, const std::string& name, const std::string& text, const std::vector<std::string>& selects);

	cSprite1* _spriteHead = nullptr;
	cSprite9* _spriteName = nullptr;
	cLabel* _labelName = nullptr;
	cText* _textContent = nullptr;
	Sprite9* _spriteDialog = nullptr;
	Sprite9* _spriteSelect = nullptr;
	ui::ScrollView* _scrollView = nullptr;
	cButton* _buttonClose = nullptr;
public:
	cButton::sClick onClick = nullptr;
	static const int c160;
};