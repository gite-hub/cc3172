#pragma once
#include "_inc.h"

class uiMod : public Node
{
public:
// 	static uiMod* create(int wh, const sMod& mod, int lv, int tlv);
// 	static uiMod* create(int wh, const sMod& mod, int lv);
	static uiMod* create(int wh);
// 	static uiMod* create(const sMod& mod, int lv, int tlv);
// 	static uiMod* create(const sMod& mod, int lv);
	static uiMod* create();
protected:
	bool init(int wh/*, const sMod& mod, int lv, int tlv*/);

public:
	void load(const sPet* pet);
	void load(const sMod& mod, int lv, int tlv);
	void load(const sMod& mod);
	void load(int lv);
	void loadTakeLv(int tlv);
	void setJJ(bool isjj);
protected:
	sMod _mod;
	bool _isJJ = true;

	cLabel* _labelTlv = nullptr;
	cLabelEasy* _labelLv = nullptr;
	cLabelEasy* _labelTakelv = nullptr;
	cSprite* _sprite = nullptr;
public:
	// ÷∏’Î ’Ω∂∑
	std::function<bool(const sMod&)> onMod = nullptr;

	static const int c180;
};
