#pragma once
#include "uiAttr.h"
#include "uiStone.h"

class uiState : public Node
{
public:
	static uiState* create(const sRole* role);

protected:
	bool init(const sRole* role);

public:
	void load(const sRole* role);
	void load(const std::string& name);
	void load(eMenpai e);
	void loadAttr(const sRole* role, bool check);
	void loadLv(const sRole* role, bool check);
	void loadExp(const sRole* role, bool check);

	uiStone* getStone() const { return _stone; }

protected:
	const sRole* _role = nullptr;
	cLabelEasy* _labelLv = nullptr;
	cLabel* _labelName = nullptr;
	cLabel* _labelMenpai = nullptr;

	cButton* _buttonName = nullptr;

	uiAttr* _attrHp = nullptr;
	uiAttr* _attrMp = nullptr;
	uiAttr* _attrAp = nullptr;
	uiAttribute* _attr = nullptr;
	uiPoint* _point = nullptr;
	uiAttr* _attrExp = nullptr;
	uiStone* _stone = nullptr;
public:
	// 角色 控制 战斗 经验
	std::function<bool(const sRole*)> onLvup = nullptr;
	// 指针 控制 队伍 战斗
	std::function<bool(const sRole*, const std::string&)> onName = nullptr;
	// 指针 控制 队伍 战斗
	std::function<bool(const sRole*, eMenpai)> onMenpai = nullptr;
};

