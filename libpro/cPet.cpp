#include "cPet.h"

cPet* cPet::getInstance()
{
	static cPet* s_pet = new cPet();
	return s_pet;
}

cPet::cPet()
{
}


sPet* cPet::createPet(eMod e, const std::string& name /* = "" */)
{
	auto pet = new sPet();
	bool iszz = true;
	bool skill = true;
	const auto& zzs = txtZz::getZzs();
	const auto& it = zzs.find(e);
	if (it == zzs.end())
	{
		return nullptr;
	}
	const auto& pzz = it->second;
	pet->mod.setMod(e, 0);
	if (name.empty())
	{
		pet->name = txtMod::getMods().at(e).name;
	}
	else
	{
		pet->name = name;
	}
	if (iszz)
	{
		pet->zz = pzz;
	}
	if (skill)
	{
		pet->eskis = pzz.skis;
	}
	return pet;
}


sPet* cPet::getPet(eMod e, const std::string& name /* = "" */)
{
	auto pet = createPet(e, name);
	if (pet != nullptr)
	{
		insert(pet);
	}
	return pet;
}

sPet* cPet::getPet(int unique)
{
	return get(unique);
}

bool cPet::removePet(int unique)
{
	return remove(unique);
}
