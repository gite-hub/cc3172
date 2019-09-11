#pragma once
#include "_inc.h"
#include "eMod.h"
#include "eMap.h"

class txtMap
{
public:
	struct sNpc
	{
		eMod mod;
		int x, y, direction;
		std::string name, script;
	};
	// 传送
	struct sTransmit
	{
		eMap e;
		int x, y, tx, ty;
	};
	struct sMap
	{
		int mapid, lv = c0;
		ulong uid, music;
		std::string mapname;
		std::vector<sNpc> npcs;
		std::vector<sTransmit> transmits;
		// 暗雷
		std::vector<eMod> mines;
	};
	txtMap();
private:
	void init(eMap e, int mapid, ulong uid, ulong music, const std::string& mapname);
	void insert(int lv, const std::vector<eMod>& mines);
	void insert(int x, int y, eMap e, int tx, int ty);
	void insert(int x, int y, int direction, const std::string& name = "", const std::string& script = "");
	void insert(eMod e, int x, int y, int direction, const std::string& name = "", const std::string& script = "");
	sNpc _npc;
	sTransmit _transmit;
	sMap* _map;
protected:
	std::map<eMap, sMap> _maps;
public:
	static const std::map<eMap, sMap>& getMaps();
	static const int c0;
	static const char* cTransmit;
};