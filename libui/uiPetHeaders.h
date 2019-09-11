#pragma once
#include "_inc.h"
#include "ui/UIScrollView.h"

class uiPetHeaders : public ui::ScrollView
{
public:
	CREATE_FUNC(uiPetHeaders);
// 	static uiPetHeaders* create(const sPets& pets, int fight);
// 	static uiPetHeaders* create();

protected:
	bool init(/*const sPets& pets, int fight*/);

public:
	void load(const sPets& pets, int fight);

	void load(int fight);
protected:
	sPets _pets;
	int _select, _fight;
	cSprite9* _spriteSelect = nullptr;
	Sprite* _spriteFight = nullptr;

	cMenu* _menu = nullptr;
	std::vector<cButton*> _buttons;

public:
	static const int c4, cTagSprite, cTagFight;
	std::function<void(const sPet*, int)> onSelect = nullptr;
	std::function<bool(const sPets&, int, int&)> onRemove = nullptr;
};