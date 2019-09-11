#include "sStone.h"
#include "cEquip.h"

static std::map<eIcon, std::vector<eStone>> tables;
sStone::sStone()
{
	idxs.resize(cEquip::c4);
	std::fill(idxs.begin(), idxs.end(), 0);
	if (tables.empty())
	{
		std::vector<eStone> stones;
		for(int k = 0; k < cEquip::c4; ++k)
		{
			auto first = cEquip::getType(k);
			cEquip::setStone(first, stones);
			tables.insert(std::make_pair(first, stones));
		}
	}
}

eStone sStone::correct(int idx, bool add)
{
	const auto& stones = tables.at(cEquip::getType(idx));
	auto& i = idxs.at(idx);
	if (add)
	{
		++i;
	}
	if (i >= stones.size())
	{
		i = 0;
	}
	return stones.at(i);
}


void sStone::correct()
{
	forv(idxs, k)
	{
		correct(k, false);
	}
}



eStone sStone::getStone(int idx)
{
	if (idx < 0 || idx >= cEquip::c4)
	{
		return eStone::eNone;
	}
	return correct(idx, false);
}

eStone sStone::switchStone(int idx)
{
	if (idx < 0 || idx >= cEquip::c4)
	{
		return eStone::eNone;
	}
	return correct(idx, true);
}


void sStone::save() const
{
	sStream& sav = *cSave::getSave();
	forr(idxs, k)
	{
		sav << idxs.at(k) << s_space;
	}
}

void sStone::load()
{
	sStream& sav = *cSave::getLoad();
	forr(idxs, k)
	{
		sav >> idxs.at(k);
	}
	correct();
}
