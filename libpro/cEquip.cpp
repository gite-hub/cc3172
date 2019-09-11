#include "cEquip.h"
#include "_cc8.h"
#include "../libtxt/_cc8.h"

const int cEquip::c2 = 2;
const int cEquip::c4 = 4;

static int ccc_rand(int a, int b)
{
	return cc::random(a, b);
}
static float ccc_rand()
{
	return cc::gauss(5);
}

static int proAtk(int lv, int e)
{
	int v = 10 + lv * 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 6) + (lv)* e / 100;
}

static int proHit(int lv, int e)
{
	int v = 10 + lv * 7 / 2;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 5) + (lv * 6 / 5) * e / 100;
}

static int proDef(int lv, int e)
{
	int v = 5 + lv / 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 14) + (lv / 5) * e / 100;
}

static int proMp(int lv, int e)
{
	int v = 5 + lv;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 10) + (lv / 3) * e / 100;
}

static int proMana(int lv, int e)
{
	int v = 5 + lv * 6 / 5;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 9) + (lv * 2 / 5) * e / 100;
}

static int proHp(int lv, int e)
{
	int v = 10 + lv * 2;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 5) + (lv * 2 / 3) * e / 100;
}

static int proDef2(int lv, int e)
{
	int v = 10 + lv * 5 / 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 5) + (lv / 2) * e / 100;
}

static int proAgi(int lv, int e)
{
	int v = 5 + lv / 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 17) + (lv / 10) * e / 100;
}

static int proPointEx(int lv, int e)
{
	int v = 4 + lv / 8;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 10) * e / 100;
}

static int proSpeed(int lv, int e)
{
	return proPointEx(lv, e) * 7 / 10;
}

static int proAvoid(int lv, int e)
{
	return proPointEx(lv, e);
}

static int proRole(eIcon type, cEquip::eProPerty pro, int lv, int e)
{
	switch (pro)
	{
	case cEquip::eProPerty::hit:
		return proHit(lv, e);
	case cEquip::eProPerty::atk:
		return proAtk(lv, e);
	case cEquip::eProPerty::def:
		return cEquip::isClothes(type) ? proDef2(lv, e) : proDef(lv, e);
	case cEquip::eProPerty::mp:
		return proMp(lv, e);
	case cEquip::eProPerty::mtk:
	case cEquip::eProPerty::mef:
		return proMana(lv, e);
	case cEquip::eProPerty::hp:
		return proHp(lv, e);
	case cEquip::eProPerty::speed:
		return proSpeed(lv, e);
	case cEquip::eProPerty::avoid:
		return proAvoid(lv, e);
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
cEquip::sProperty::operator bool() const
{
	return pro != eProPerty::eNone && value > 0;
}

std::string cEquip::sProperty::toString(const std::string& space /*= " "*/) const
{
	return getName(pro) + space + cc::toString(value);
}

//////////////////////////////////////////////////////////////////////////
bool cEquip::isEquip(eIcon _type)
{
	return _type >= eIcon::equip0 && _type <= eIcon::equipEnd;
}

bool cEquip::isWeapon(eIcon _type)
{
	return _type == eIcon::weapon;
}

bool cEquip::isArmor(eIcon _type)
{
	return _type >= eIcon::eArm0 && _type <= eIcon::eArmEnd;
}


// bool cEquip::isHelmet(eIcon _type)
// {
// 	return _type == eIcon::helmet;
// }
// 
// bool cEquip::isNeck(eIcon _type)
// {
// 	return _type == eIcon::neck;
// }

bool cEquip::isBracer(eIcon _type)
{
	return _type == eIcon::bracer;
}

bool cEquip::isClothes(eIcon _type)
{
	return _type == eIcon::clothes;
}

// bool cEquip::isBelt(eIcon _type)
// {
// 	return _type == eIcon::belt;
// }

bool cEquip::isShoe(eIcon _type)
{
	return _type == eIcon::shoe;
}

//////////////////////////////////////////////////////////////////////////
void cEquip::sPro::apply(eIcon type)
{
	// 石头 打造才有
	pro = 0;
	pro1 = ccc_rand(0, 100);
	pro2 = ccc_rand(0, 100);
	float r = 1.0f;
	// 简易
	if (ccc_rand() < r)
	{
		easy = 1;
	}
	// 精致
	if (ccc_rand() < r)
	{
		delicate = 1;
	}
	// 溅射
	if (ccc_rand() < r)
	{
		spurting = 1;
	}
	// 嗜血幡
	if (ccc_rand() < r)
	{
		zhuiji = 1;
	}
	// 石头 +1
	// 特技 +1
	if (ccc_rand() < r)
	{
		special = ccc_rand((int)eSki::eSpecial0, (int)eSki::eSpecialEnd) - (int)eSki::eSpecial0 + 1;
	}
	// 追加 +1
	if (ccc_rand() < r)
	{
		std::vector<eSki> eskis;
		for (int eski = (int)eSki::eZhuijia0; eski <= (int)eSki::eZhuijiaEnd; ++eski)
		{
			eskis.push_back((eSki)eski);
		}
		eskis.push_back(eSki::hengsaoqianjun);
		eSki eski = eskis.at(ccc_rand(0, eskis.size() - 1));
		if (eski == eSki::hengsaoqianjun)
		{
			zhuijia = 0xF;
		}
		else
		{
			zhuijia = (int)eski - (int)eSki::eZhuijia0 + 1;
		}	
	}
}


void cEquip::apply(const sItem* equip, sPropertys& pros)
{
	eIcon type = equip->getType();
	std::vector<eProPerty> epros;
	if (isBracer(type))
	{
		epros.push_back(eProPerty::def);
		epros.push_back(eProPerty::mp);
	}
// 	else if (isNeck(type))
// 	{
// 		epros.push_back(eProPerty::mtk);
// 		epros.push_back(eProPerty::mef);
// 	}
	else if (isWeapon(type))
	{
		epros.push_back(eProPerty::hit);
		epros.push_back(eProPerty::atk);
	}
	else if (isClothes(type))
	{
		epros.push_back(eProPerty::def);
	}
	else if (isShoe(type))
	{
		epros.push_back(eProPerty::def);
		epros.push_back(eProPerty::hp);
	}
// 	else if (isShoe(type))
// 	{
// 		epros.push_back(eProPerty::def);
// 		epros.push_back(eProPerty::avoid);
// 		epros.push_back(eProPerty::speed);
// 	}
	if (epros.empty())
	{
		return;
	}

	sPro head;
	head.pro = equip->_pro;
	int lv = getLv(equip);
	int plv = lv - 10;
	int slv = lv / 10 + head.delicate;
	sProperty p;
	p.pro = epros.at(0);
	p.value = proRole(type, p.pro, lv - 10, head.pro1);
	pros.push_back(p);
	for (int k = 1, size = epros.size(); k < size; ++k)
	{
		p.pro = epros.at(k);
		p.value = proRole(type, p.pro, plv, head.pro2);
		pros.push_back(p);
	}
	if (head.stone > 0)
	{
		sPropertys pro2s;
		setStone((eStone)(head.stone - 1), pro2s);
		for (auto& p2 : pro2s)
		{
			p2.value *= slv;
		}
		for (auto& p2 : pro2s)
		{
			if (!p2)
			{
				continue;
			}
			for (auto& p1 : pros)
			{
				if (p1.pro == p2.pro)
				{
					p1.value += p2.value;
					p2.pro = eProPerty::eNone;
				}
			}
		}
		forv(pro2s, k)
		{
			const auto& p2 = pro2s.at(k);
			if (p2)
			{
				pros.push_back(p2);
			}
		}
	}
}


void cEquip::apply(const sItem* equip, sDescs& descs)
{
	sPro head;
	head.pro = equip->_pro;
	int lv = getLv(equip);
	sDesc d;
	d.text = cc8::cLv;
	d.text += " ";
	d.text += cc::toString(lv);
	d.color = s888::WHITE;
	descs.push(d);
	sPropertys pros;
	apply(equip, pros);
	// 01
	auto h = getHead(equip);
	int main = (isClothes(equip->_type) && h.stone != eStone::guangmang) ? 1 : 2;
	d.text.clear();
	for (int k = 0; k < main; ++k)
	{
		if (pros[k])
		{
			d.text += pros[k].toString("+") + " ";
		}
	}
	if (!d.text.empty())
	{
		d.text.pop_back();
		d.color = s888::YELLOW;
		descs.push(d);
	}
	if (h.stone != eStone::eNone)
	{
		d.text = cc8::cEquipXiangqian;
		d.text += ": ";
		d.text += txtIcon::getIcons().at(eIcon::stone).at((int)h.stone).name;
		d.color = s888::YELLOW;
		descs.push(d);
	}
	d.text.clear();
	for (int k = main, size = pros.size(); k < size; ++k)
	{
		if (pros[k])
		{
			d.text += pros[k].toString("+") + " ";
		}
	}
	if (!d.text.empty())
	{
		d.text.pop_back();
		d.color = s888::GREEN;
		descs.push(d);
	}
	eSki ski = h.specail;
	const auto& icons = txtIcon::getIcons().at(eIcon::ski);
	if (ski != eSki::eNone)
	{
		d.text = cc8::cEquipSpecial;
		d.text += ": ";
		d.text += icons.at((int)ski).name;
		d.color = s888(0x80, 0x80, 0xFF);
		descs.push(d);
	}
	if (head.easy != 0 || head.delicate != 0)
	{
		d.text = cc8::cEquipEffect;
		d.text += ":";
		if (head.easy)
		{
			d.text += " ";
			d.text += cc8::cEquipEasy;
		}
		if (head.delicate)
		{
			d.text += " ";
			d.text += cc8::cEquipDelicate;
		}
		d.color = s888(0x80, 0x80, 0xFF);
		descs.push(d);
	}
	if (head.spurting != 0 || head.zhuiji != 0)
	{
		d.text = cc8::cEquipFushi;
		d.text += ":";
		if (head.spurting)
		{
			d.text += " ";
			d.text += cc8::cEquipWuxinchaliu;
		}
		if (head.zhuiji)
		{
			d.text += " ";
			d.text += cc8::cEquipShixuefan;
		}
		d.color = s888(0x80, 0x80, 0xFF);
		descs.push(d);
	}
	ski = h.zhuijia;
	if (ski != eSki::eNone)
	{
		d.text = cc8::cEquipZhuijia;
		d.text += ": ";
		d.text += icons.at((int)ski).name + " (2" + cc8::cEquipZhuijia2 + ")";
		d.color = s888(0x80, 0x80, 0xFF);
		descs.push(d);
	}
}


int cEquip::getTakeLv(const sItem* equip)
{
	sPro head;
	head.pro = equip->_pro;
	int lv = getLv(equip);
	if (head.easy)
	{
		return lv - 5;
	}
	return lv;
}


int cEquip::getLv(const sItem* equip)
{
	return (equip->getId() + 1) * 10;
}


int cEquip::getIdx(eIcon type)
{
// 	if (isHelmet(type))
// 	{
// 		return 0;
// 	}
// 	if (isNeck(type))
// 	{
// 		return 1;
// 	}
	if (isWeapon(type))
	{
		return 1;
	}
	if (isBracer(type))
	{
		return 0;
	}
	if (isClothes(type))
	{
		return 2;
	}
// 	if (isBelt(type))
// 	{
// 		return 4;
// 	}
	if (isShoe(type))
	{
		return 3;
	}
	return cc::_1;
}

static std::vector<eIcon> icons = { eIcon::bracer, eIcon::weapon, eIcon::clothes, eIcon::shoe };
std::vector<eIcon>& cEquip::getTypes()
{
	return icons;
}


eIcon cEquip::getType(int idx)
{
	if (idx < 0 || idx >= c4)
	{
		return eIcon::eNone;
	}
	return icons.at(idx);
}

cEquip::sHead cEquip::getHead(const sItem* equip)
{
	sPro head;
	head.pro = equip->_pro;
	sHead h;
	h.isSpurting = head.spurting;
	h.isZhuiji = head.zhuiji;
	h.zhuijia = (head.zhuijia == 0xF) ? eSki::hengsaoqianjun : ((eSki)(head.zhuijia + (int)eSki::eZhuijia0 - 1));
	h.specail = (eSki)(head.special + (int)eSki::eSpecial0 - 1);
	h.stone = (eStone)(head.stone - 1);
	return h;
}

void cEquip::setStone(eIcon type, std::vector<eStone>& stones)
{
	stones.clear();
	if (isBracer(type))
	{
		stones.push_back(eStone::yueliang);
		stones.push_back(eStone::hongmanao);
		stones.push_back(eStone::taiyang);
	}
// 	else if (isNeck(type))
// 	{
// 		stones.push_back(eStone::shelizi);
// 		stones.push_back(eStone::feicui);
// 	}
	else if (isWeapon(type))
	{
		stones.push_back(eStone::hongmanao);
		stones.push_back(eStone::taiyang);		
		stones.push_back(eStone::shenmi);
	}
	else if (isClothes(type))
	{
		stones.push_back(eStone::yueliang);
		stones.push_back(eStone::guangmang);
		stones.push_back(eStone::shelizi);
		stones.push_back(eStone::feicui);
	}
	else if (isShoe(type))
	{
		stones.push_back(eStone::guangmang);
		stones.push_back(eStone::heibaoshi);
		stones.push_back(eStone::shenmi);
	}
// 	else if (isShoe(type))
// 	{
// 		stones.push_back(eStone::heibaoshi);
// 		stones.push_back(eStone::shenmi);
// 	}
}


static int getStoneValue(cEquip::eProPerty pro)
{
	// 舍利子改为 12法术伤害
	switch (pro)
	{
// 	case cEquip::eProPerty::eNone:
// 		break;
	case cEquip::eProPerty::atk:
		return 8;
	case cEquip::eProPerty::hit:
		return 25;
	case cEquip::eProPerty::def:
		return 12;
// 	case cEquip::eProPerty::mp:
// 		break;
	case cEquip::eProPerty::speed:
		return 8;
	case cEquip::eProPerty::hp:
		return 40;
	case cEquip::eProPerty::avoid:
		return 20;
	case cEquip::eProPerty::mtk:
		return 12;
	case cEquip::eProPerty::mef:
		return 12;
// 	default:
// 		break;
	}
	return 0;
}

void cEquip::setStone(eStone stone, sPropertys& pros)
{
	std::vector<eProPerty> epros;
	switch (stone)
	{
// 	case cEquip::eStone::eNone:
// 		break;
	case eStone::guangmang:
		epros.push_back(eProPerty::hp);
		break;
	case eStone::heibaoshi:
		epros.push_back(eProPerty::speed);
		break;
	case eStone::hongmanao:
		epros.push_back(eProPerty::hit);
		break;
	case eStone::shelizi:
		epros.push_back(eProPerty::mtk);
//		epros.push_back(eProPerty::mef);
		break;
	case eStone::taiyang:
		epros.push_back(eProPerty::atk);
		break;
	case eStone::yueliang:
		epros.push_back(eProPerty::def);
		break;
	case eStone::feicui:
		epros.push_back(eProPerty::mef);
		break;
	case eStone::shenmi:
		epros.push_back(eProPerty::avoid);
		break;
// 	default:
// 		break;
	}
	pros.resize(epros.size());
	forv(pros, k)
	{
		auto& p = pros.at(k);
		p.pro = epros.at(k);
		// (p.pro == eProPerty::mef && stone == eStone::feicui) ? 12 : 
		p.value = getStoneValue(p.pro);
	}
}

void cEquip::setStone(sItem* equip, eStone stone)
{
	sPro p;
	p.pro = equip->_pro;
	p.stone = (int)stone + 1;
	equip->_pro = p.pro;
}

int cEquip::getAtk(const sItems& equips, sStone* stone)
{
	int atk = 0;
	sPropertys pros;
	forr(equips, k)
	{
		auto pe = equips.at(k);
		if (pe == nullptr || pe->isValid() || !cEquip::isEquip(pe->getType()))
		{
			continue;
		}
		auto e = *pe;
		pros.clear();
		if (stone != nullptr)
		{
			cEquip::setStone(&e, stone->getStone(cEquip::getIdx(e.getType())));
		}
		cEquip::apply(&e, pros);
		forr(pros, k)
		{
			const auto& p = pros.at(k);
			if (!p)
			{
				continue;
			}
			if (p.pro == eProPerty::atk)
			{
				atk += p.value;
			}
		}
	}
	return atk;
}


std::string cEquip::getName(eProPerty epro)
{
	std::string str = "error";
	switch (epro)
	{
	case eProPerty::atk:
		str = cc8::cPropertyAtk;
		break;
	case eProPerty::hit:
		str = cc8::cPropertyHit;
		break;
	case eProPerty::def:
		str = cc8::cPropertyDef;
		break;
	case eProPerty::mp:
		str = cc8::cPropertyMp;
		break;
	case eProPerty::speed:
		str = cc8::cPropertySpeed;
		break;
	case eProPerty::hp:
		str = cc8::cPropertyHp;
		break;
	case eProPerty::avoid:
		str = cc8::cPropertyAvoid;
		break;
	case eProPerty::mtk:
		str = cc8::cPropertyMtk;
		break;
	case eProPerty::mef:
		str = cc8::cPropertyMef;
		break;
	}
	return str;
}
