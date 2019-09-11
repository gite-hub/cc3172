#pragma once
#include "uiDesc.h"

class uiSkill : public Node
{
public:
	static uiSkill* create(const sRole* role);
protected:

	bool init(const sRole* role);

public:
	void load(const sRole* role);

	bool learn(int index, int ilv);

	void loadLabel(int skilv);

	void loadLabel(int index, int skilv);

protected:
	void apply();

	const sRole* _role = nullptr;
	bool _isLearned = false;
	int _select, _lv;
	u64 _exp, _money, _expOri, _moneyOri;
	std::vector<int> _skilvs, _skiOri;
	std::vector<sDescs> _descs;

	cLabelEasy*_labelNeedExp = nullptr;
	cLabelEasy* _labelNeedMoney = nullptr;
	cLabelEasy* _labelExp = nullptr;
	cLabelEasy* _labelMoney = nullptr;
	std::vector<cSprite1*> _sprites;
	std::vector<cLabelEasy*> _labels;
	std::vector<cLabelEasy*> _labelShadows;
	
	uiDesc* _textDesc = nullptr;
	cSprite9* _spriteSelect = nullptr;

	// 特技
	Menu* _menu = nullptr;
	std::vector<cSprite1*> _spriteSpecials;
	std::vector<MenuItem*> _menuItemSpecials;
	std::vector<sDescs> _descSpecials;
	cSprite9* _spriteSpecialSelect = nullptr;
public:
	static const int c72;
	static const Size cSizeSelect;
	// 角色 控制 战斗
	std::function<bool(const sRole*, const std::vector<int>&, u64, u64)> onLearn = nullptr;
};
