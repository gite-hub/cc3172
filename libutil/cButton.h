#pragma once
#include "cLabel.h"

enum class eAilgn { Left, Mid, Right };

class cLabelInner
{
public:
	void setColor(uchar r, uchar g, uchar b);
	void setColor(const sColor& color);

	void setString(const std::string& text);

	const std::string& getString();

protected:
	void setAilgn(eAilgn e, const Size& contentSize);

protected:
	cLabel* _label = nullptr;
	sColor _color;
	Vec2 _vLabel;
	eAilgn _eAilgn = eAilgn::Mid;
};

class cNode;
class cButton : public MenuItemSprite, public cLabelInner
{
public:
	static cButton* create(const std::string& text, eFont e);
	static cButton* create(const std::string& text);
	static cButton* create(eFont e);
	static cButton* create();

	static cButton* create2(const std::string& image, const std::string& text, eFont e);
	static cButton* create2(const std::string& image, const std::string& text);
	static cButton* create2(const std::string& image, eFont e);
	static cButton* create2(const std::string& image);

	static cButton* create2(ulong uid, const std::string& text, eFont e);
	static cButton* create2(ulong uid, const std::string& text);
	static cButton* create2(ulong uid);
	static cButton* create2();

	static cButton* create9(ulong uid, const std::string& text, eFont e);
	static cButton* create9(ulong uid, const std::string& text);
	static cButton* create9(ulong uid, eFont e);
	static cButton* create9(ulong uid);
protected:
	bool init(const std::string& image, ulong uid, const std::string& text, eFont e);

public:
	void setContentSize(const Size& contentSize);

// 	void setPosition(float x, float y);
// 	void setPosition(const Vec2& v);

	void selected();

	void unselected();

	void setEnabled(bool bEnabled);

	void setAilgn(eAilgn e);
	void setAilgn() { setAilgn(_eAilgn); }

	void set9(int other, int top);
	// ³¤°´
	void setEasy(bool easy) { _isEasy = easy; }
protected:
	Vec2 _v;
	bool _isEasy = false;
	int _9, _top9;
public:
	typedef std::function<void()> sClick;
	sClick onClick = nullptr;
	std::function<void(bool)> onKeep = nullptr;

};