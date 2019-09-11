#pragma once
#include "uiPad.h"

class uiState;
class uiAddpoint;
class uiSkill;
class uiXL;
class uiRole : public uiPad
{
public:
	static uiRole* create(sRole* role);

protected:
	bool init(sRole* role);

public:
	void load(sRole* role);

	uiState* getState() const { return _state; }

protected:
	void hide();

	sRole* _role = nullptr;

	uiState* _state = nullptr;
	uiAddpoint *_point = nullptr;
	uiSkill* _skill = nullptr;
	uiXL* _xl = nullptr;

public:
	std::function<void(sRole*)> onFill = nullptr;
	std::function<void(sRole*)> onHpMp = nullptr;
};