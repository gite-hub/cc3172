#include "sPoint.h"
#include "_inc.h"


const int sPoint::cInit = 0;
const int sPoint::cRemain = 0;

sPoint::sPoint()
{
	reset();
}



bool sPoint::reset(int initPoint /* = 0 */)
{
	// 体力
	body = initPoint;
	// 魔力
	mana = initPoint;
	// 力量
	str = initPoint;
	// 耐力
	dex = initPoint;
	// 敏捷
	agi = initPoint;
	// 剩余
	remain = 0;
	return true;
}


int& sPoint::get(ePoint e)
{
//	int* p = nullptr;
	switch (e)
	{
	case ePoint::body:
		return body;
//		break;
	case ePoint::mana:
		return mana;
//		break;
	case ePoint::str:
		return str;
//		break;
	case ePoint::dex:
		return dex;
//		break;
	case ePoint::agi:
		return agi;
//		break;
//	default:
//		break;
	}
	return remain;
//	ccc_box(((int)e));
}


bool sPoint::check(int lv)const
{
	return body + mana + str + dex + agi + remain == (lv * 10);
}


void sPoint::correct(int lv)
{
	reset(lv);
	remain = lv * 5;
}

void sPoint::correctRemain(int lv)
{
	remain = lv * 10 - (body + mana + str + dex + agi);
}

bool sPoint::add(ePoint e, bool onlyCheck)
{
	if (remain <= 0)
	{
		return false;
	}
	if (onlyCheck)
	{
		return true;
	}
	int& p = get(e);
	++(p);
	--remain;
	return true;
}


bool sPoint::sub(ePoint e, bool onlyCheck)
{
	int& p = get(e);
// 	if (p == nullptr)
// 	{
// 		return false;
// 	}
	if ((p) <= 0)
	{
		return false;
	}
	if (onlyCheck)
	{
		return true;
	}
	--(p);
	++remain;
	return true;
}


void sPoint::lvup(int per /* = 1 */)
{
	body += per;
	mana += per;
	str += per;
	dex += per;
	agi += per;
	remain += 5 * per;
}

bool sPoint::lvdown(bool onlyCheck, int per /* = 1 */)
{
	if (body + mana + str + dex + agi + remain < (per * 10))
	{
		return false;
	}
	std::vector<int*> ps =
	{
		&body,
		&mana,
		&str,
		&dex,
		&agi
	};
	std::sort(ps.begin(), ps.end(), [](const int* a, const int* b){return (*a) < (*b); });
	if (*(ps.front()) < per)
	{
		return false;
	}
	if (onlyCheck)
	{
		return true;
	}
	body -= per;
	mana -= per;
	str -= per;
	dex -= per;
	agi -= per;

	per = per * 5;
	if (per > remain)
	{
		per -= remain;
		remain = 0;
	}
	else
	{
		remain -= per;
		return true;
	}

	int* point;
	while (per > 0)
	{
		point = ps.back();
		if (per > *point)
		{
			per -= *point;
			remain = 0;
		}
		else
		{
			*point -= per;
			return true;
		}
	}
	return false;
//	ccc_box("sPoint::lvdown");
}



void sPoint::operator+=(const sPoint& point)
{
	body += point.body;
	mana += point.mana;
	str += point.str;
	dex += point.dex;
	agi += point.agi;
}

sPoint sPoint::operator+(const sPoint& point) const 
{
	sPoint p;
	p.body = body + point.body;
	p.mana = mana + point.mana;
	p.str = str + point.str;
	p.dex = dex + point.dex;
	p.agi = agi + point.agi;
	p.remain = remain;
	return p;
}



void sPoint::operator+=(int point)
{
	body += point;
	mana += point;
	str += point;
	dex += point;
	agi += point;
}

sPoint sPoint::operator+(int point) const 
{
	sPoint p;
	p.body = body + point;
	p.mana = mana + point;
	p.str = str + point;
	p.dex = dex + point;
	p.agi = agi + point;
	p.remain = remain;
	return p;
}


void sPoint::operator*=(int point)
{
	body *= point;
	mana *= point;
	str *= point;
	dex *= point;
	agi *= point;
	remain *= point;
}

sPoint sPoint::operator*(int point) const
{
	sPoint p;
	p.body = body * point;
	p.mana = mana * point;
	p.str = str * point;
	p.dex = dex * point;
	p.agi = agi * point;
	p.remain = remain * point;
	return p;
}

void sPoint::save()const
{
	sStream& sav = *cSave::getSave();
	sav << str << s_space << dex << s_space << body << s_space << mana << s_space << agi << s_space << remain << s_space;
}


void sPoint::load()
{
	sStream& sav = *cSave::getLoad();
	sav >> str >> dex >> body >> mana >> agi >> remain;
}
