#include "sRole.h"
#include "ccp.h"
#include "cItem.h"
#include "cPet.h"
#include "cRole.h"

sRole::sRole() : sProperty(false)
{
	skilvs.resize(ccp::main7);
	std::fill(skilvs.begin(), skilvs.end(), cSki::cGap);

	items.resize(cItem::c20);
	std::fill(items.begin(), items.end(), nullptr);
	stores.resize(cItem::c20);
	std::fill(stores.begin(), stores.end(), nullptr);
}


int sRole::getSkiLv(eSki eski /* = eSki::eNone */) const
{
	if (menpai == eMenpai::eNone || !txtSki::isMenpai(eski, menpai))
	{
		return sProperty::getSkiLv(eski);
	}
	int idx = (int)eski - (int)txtSki::get0(menpai);
	return skilvs.at(idx) + xl.get(eXl::mtk);
}


bool sRole::addPet(sPet* pet)
{
	if (pet == nullptr)
	{
		return false;
	}
	pets.push_back(pet);
	return true;
}

void sRole::unPet()
{ 
	fight = cc::_1;
}

static bool isValid(const sPets& pets, int index)
{
	return index >= 0 && index < pets.size();
}

bool sRole::removePet(int index, bool del)
{
	if (!isValid(pets, index))
	{
		return false;
	}
	if (del)
	{
		cPet::getInstance()->removePet(pets.at(index)->unique);
	}
	pets.erase(pets.begin() + index);
	if (fight == index)
	{
		fight = cc::_1;
	}
	else if (fight > index)
	{
		--fight;
	}
	return true;
}

sPet* sRole::getPet(int index)
{
	if (!isValid(pets, index))
	{
		return nullptr;
	}
	return pets.at(index);
}


sPet* sRole::getPet()
{
	return getPet(fight);
}


bool sRole::setPet(int fig, bool onlyCheck)
{
	if (!isValid(pets, fig))
	{
		return false;
	}
	const auto& p = pets.at(fig);
	if (p->lv > lv + ccp::lvGap || txtZz::getZzs().at(p->mod.e).takelv > lv)
	{
		return false;
	}
	if (!onlyCheck)
	{
		fight = fig;
	}
	return true;
}

bool sRole::isControllabel() const
{
	return this == cRole::getInstance()->getHero();
}

bool sRole::isTeam() const
{
	return false;
}


void sRole::save()const
{
	sProperty::save();
	sStream& sav = *cSave::getSave();
	sav << money.union64 << s_space;
	forr(skilvs, k)
	{
		sav << skilvs.at(k) << s_space;
	}
	stone.save();
	xl.save();
	xlbb.save();
	sav << items.size() << s_space;
	forr(items, k)
	{
		items.at(k)->save(false);
	}
	sav << stores.size() << s_space;
	forr(stores, k)
	{
		stores.at(k)->save(false);
	}
	sav << pets.size() << s_space;
	forr(pets, k)
	{
		pets.at(k)->save();
	}
	sav << fight << s_space;
}

void sRole::load()
{
	sProperty::load();
	sStream& sav = *cSave::getLoad();
	sav >> money.union64;
	forr(skilvs, k)
	{
		sav >> skilvs.at(k);
	}
	stone.load();
	xl.load();
	xlbb.load();
	sav >> fight;
	items.resize(fight);
	forr(items, k)
	{
		items.at(k)->load(false);
	}
	sav >> fight;
	stores.resize(fight);
	forr(stores, k)
	{
		stores.at(k)->load(false);
	}
	sav >> fight;
	pets.resize(fight);
	forr(pets, k)
	{
		pets.at(k) = new sPet();
		pets.at(k)->load();
	}
	sav >> fight;
}
