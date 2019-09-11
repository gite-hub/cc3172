#pragma once
#include "sRole.h"
#include "cIndexCounter.h"

class cRole : public cUnique<sRole>
{
public:
	static cRole* getInstance();

	cRole();

	sRole* getHero();

	sRole* createRole(eMod e, const std::string& name, eMenpai menpai);

	sRole* getRole(eMod e, const std::string& name, eMenpai menpai);

	sRole* getRole(eMod e, eMenpai menpai);

	sRole* getRole(int unique);

private:
	sRole* _hero = nullptr;
};