#include "sZz.h"

sZz::sZz()
{
	reset();
}


void sZz::reset()
{
	atk = def = speed = avoid = hp = mana = grow = 0;
}


bool sZz::isValid()
{
	return atk > 0 && def > 0 && hp > 0 && mana > 0 && speed > 0 && avoid > 0 && grow > 0;
}


void sZz::correct()
{
	txtZz::sZz zz;
	atk = std::min(1680, std::max(zz.atk, atk));
	def = std::min(1680, std::max(zz.def, def));
	speed = std::min(1920, std::max(zz.speed, speed));
	avoid = std::min(1920, std::max(zz.avoid, avoid));
	hp = std::min(7200, std::max(zz.hp, hp));
	mana = std::min(3600, std::max(zz.mp, mana));
	grow = std::min(128, std::max(zz.grow, grow));
}



void sZz::operator=(const txtZz::sZz& zz)
{
	atk = zz.atk;
	def = zz.def;
	hp = zz.hp;
	mana = zz.mp;
	speed = zz.speed;
	avoid = zz.avoid;
	grow = zz.grow;
}


#pragma pack (push)
#pragma pack (1)
union sZzSaveLoad
{
	struct
	{
		u64 vint64;
		uint vint;
	};
	struct
	{
		u64 atk : 11;
		u64 def : 11;
		u64 hp : 14;
		u64 mag : 13;
		u64 speed : 11;
		u64 temp64 : 4;
		uint evoid : 11;
		uint grow : 8;
		uint temp : 13;
	};
};
#pragma pack (pop)


void sZz::save()const
{
	sZzSaveLoad zz;
	zz.atk = atk;
	zz.def = def;
	zz.hp = hp;
	zz.mag = mana;
	zz.speed = speed;
	zz.evoid = avoid;
	zz.grow = grow;

	sStream& sav = *cSave::getSave();
	sav << zz.vint << s_space << zz.vint64 << s_space;
}


void sZz::load()
{
	sStream& sav = *cSave::getLoad();
	sZzSaveLoad zz;
	sav >> zz.vint >> zz.vint64;

	atk = zz.atk;
	def = zz.def;
	hp = zz.hp;
	mana = zz.mag;
	speed = zz.speed;
	avoid = zz.evoid;
	grow = zz.grow;
}
