#pragma once
#include "_inc.h"

class cScript
{
public:
	static cScript* getInstance();

	bool run(ulong head, const std::string& name, const std::string& script);
};







