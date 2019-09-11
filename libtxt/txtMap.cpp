#include "txtMap.h"

const int txtMap::c0 = 0;

void txtMap::init(eMap e, int mapid, ulong uid, ulong music, const std::string& mapname)
{
	_map = &_maps.at(e);
	_map->mapid = mapid;
	_map->uid = uid;
	_map->music = music;
	_map->mapname = mapname;
}

void txtMap::insert(int lv10, const std::vector<eMod>& mines)
{
	_map->lv = lv10;
	_map->mines = mines;
}

void txtMap::insert(int x, int y, eMap e, int tx, int ty)
{
	_transmit.x = x;
	_transmit.y = y;
	_transmit.e = e;
	_transmit.tx = tx;
	_transmit.ty = ty;
	_map->transmits.push_back(_transmit);
}

void txtMap::insert(int x, int y, int direction, const std::string& name /*= ""*/, const std::string& script /*= ""*/)
{
	insert(eMod::eNone, x, y, direction, name, script);
}

void txtMap::insert(eMod e, int x, int y, int direction, const std::string& name /*= ""*/, const std::string& script /*= ""*/)
{
	_npc.mod = e;
	_npc.x = x;
	_npc.y = y;
	_npc.direction = direction;
	_npc.name = name;
	_npc.script = script;
	_map->npcs.push_back(_npc);
}



const char* txtMap::cTransmit = "transmit";
static std::string scriptTransmit(eMap e, int x, int y)
{
	return txtMap::cTransmit + toString("_%d_%d_%d", (int)e, x, y);
}
namespace eD = eDirection;


txtMap::txtMap()
{
	{
		sMap m;
		for (int e = (int)eMap::e0; e <= (int)eMap::eEnd; ++e)
		{
			_maps.insert(std::make_pair((eMap)e, m));
		}
	}
	// 33,110 出生点
	init(eMap::haiwan, 1506, 0x3303D9A1, 0x4B4740AC, "海湾");
	insert(c0, { eMod::haimaochong, eMod::zhangyu, eMod::li });
	insert(6, 85, eMap::yewai, 137, 98);
	insert(11, 13, eMap::yewai, 141, 55);
	insert(79, 32, eMap::yandong, 12, 9);
	insert(103, 10, eMap::chenchuan, 13, 44);
	insert(70, 17, eD::RD, "傲来", scriptTransmit(eMap::aolai, 166, 19));

	init(eMap::yewai, 1193, 0x242616F7, 0x266E2C58, "野外");
	insert(10, { eMod::yezhu, eMod::huayao, eMod::erha });
	insert(146, 96, eMap::haiwan, 14, 84);
	insert(151, 53, eMap::haiwan, 26, 13);

	init(eMap::chenchuan, 1507, 0xC8748621, 0x8EF4D872, "沉船");
	insert(30, { eMod::xiabing, eMod::xiejiang });
	insert(9, 57, eMap::haiwan, 83, 15);

	init(eMap::yandong, 1126, 0x63033A32, 0xA6F426EB, "岩洞");
	insert(20, { eMod::kulouguai, eMod::yegui });
	insert(9, 17, eMap::haiwan, 74, 27);
	insert(31, 78, eMap::guicheng, 38, 19);

	init(eMap::guicheng, 1202, 0x3FCA8C5A, 0xEBCC1270, "鬼城");
	insert(40, { eMod::jiangshi, eMod::mamian, eMod::niutou });
	insert(24, 9, eMap::yandong, 29, 71);

	init(eMap::aolai, 1092, 0xAEAEAF33, 0x35159569, "傲来");
	insert(207, 139, eD::LD, "北极", scriptTransmit(eMap::beiji, 179, 104));
	insert(22, 129, eD::RD, "北极", scriptTransmit(eMap::beiji, 183, 17));
	insert(172, 11, eD::RD, "海湾", scriptTransmit(eMap::haiwan, 75, 21));

	init(eMap::beiji, 1174, 0xC4523BAE, 0x2142584C, "北极");
	insert(50, { eMod::leiniaoren, eMod::ruishou, eMod::tianjiang });
	insert(82, 150, eMap::fengchao, 73, 23);
	insert(11, 83, eMap::longku, 96, 15);
	insert(199, 105, eD::LD, "傲来", scriptTransmit(eMap::aolai, 197, 127));
//  insert(195, 9, eD::RD, "地遁鬼", scriptTransmit("长寿郊外", 60, 67));

	init(eMap::longku, 1183, 0xEADE2B36, 0x65B90ACA, "龙窟");
	insert(60, { eMod::tianbing, eMod::jiaolong });
	insert(101, 11, eMap::beiji, 18, 77);

	init(eMap::fengchao, 1192, 0xA2C1DE00, 0xB33EB187, "凤巢");
	insert(60, { eMod::diyuzhanshen, eMod::fenghuang });
	insert(83, 10, eMap::beiji, 87, 139);
}

const std::map<eMap, txtMap::sMap>& txtMap::getMaps()
{
	static txtMap s_map;
	return s_map._maps;
}


