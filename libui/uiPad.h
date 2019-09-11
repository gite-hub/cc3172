#pragma once
#include "_inc.h"

class uiPad : public Node
{
public:
	static uiPad* create(const std::string& image, bool swallowTouches = true);
	static uiPad* create(bool swallowTouches = true);
	static uiPad* create(ulong uid, bool swallowTouches = true);
protected:
	bool init(const std::string& image, ulong uid, bool swallowTouches);
	bool init(const std::string& image, bool swallowTouches);
	bool init(const std::string& image);
	bool init(ulong uid, bool swallowTouches);
	bool init(ulong uid);
public:
	virtual void setContentSize(const Size& contentSize);

	void setTitle(const std::string& title);

	void setClose(bool visible);
	// 点击区域外是否close
	void setCloseOnOut(bool close) { _isCloseOnOut = close; }

	void resetButtonTitlePosition();

	void setRemoveOnClose(bool remove) { _isRemoveOnColse = remove; }

	void setAlpha(bool alpha);

	virtual void show();

	virtual void close();

	Menu* getMenu() const { return _menu; }
protected:
	cNode* _nodeAlpha = nullptr;
	Menu* _menu = nullptr;
	MenuItem* _menuItemPad = nullptr;
	Node* _nodePad = nullptr;
	cButton* _buttonClose = nullptr;
	cLabel* _labelTitle = nullptr;
	Sprite* _spriteTitle = nullptr;
	bool _isRemoveOnColse;
	bool _isCloseOnOut;
public:
	static const Size cSize;
	std::function<void(bool)> onClose = nullptr;
	cButton::sClick onClick = nullptr, onClickOut = nullptr;
};