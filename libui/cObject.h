#pragma once
#include "_inc.h"

class cBody : public Node
{
protected:
	bool init();

public:
	void load(const sMod::sActs& acts);
	void load(const sMod& mod, bool map);

	cSprite* getBody() const;
	virtual void setBody(eAct e, bool reframe = true);

	int getHeight(bool only1st) const;

	void setName(const std::string& name);
	void showName(bool show);
	void setNameColor(const sColor& color);

	void setLight(float delta);

	void say(const std::string& text, bool toast);

protected:
	Node* _nodeInner = nullptr;

	int  _hBody = 0, _h1 = 0, _hSay = 0;
	Node* _nodeSay = nullptr;

	sColor _colorName;
	cLabel* _labelName = nullptr;

	Node* _nodeBody = nullptr;
	std::map<eAct, cSprite*> _bodies;
	eAct _eact = eAct::eAtk;
	cSprite* _body = nullptr;
};


class cObject : public cBody, public cSpriteDelta
{
public:
	static cObject* create(const sMod& mod);
protected:
	bool init(const sMod& mod);

public:
	void loadTop(ulong top);
	void setBody(eAct e, bool reframe = true);

	void stand();
	void walk();
	void walk(const Vec2& vTo);

	void setWays(const std::vector<Vec2>& ways);
	void clearWays();
	bool isWays() const;

	void moving(int speed);

	void setHead(ulong head);
	void setScript(const std::string& script);
	void runScript();
protected:
	void update(float delta);
//	bool _isStand;

	bool _isTopPlaying = false;
	cSprite* _spriteTop = nullptr;

	std::vector<Vec2> _ways;
	ulong _head;
	std::string _script;
};