#pragma once
#include "_inc.h"

class uiMenu : public Node
{
public:
	CREATE_FUNC(uiMenu);

protected:
	bool init();

public:
	enum class eOperate { atk, act, achi, job, team, pack, sys, fri, visi };
	std::function<void(eOperate)> onOperate = nullptr;
	std::function<void()> onHiden = nullptr;
};