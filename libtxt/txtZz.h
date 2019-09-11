#pragma once
#include "_inc.h"
#include "eMod.h"
#include "eSki.h"


class txtZz
{
public:
	enum class eAp
	{
		magicd,
		atk,
		magic,
		rand,
	};
	struct sZz
	{
		eAp ap;
		int takelv;
		int atk;
		int def;
		int hp;
		int mp;
		int speed;
		int avoid;
		int grow;
		std::vector<eSki> skis;
		sZz();
	};
	txtZz();
private:
	void init(eMod e, int takelv, eAp ap);
	void insert(int atk, int def, int hp, int mp, int speed, int evoid, int grow);
	void insert(eSki ski);
	void insert(eSki ski, eSki ski2);
	void insert(eSki ski, eSki ski2, eSki ski3);
	void insert(eSki ski, eSki ski2, eSki ski3, eSki ski4);
	void insert(eSki ski, eSki ski2, eSki ski3, eSki ski4, eSki ski5);
	void insert(eSki ski, eSki ski2, eSki ski3, eSki ski4, eSki ski5, eSki ski6);
	void insert(eSki ski, eSki ski2, eSki ski3, eSki ski4, eSki ski5, eSki ski6, eSki ski7);
	void correctSki();
	sZz* _zz;
	std::vector<eSki>* _skis;
protected:
	std::map<eMod, sZz> _zzs;
public:
	static const std::map<eMod, sZz>& getZzs();
};