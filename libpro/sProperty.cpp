#include "sProperty.h"
#include "ccp.h"

sProperty::sProperty(bool pet)
{
	reset(pet);
}

sProperty::sProperty()
{
	reset(true);
}


void sProperty::reset(bool pet)
{
	ispet = pet;
	if (!pet)
	{
		equips.resize(cEquip::c4);
		std::fill(equips.begin(), equips.end(), nullptr);
	}
}

bool sProperty::isSki(eSki e)
{
	return ccc_find(eskis, e);
}


int sProperty::getSkiLv(eSki eski /* = eSki::eNone */) const
{
	return lv + xl.get(eXl::mtk);
}

bool sProperty::lvup(bool onlyCheck)
{
	return ccp::lvup(this, onlyCheck);
}


void sProperty::lvupEasy(int lv_)
{
	auto old = exp;
	for (int k = 0; k < lv_; ++k)
	{
		exp.add(sExp::getExp(k + lv + 1, ispet));
		lvup(false);
	}
	exp = old;
	ccp::fillHpMp(this);
}

void sProperty::save()const
{
	sUnique::save();
	mod.save(ispet);
	sStream& sav = *cSave::getSave();
	sav << (int)menpai << s_space << name << s_space << lv << s_space << hp << s_space << mp << s_space << ap << s_space;
	zz.save();
	point.save();
	forr(equips, k)
	{
		equips[k]->save(false);
	}
	sav << eskis.size() << s_space;
	forr(eskis, k)
	{
		sav << (int)eskis.at(k) << s_space;
	}
	// О­бщ
	sav << exp.union64 << s_space;
	zz.save();
}


void sProperty::load()
{
	sUnique::load();
	mod.load(ispet);
	sStream& sav = *cSave::getLoad();
	int e;
	sav >> e >> name >> lv >> hp >> mp >> ap;
	menpai = (eMenpai)e;
	zz.load();
	point.load();
	forr(equips, k)
	{
		equips[k]->load(false);
	}
	sav >> e;
	eskis.resize(e);
	forr(eskis, k)
	{
		sav >> e;
		eskis.at(k) = (eSki)e;
	}
	sav >> exp.union64;
	zz.load();
}