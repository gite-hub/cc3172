#pragma once
#include "uiAttr.h"
#include "uiPad.h"

class uiAddpoint5 : public Node
{
public:
	static uiAddpoint5* create(bool is5);

protected:
	bool init(bool is5);

	void updatePoint();
public:
	void load(const sPoint& point, int lv);
	void load(int lv);

protected:
	sPoint _point;
	sPoint _point5;
	sPoint _pointShow;
	int _lv;
	bool _is5;
	bool _isPointed = false;
	std::array<int*, 5> _points;
	std::array<cButton*, 5> _buttonAdds;
	std::array<cButton*, 5> _buttonSubs;
	cButton* _buttonConfirm = nullptr;

	cLabelEasy* _labelBody = nullptr;
	cLabelEasy* _labelMana = nullptr;
	cLabelEasy* _labelStr = nullptr;
	cLabelEasy* _labelDex = nullptr;
	cLabelEasy* _labelAgi = nullptr;
	cLabelEasy* _labelRemian = nullptr;
public:
	std::function<void(const sPoint&)> onPoint = nullptr;
	cButton::sClick onLong = nullptr;
};

class cAddpoint
{
protected:
	bool init(Node* parent);
public:
	void loadAttr(const sProperty* pro);

	void load(const sProperty* pro);

protected:
	const sProperty* _pro = nullptr;
	uiAttribute* _attr = nullptr;
	uiAddpoint5* _point = nullptr;
	uiAddpoint5* _point5 = nullptr;

public:
	// ÷∏’Î ’Ω∂∑
	std::function<bool(const sProperty*, const sPoint&)> onPoint = nullptr;
};


class uiAddpoint : public Node, public cAddpoint
{
public:
	static uiAddpoint* create(const sProperty* pro);

protected:
	virtual bool init(const sProperty* pro);
};


class uiAddpointer : public uiPad, public cAddpoint
{
public:
	static uiAddpointer* create(const sProperty* pro);

protected:
	virtual bool init(const sProperty* pro);
};