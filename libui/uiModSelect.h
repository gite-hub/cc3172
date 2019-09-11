#pragma once
#include "uiPad.h"

class uiModSelect : public uiPad
{
public:
	CREATE_FUNC(uiModSelect);

protected:
	bool init();

	int _select;
	cSprite9* _spriteSelect = nullptr;
	std::vector<eMod> _mods;
public:
	std::function<void(eMod)> onSelect = nullptr;
};