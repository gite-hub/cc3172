#include "sMod.h"
#include "cEquip.h"

void sMod::setMod(eMod emod)
{
	setMod(emod, 0);
}

void sMod::setMod(eMod emod, int jdx_)
{
	if (emod == eMod::eNone)
	{
		return;
	}
	e = emod;
	const auto& m = txtMod::getMods().at(e);
	dyes.reset(m.parts.size());
	dyes.resetZero();

	setJdx(jdx_, m.jjs.size());
}

void sMod::setJdx(int jdx_)
{
	if (e == eMod::eNone)
	{
		return;
	}
	setJdx(jdx_, txtMod::getMods().at(e).jjs.size());
}

void sMod::setJdx(int jdx_, int max)
{
	if (jdx_ < 0 || jdx_ >= max)
	{
		jdx_ = 0;
	}
	jdx = jdx_;
}

void sMod::apply(sActs& sps, bool onMap, bool shadow) const
{
	const auto& m = txtMod::getMods().at(e);
	std::vector<txtAction::sAction> acts;
	std::vector<ulong> cids;
	const auto& jjs = m.jjs.at(jdx);
	forv(jjs, k)
	{
		const auto& p = m.parts.at(jjs.at(k));
		acts.push_back(onMap ? p.maps : p.acts);
		cids.push_back(p.color);
	}
	sps.clear();
	std::vector<sSp> sp;
	if (shadow)
	{
		sSp _sp;
		_sp.uid = ccu::uShadow;
		sp.push_back(_sp);
	}
	for (const auto& a : acts.at(0))
	{
		sps.insert(std::make_pair(a.first, sp));
	}
	sSp spMatrixs;
	forv(acts, k)
	{
		const auto& act = acts.at(k);
		const auto& cid = cids.at(k);
		const auto& dye = dyes.get(jjs.at(k));
		cDye::toMatrixs(spMatrixs.matrixs, cid, dye);
		for (const auto& a : act)
		{
			if (a.second == cSp::c0)
			{
				continue;
			}
			spMatrixs.uid = a.second;
			sps.at(a.first).push_back(spMatrixs);
		}
	}
	if (!onMap)
	{
		if (sps.find(eAct::atk2) == sps.end())
		{
			sps.insert(std::make_pair(eAct::atk2, sps.at(eAct::atk)));
		}
	}
}


void sMod::apply(txtAction::sAction& heads, bool sound) const
{
	const auto& m = txtMod::getMods().at(e);
	heads = sound ? m.sound : m.head;
	if (sound && heads.at(eAct::eAtk2) == cSp::c0)
	{
		heads.at(eAct::eAtk2) = heads.at(eAct::eAtk);
	}
	else if (!sound && heads.at(eAct::head) == cSp::c0)
	{
		heads.at(eAct::head) = heads.at(eAct::dialog);
	}
}


static txtAction::sAction s_heads, s_sounds;
static sMod::sActs s_acts, s_mapActs, s_shadowActs, s_shadowMaps;
void sMod::apply()const
{
	apply(s_heads, false);
	apply(s_sounds, true);
	apply(s_mapActs, true, false);
	apply(s_acts, false, false);
	apply(s_shadowMaps, true, true);
	apply(s_shadowActs, false, true);
}

ulong sMod::get(eAct eact) const
{
	if (eact == eAct::head || eact == eAct::dialog)
	{
		return s_heads.at(eact);
	}
	return s_sounds.at(eact);
}



sSps sMod::get(eAct eact, bool shadow) const
{
	if (eact == eAct::stand || eact == eAct::walk)
	{
		return shadow ? s_shadowMaps.at(eact) : s_mapActs.at(eact);
	}
	return shadow ? s_shadowActs.at(eact) : s_acts.at(eact);
}


sMod::operator bool() const
{
	return e != eMod::eNone;
}

void sMod::save(bool pet) const
{
	sStream& sav = *cSave::getSave();
	sav << (int)e << jdx << s_space;
	dyes.save();
}


void sMod::load(bool pet)
{
	sStream& sav = *cSave::getLoad();
	int n;
	sav >> n >> jdx;
	e = (eMod)n;
	dyes.load();
}
