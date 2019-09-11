#pragma once
#include "_inc.h"

class uiXL : public Node
{
public:
	static uiXL* create(const sRole* role);

protected:
	bool init(const sRole* role);

public:
	void load(const sRole* role);

	bool learn(int select);

	void loadLabel(int select, int xlv);

	void loadLabel(int xlv);

protected:
	void apply();

	int& getlv(int select);

	const sRole* _role = nullptr;
	int _maxlv;
	bool _isLearned = false;
	int _select = -1;
	sXl _xl, _xlOri, _xlbb, _xlbbOri;
	u64 _money, _moneyOri;

	cButton* _buttonLearn = nullptr;
	cLabelEasy* _labelExp = nullptr;
	cLabelEasy* _labelNeed = nullptr;
	std::vector<cLabelEasy*> _labelLvs;

	cSprite9* _sprite = nullptr;
public:
	// ½ÇÉ« ¿ØÖÆ Õ½¶·
	std::function<bool(const sRole*, const sXl&, const sXl&, u64)> onXL = nullptr;
};