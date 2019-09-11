#include "txtZz.h"

void txtZz::init(eMod e, int takelv, eAp ap)
{
	_zz = &_zzs.at(e);
	_zz->takelv = takelv;
	_zz->ap = ap;
	_skis = &_zz->skis;
}

void txtZz::insert(int atk, int def, int hp, int mp, int speed, int evoid, int grow)
{
	_zz->atk = atk;
	_zz->def = def;
	_zz->hp = hp;
	_zz->mp = mp;
	_zz->speed = speed;
	_zz->avoid = evoid;
	_zz->grow = grow;
}

void txtZz::insert(eSki ski)
{
	_skis->push_back(ski);
	correctSki();
}
void txtZz::insert(eSki ski, eSki ski2)
{ 
	insert(ski);
	_skis->push_back(ski2);
	correctSki();
}
void txtZz::insert(eSki ski, eSki ski2, eSki ski3)
{
	insert(ski, ski2);
	_skis->push_back(ski3);
	correctSki();
}
void txtZz::insert(eSki ski, eSki ski2, eSki ski3, eSki ski4)
{
	insert(ski, ski2, ski3); 
	_skis->push_back(ski4);
	correctSki();
}
void txtZz::insert(eSki ski, eSki ski2, eSki ski3, eSki ski4, eSki ski5)
{
	insert(ski, ski2, ski3, ski4); 
	_skis->push_back(ski5);
	correctSki();
}
void txtZz::insert(eSki ski, eSki ski2, eSki ski3, eSki ski4, eSki ski5, eSki ski6)
{
	insert(ski, ski2, ski3, ski4, ski5);
	_skis->push_back(ski6);
	correctSki();
}
void txtZz::insert(eSki ski, eSki ski2, eSki ski3, eSki ski4, eSki ski5, eSki ski6, eSki ski7)
{
	insert(ski, ski2, ski3, ski4, ski5, ski6);
	_skis->push_back(ski7);
	correctSki();
}

void txtZz::correctSki()
{
	return;
	auto& ski = _skis->back();
}

txtZz::sZz::sZz()
{
	takelv = 0;
	atk = 512;
	def = 512;
	hp = 1024;
	mp = 1024;
	speed = 512;
	avoid = 512;
	grow = 64;
}

txtZz::txtZz()
{
	{
		sZz zz;
		for (int e = (int)eMod::e0; e <= (int)eMod::eEnd; ++e)
		{
			_zzs.insert(std::make_pair((eMod)e, zz));
		}
	}
	// ÅÝÅÝ(ÉÆ¶ñÓÐ±¨)
	init(eMod::paopao, 5, eAp::atk);
	insert(1400, 1400, 4500, 2500, 1400, 1200, 125);
	insert(eSki::fanji, eSki::shaneyoubao, eSki::minjie);
	// °×Ôó(ËÀÍöÕÙ»½)
	init(eMod::baize, 5, eAp::atk);
	insert(1400, 1400, 4500, 2500, 1400, 1200, 125);
	insert(eSki::siwangzhaohuan, eSki::fanji);
	// Ð¡Ïó(·¨Êõ·ÀÓù)
	init(eMod::xiaoxiang, 5, eAp::magic);
	insert(1400, 1400, 4500, 2500, 1400, 1200, 125);
	insert(eSki::fashufangyu, eSki::shuixishou, eSki::fanzhen, eSki::shuigong);
	// Áù¶úâ¨ºï(Á¦Åü»ªÉ½)
	init(eMod::liuermihou, 5, eAp::atk);
	insert(1400, 1400, 4500, 2500, 1400, 1200, 125);
	insert(eSki::lipihuashan, eSki::taishanyading);
	// º£Ã«³æ
	init(eMod::haimaochong, 5, eAp::atk);
	insert(1555, 972, 2592, 1296, 1425, 1296, 103);
	insert(eSki::fanzhen, eSki::bisha);
	// ÕÂÓã
	init(eMod::zhangyu, 5, eAp::atk);
	insert(1555, 907, 2592, 1296, 1425, 1296, 103);
	insert(eSki::lianji, eSki::xixue, eSki::shuixishou);
	// Àê
	init(eMod::li, 5, eAp::atk);
	insert(1555, 972, 3110, 1296, 1490, 1425, 104);
	insert(eSki::touxi, eSki::bisha);
	// Ò°Öí
	init(eMod::yezhu, 5, eAp::atk);
	insert(1231, 1231, 4147, 1360, 1231, 1296, 104);
	insert(eSki::ganzhi, eSki::fanji);
	// É½Ôô
	init(eMod::shangzei, 5, eAp::atk);
	insert(1166, 1296, 3888, 1296, 1296, 1425, 104);
	insert(eSki::touxi, eSki::minjie);
	// Ç¿µÁ
	init(eMod::qiangdao, 5, eAp::atk);
	insert(1360, 1360, 3564, 1490, 1296, 1296, 103);
	insert(eSki::lianji, eSki::liehuo);
	// »¤ÎÀ
	init(eMod::huwei, 5, eAp::atk);
	insert(1231, 1101, 2916, 1944, 1296, 1296, 97);
	insert(eSki::fanji, eSki::bisha);
	// ÷¼÷Ã¹Ö
	init(eMod::kulouguai, 15, eAp::atk);
	insert(1296, 1296, 3240, 1296, 1296, 1620, 105);
	insert(eSki::leixishou, eSki::fanzhen);
	// »¨Ñý
	init(eMod::huayao, 15, eAp::magic);
	insert(1101, 1555, 4082, 1555, 1231, 1231, 107);
	insert(eSki::ganzhi, eSki::luoyan, eSki::tuxishou);
	// ¶þ¹þ
	init(eMod::erha, 25, eAp::atk);
	insert(1555, 1036, 3888, 1296, 1620, 1581, 104);
	insert(eSki::lianji, eSki::touxi);
	// Ò°¹í
	init(eMod::yegui, 25, eAp::atk);
	insert(1425, 1425, 4536, 1296, 1231, 1360, 104);
	insert(eSki::tuxishou, eSki::xixue, eSki::minjie);
	// Ïº±ø
	init(eMod::xiabing, 25, eAp::atk);
	insert(1296, 1490, 5184, 2592, 1166, 1555, 106);
	insert(eSki::bisha, eSki::fanji, eSki::shuixishou);
	// Ð·½«
	init(eMod::xiejiang, 25, eAp::atk);
	insert(1425, 1296, 5508, 2462, 1296, 1296, 107);
	insert(eSki::lianji, eSki::fanji, eSki::shuixishou);
	// ½©Ê¬
	init(eMod::jiangshi, 35, eAp::atk);
	insert(1555, 1166, 4665, 2592, 1296, 1490, 109);
	insert(eSki::tuxishou, eSki::xixue, eSki::chidun);
	// Å£Í·
	init(eMod::niutou, 35, eAp::atk);
	insert(1425, 1425, 3888, 1944, 1555, 1296, 110);
	insert(eSki::bisha, eSki::touxi, eSki::fanzhen);
	// ÂíÃæ
	init(eMod::mamian, 35, eAp::atk);
	insert(1425, 1425, 3888, 1944, 1555, 1296, 109);
	insert(eSki::bisha, eSki::touxi, eSki::fanji);
	// À×ÄñÈË
	init(eMod::leiniaoren, 45, eAp::magicd);
	insert(1296, 1296, 4536, 2073, 1555, 1231, 117);
	insert(eSki::leiji, eSki::benleizhou, eSki::leixishou);
	// ÈðÊÞ
	init(eMod::ruishou, 45, eAp::magic);
	insert(1231, 1360, 3888, 2592, 1490, 1296, 117);
	insert(eSki::taishanyading, eSki::fanzhen, eSki::mozhixin);
	// Ìì±ø
	init(eMod::tianbing, 55, eAp::atk);
	insert(1425, 1620, 5508, 2397, 1425, 1425, 117);
	insert(eSki::bisha, eSki::fanji, eSki::ganzhi);
	// Ìì½«
	init(eMod::tianjiang, 55, eAp::atk);
	insert(1490, 1231, 5184, 2527, 1490, 1296, 118);
	insert(eSki::lianji, eSki::fanji, eSki::minjie);
	// µØÓüÕ½Éñ
	init(eMod::diyuzhanshen, 55, eAp::rand);
	insert(1620, 1555, 4860, 1944, 1166, 1620, 115);
	insert(eSki::lianji, eSki::taishanyading, eSki::fanzhen, eSki::mozhixin);
	// ·ï»Ë
	init(eMod::fenghuang, 65, eAp::magic);
	insert(1296, 1555, 4536, 2592, 1684, 1425, 122);
	insert(eSki::huoxishou, eSki::diyuliehuo, eSki::shenyou);
	// òÔÁú
	init(eMod::jiaolong, 65, eAp::rand);
	insert(1555, 1555, 4924, 3240, 1296, 1425, 122);
	insert(eSki::shuimanjinshan, eSki::shuixishou, eSki::ganzhi);
};



const std::map<eMod, txtZz::sZz>& txtZz::getZzs()
{
	static txtZz s_zz;
	return s_zz._zzs;
}

