#include "ccp.h"
#include "cItem.h"

////////////////////////////////////////////////////////////////////////// 面板属性
void ccp::apply(sAttribute& attr, cEquip::eProPerty epro, int skilv)
{
	if (epro == cEquip::eProPerty::hp)
	{
		attr.hpMax.ori += skilv * 5;
		attr.hpMax.per += skilv;
		return;
	}
	if (epro == cEquip::eProPerty::mp)
	{
		attr.mpMax.per += skilv;
		return;
	}
	int3* a3 = nullptr;
	float base = 1.0f, exp = 0.02f;
	switch (epro)
	{
	case cEquip::eProPerty::eNone:
		break;
	case cEquip::eProPerty::atk:
		a3 = &attr.atk;
		break;
	case cEquip::eProPerty::hit:
		break;
	case cEquip::eProPerty::def:
		a3 = &attr.def;
		break;
	case cEquip::eProPerty::mp:
		break;
	case cEquip::eProPerty::speed:
		break;
	case cEquip::eProPerty::hp:
		break;
	case cEquip::eProPerty::avoid:
		a3 = &attr.avoid;
		base = 2.0f;
		break;
	case cEquip::eProPerty::mtk:
		a3 = &attr.mtk;
		base = 0.5f;
		exp = 0.01f;
		break;
	case cEquip::eProPerty::mef:
		a3 = &attr.mef;
		base = 0.5f;
		exp = 0.01f;
		break;
	default:
		break;
	}
	if (a3 != nullptr)
	{
		float ori = 0;
		for (int i = skilv; i > 0; --i)
		{
			ori += base + exp * i;
		}
		a3->ori += ori;
	}
}


void ccp::apply(sAttribute& attr, const sPoint& point)
{
	float _atk, _def, _hp, _mana, _mp, _speed, _evade, _hit;
	_atk = point.str/* * 7 / 9*/;
	_def = point.dex * 5 / 3;
	_hp = point.body * 5;
	_mana = point.mana * (7 + 3) + point.body * 3 + point.str * 4 + point.dex * 2;
	_mana /= 10;
	_mp = point.mana * 4;
	_speed = point.agi * (7 + 3) + (point.body + point.str + point.dex) * 2;
	_speed /= 10;
	_evade = point.agi;
	_hit = point.str * 7 / 3;

	attr.atk.ori += _atk;
	attr.def.ori += _def;
	attr.hpMax.ori += _hp;
	attr.mpMax.ori += _mp;
	attr.mtk.ori += _mana;
	attr.mef.ori += _mana;
	attr.speed.ori += _speed;
	attr.hit.ori += _hit;
	attr.avoid.ori += _evade;
}


void ccp::apply(sAttribute& attr, const sPoint& point, const sZz& zz, int lv)
{
	float _atk, _def, _hp, _mana, _mp, _speed, _evade, _hit;
	int _grow = zz.grow + 10;
	int mana = zz.mana * 3 / 2;
	_atk = lv * zz.atk * (1400 + 10 * _grow) / 750000;
	_atk += point.str * _grow / 100;

	_def = (lv * zz.def) * 19 / 7500;
	_def += (point.dex * _grow * 4) / 300;

	_hp = (lv * zz.hp * 3 / 2) / 1000;
	_hp += point.body * _grow * 6 / 100;

	_mana = lv * (mana + 1640) * (_grow + 100) / 75000;
	_mana += point.body * 3 + point.mana * (7 + 2) + point.str * 4 + point.dex * 2;
	_mana /= 10;

	_mp = lv * mana / 500 + _grow * point.mana * 3 / 100;

	_speed = zz.speed * point.agi / 1000;
	_evade = zz.avoid * point.agi / 300;

	_hit = _atk / 2;
	_hit += point.str * 5 / 2;

	attr.atk.ori += _atk;
	attr.def.ori += _def;
	attr.hpMax.ori += _hp;
	attr.mpMax.ori += _mp;
	attr.mtk.ori += _mana;
	attr.mef.ori += _mana;
	attr.speed.ori += _speed;
	attr.hit.ori += _hit;
	attr.avoid.ori += _evade;
}


void ccp::apply(sAttribute& attr, const cEquip::sPropertys& pros)
{
	int v;
	forr(pros, k)
	{
		const auto& p = pros.at(k);
		if (!p)
		{
			continue;
		}
		v = p.value;
		switch (p.pro)
		{
		case cEquip::eProPerty::eNone:
			break;
		case cEquip::eProPerty::atk:
			attr.atk.ori += v;
			break;
		case cEquip::eProPerty::hit:
			attr.hit.ori += v;
			attr.atk.ori += v / 3;
			break;
		case cEquip::eProPerty::def:
			attr.def.ori += v;
			break;
		case cEquip::eProPerty::mp:
			attr.mpMax.ori += v;
			break;
		case cEquip::eProPerty::speed:
			attr.speed.ori += v;
			break;
		case cEquip::eProPerty::hp:
			attr.hpMax.ori += v;
			break;
		case cEquip::eProPerty::avoid:
			attr.avoid.ori += v;
			break;
		case cEquip::eProPerty::mtk:
			attr.mtk.ori += v;
			break;
		case cEquip::eProPerty::mef:
			attr.mef.ori += v;
			break;
		default:
			break;
		}
	}
}


////////////////////////////////////////////////////////////////////////// 内置属性
void ccp::apply(sPropertyInfo& info, eMenpai menpai)
{
	switch (menpai)
	{
// 	case eMenpai::eNone:
// 		break;
// 	case eMenpai::eMenpai0:
// 		break;
	case eMenpai::physics:
		// 穿刺
		info.pierceRate.d1 += 5;
		// 吸血
		info.blood.rate.d1 += 25;
		info.blood.per.d1 += 10;
		// 反击
		info.counter.rate.d1 += 20;
		info.counter.per.d1 += 50;
		// 必杀
		info.criRate.d1 += 5;
		break;
	case eMenpai::magic:
		// 法术穿刺
		info.pierceRateMaigc.d1 += 5;
		// 魔之心
		info.damageMagic.per.d1 += 10;
		// 法术连击
		info.comboRateMagic.d1 += 10;
		// 法术暴击
		info.criRateMagic.d1 += 10;
		// 火甲术
		info.counterMagic.rate.d1 += 20;
		info.counterMagic.per.d1 += 100;
		break;
	case eMenpai::treat:
		// 神农
		info.damageCure.per.d1 += 10;
		info.damageCure.add.d1 += 64;
		// 慈悲
		info.criRateCure.d1 += 15;
		// 四法吸收
		{
			int v = 20;
			info.fire.rate.d1 += v;
			info.soil.rate.d1 += v;
			info.water.rate.d1 += v;
			info.thunder.rate.d1 += v;
		}
		break;
	case eMenpai::assist:
		// 药效
		info.damageCure.per.d2 += 10;
		info.damageCure.add.d2 += 64;
		// 法术反弹
		info.stabMagic.per.d1 += 25;
		info.stabMagic.rate.d1 += 20;
		// 法术躲避
		info.hitRateMagic.dper += 10;
		// 感知
		info.hide.d2 += cFF;
		break;
// 	case eMenpai::eMenpaiEnd:
// 		break;
// 	default:
// 		break;
	}
}


void ccp::apply(sPropertyInfo& info, const sXl& xl)
{
	info.damage.per.d1 += xl.lvs[0] * 2;
	info.damage.per.d2 += xl.lvs[0] * 2;
	info.damage.add.d1 += xl.lvs[1] * 5;
	info.damage.add.d2 += xl.lvs[1] * 5;

	info.damageMagic.per.d1 += xl.lvs[2] * 2;
	info.damageMagic.per.d2 += xl.lvs[2] * 2;
	info.damageMagic.add.d1 += xl.lvs[3] * 5;
	info.damageMagic.add.d2 += xl.lvs[3] * 5;

	info.hitRateSeal.d1 += xl.lvs[2] * 3 / 2;
	info.hitRateSeal.d2 += xl.lvs[3] * 3 / 2;
}


////////////////////////////////////////////////////////////////////////// 装备
void ccp::apply(sPropertys& pr, const sItems& equips, sStone* stone)
{
	pr.specials.clear();
	std::map<eSki, int> zjMap;
//	pr.zhuijias.rate = 0;

//	bool isZhuijia;
	eSki eski;
	cEquip::sPropertys pros;
	cEquip::sHead head;
	forr(equips, k)
	{
		auto pe = equips.at(k);
		if (pe == nullptr || !pe->isValid() || !cEquip::isEquip(pe->getType()))
		{
			continue;
		}
		auto e = *pe;
		if (stone != nullptr)
		{
			cEquip::setStone(&e, stone->getStone(cEquip::getIdx(e.getType())));
		}
		pros.clear();
		cEquip::apply(&e, pros);
		apply(pr.attr, pros);
		
		head = cEquip::getHead(&e);
		eski = head.zhuijia;
		if (eski != eSki::eNone)
		{
			const auto& it = zjMap.find(eski);
			if (it == zjMap.end())
			{
				zjMap.insert(std::make_pair(eski, 1));
			}
			else
			{
				++it->second;
			}
		}
		eski = head.specail;
		if (eski != eSki::eNone && !ccc_find(pr.specials, eski))
		{
			pr.specials.push_back(eski);
		}
		if (head.isSpurting)
		{
			++pr.spurting;
		}
		if (head.isZhuiji)
		{
			++pr.zhuiji;
		}
	}

	auto& zjs = pr.zhuijias;
	for (const auto& it : zjMap)
	{
		if (it.second >= cEquip::c2)
		{
			ccp::sZhuijia zj;
			zj.e = it.first;
			zj.lvGap = it.second - cEquip::c2;
			zj.rate = 14 + zj.lvGap * 8;
			zj.lvGap = (zj.lvGap - 1) * 10;
			zjs.push_back(zj);
		}
	}
}


////////////////////////////////////////////////////////////////////////// 技能
void ccp::apply(sPropertyInfo& info, sAttribute& attr, eSki eski)
{
	switch (eski)
	{
	case eSki::fanji:
		info.counter.rate.d1 += 35;
		info.counter.per.d1 += 100;
		break;
	case eSki::fanzhen:
		info.stab.rate.d1 += 35;
		info.stab.per.d1 += 50;
		break;
	case eSki::xixue:
		info.blood.rate.d1 += 100;
		info.blood.per.d1 += 20;
		break;
	case eSki::lianji:
		info.comboRate.d1 += 60;
		info.damage.per.d1 -= 20;
		break;
	case eSki::bisha:
		info.criRate.d1 += 20;
		break;
	case eSki::yinshen:
		info.hide.d1 += 3;
		break;
	case eSki::touxi:
		info.stab.rate.d2 += cFF;
		info.counter.rate.d2 += cFF;
		break;
	case eSki::mozhixin:
		info.damageMagic.per.d1 += 20;
		break;
	case eSki::fashulianji:
		info.comboRateMagic.d1 += 25;
		break;
	case eSki::fashubaoji:
		info.criRateMagic.d1 += 20;
		break;
	case eSki::shenyou:
		info.gad.rate.d1 += 30;
		info.gad.per.d1 += 100;
		break;
	case eSki::ganzhi:
		info.hide.d2 += cFF;
		break;
	case eSki::minjie:
		attr.speed.per += 20;
		break;
	case eSki::chidun:
		attr.speed.per -= 50;
		break;
	case eSki::leixishou:
		info.thunder.rate.d2 += 30;
		info.thunder.per.d2 += 30;
		break;
	case eSki::tuxishou:
		info.soil.rate.d2 += 30;
		info.soil.per.d2 += 30;
		break;
	case eSki::huoxishou:
		info.fire.rate.d2 += 30;
		info.fire.per.d2 += 30;
		break;
	case eSki::shuixishou:
		info.water.rate.d2 += 20;
		info.water.per.d2 += 20;
		break;
	}
}

void ccp::apply(std::set<eSki>& mutexs, const eSkis& eskis)
{
	forr(eskis, k)
	{
		const auto& e = eskis.at(k);
		if (e == eSki::chidun)
		{
			mutexs.insert(eSki::minjie);
		}
	}
}


////////////////////////////////////////////////////////////////////////// 主属性
void ccp::apply(sPropertys& pros, const sProperty* pro)
{
	sPropertyInfo& info = pros.info;
	sAttribute& attr = pros.attr;
	info.resetCri();
	attr.reset();

	if (pro->ispet)
	{
		apply(pros, pro->equips, nullptr);
		// 属性
		apply(attr, pro->point, pro->zz, pro->lv);
		// 内丹
	}
	else
	{
		auto r = dynamic_cast<const sRole*>(pro);
		apply(pros, pro->equips, r == nullptr ? nullptr : &((sRole*)r)->stone);
		// 属性
		apply(attr, pro->point);
		// 师门技能
		if (r != nullptr)
		{
			const auto& skilvs = r->skilvs;
			forv(skilvs, k)
			{
				apply(attr, (cEquip::eProPerty)k, skilvs.at(k));
			}
		}
		// 门派特色
		apply(info, pro->menpai);
	}
	// 辅助
	// 修炼
	apply(info, pro->xl);
	// 被动技能
	std::set<eSki> mutexs;
	apply(mutexs, pro->eskis);
	for (const auto& ski : pro->eskis)
	{
		if (mutexs.find(ski) == mutexs.end())
		{
			apply(info, attr, ski);
		}
	}
}



void ccp::fillHpMp(sProperty* pro)
{
	sPropertys pros;
	apply(pros, pro);
	pro->hp = pros.attr.hpMax;
	pro->mp = pros.attr.mpMax;
}


bool ccp::lvup(sProperty* pro, bool onlyCheck)
{
	if (pro->lv >= (pro->ispet ? ccp::lv79 : ccp::lv69))
	{
		return false;
	}

	int expMax = sExp::getExp(pro->lv + 1, pro->ispet);

	if (pro->exp < expMax)
	{
		return false;
	}

	if (!onlyCheck)
	{
		++pro->lv;
		pro->exp.sub(expMax);
		pro->point.lvup();
	}
	return true;
}


bool ccp::lvdown(sProperty* pro, bool onlyCheck)
{
	if (pro->lv <= 0)
	{
		return false;
	}
	forr(pro->equips, k)
	{
		const auto& e = pro->equips[k];
		if (e->getCount() != 1)
		{
			continue;
		}
		if (cEquip::getTakeLv(e) >= pro->lv)
		{
			return false;
		}
	}
	if (!pro->point.lvdown(true))
	{
		return false;
	}
	if (!onlyCheck)
	{
		pro->point.lvdown(false);
		pro->exp.add(sExp::getExp(pro->lv, pro->ispet));
		--pro->lv;
	}
	return true;
}


bool ccp::lvdown(sRole* role)
{
	int xlv = sXl::getLv(role->lv);
	std::vector<sXl*> xls = { &role->xl, &role->xlbb };
	for (auto& pXl : xls)
	{
		auto& xl = *pXl;
		forr(xl.lvs, k)
		{
			while (xl.lvs[k] > xlv)
			{
				if (xl.lvdown(k, false))
				{
					role->money.add(sXl::c2000);
				}
			}
		}
	}

	for (auto& skilv : role->skilvs)
	{
		while (skilv > role->lv + cSki::cGap)
		{
			role->exp.add(cSki::getExp(skilv));
			role->money.add(cSki::getMoney(skilv));
			--skilv;
		}
	}

	if (!role->setPet(role->fight, true))
	{
		role->unPet();
	}
	return true;
}


bool ccp::addSki(eSkis& eskis, eMenpai mp)
{
	if (mp == eMenpai::eNone)
	{
		return false;
	}
	for (int e = (int)txtSki::get0(mp), end = (int)txtSki::getEnd(mp); e <= end; ++e)
	{
		eskis.push_back((eSki)e);
	}
	return true;
}


bool ccp::addSki(eSkis& eskis, eSki eski, int idx /* = cFF */)
{
	bool isSame = ccc_find(eskis, eski);
	if (isSame)
	{
		return false;
	}
	int size = eskis.size();
// 	if (size <= 2 || (size == 3 && cc::random() < 0.2f))
// 	{
// 		eskis.push_back(eski);
// 		return true;
// 	}
// 	eskis.at(cc::random(0, size - 1)) = eski;
// 	return true;

	// 替换和添加
	if (idx >= size)
	{
		eskis.push_back(eski);
		return true;
	}
	eskis.at(idx) = eski;
	return true;
}

static int compose(int z1, int z2, int zi)
{
	int m = std::min(z1, z2);
	z2 = std::max(z1, z2);
	z1 = m;
	m = (z1 + z2) / 2;
	int m1 = z1 - zi / 2;
	int m2 = z2 + zi;
	zi = std::max(m - m1, m2 - m);
	zi = m - zi + cc::gauss() * zi * 2;
	return zi;
}
static void compose(const sZz& z1, const sZz& z2, sZz& z)
{
	z.atk = compose(z1.atk, z2.atk, 128);
	z.def = compose(z1.def, z2.def, 128);
	z.hp = compose(z1.hp, z2.hp, 256);
	z.mana = compose(z1.mana, z2.mana, 128);
	z.speed = compose(z1.speed, z2.speed, 128);
	z.avoid = compose(z1.avoid, z2.avoid, 128);
	z.grow = compose(z1.grow, z2.grow, 2);
	z.correct();
}
sPet* ccp::compose(const sPet* pet1, const sPet* p2)
{
	sPet* p1 = (sPet*)pet1;
	if (cc::random() < 0.5f)
	{
		p1->mod = p2->mod;
	}
	sZz zz;
	compose(p1->zz, p2->zz, zz);
	p1->zz = zz;

	auto eskis = p1->eskis;	
	p1->eskis.clear();
	forv(p2->eskis, k)
	{
		addSki(eskis, p2->eskis.at(k));
	}
	while (!eskis.empty())
	{
		const auto& it = eskis.begin() + cc::random(0U, eskis.size() - 1);
		p1->eskis.push_back(*it);
		eskis.erase(it);
	}
	eskis = p1->eskis;
	p1->eskis.clear();
	for (int k = 0, size = std::min(4U, eskis.size());  k <  4; ++k)
	{
		p1->eskis.push_back(eskis.back());
		eskis.pop_back();
	}
	// 独立概率
	forr(eskis, k)
	{
		if (cc::random() < 0.5f)
		{
			p1->eskis.push_back(eskis.at(k));
		}
	}
	eskis = p1->eskis;
	std::sort(eskis.begin(), eskis.end());
	p1->eskis = eskis;
	p1->lv = 0;
	p1->point = sPoint();
	p1->name = txtMod::getMods().at(p1->mod.e).name;
	return p1;
}