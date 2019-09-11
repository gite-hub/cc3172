#include "cRole.h"

cRole* cRole::getInstance()
{
	static cRole* s_role = new cRole();
	return s_role;
}

cRole::cRole()
{
	_hero = getRole(eMod::hutouguai, eMenpai::eNone);
}

sRole* cRole::getHero()
{
	return _hero;
}


sRole* cRole::createRole(eMod e, const std::string& name, eMenpai menpai)
{
	auto role = new sRole();
	role->mod.setMod(e);
	role->name = name;
	role->menpai = menpai;
	return role;
}

sRole* cRole::getRole(eMod e, const std::string& name, eMenpai menpai)
{
	auto role = createRole(e, name, menpai);
	if (role != nullptr)
	{
		insert(role);
	}
	return role;
}

sRole* cRole::getRole(eMod e, eMenpai menpai)
{
	return getRole(e, txtMod::getMods().at(e).name, menpai);
}


sRole* cRole::getRole(int unique)
{
	return get(unique);
}
