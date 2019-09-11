#pragma once
#include "cObject.h"

class uiMap;
namespace ccu
{
	uiMap* getMap();
	void setMap(uiMap* map);
}

class uiMap : public Node
{
public:
	CREATE_FUNC(uiMap);
	uiMap();
	~uiMap();
	
protected:
	bool init();
public:
	void clearNpcs();
	void clearTrans();

	void load(eMap e);
	void load(const txtMap::sMap& maps);
	void load(const txtMap::sTransmit& transmit);
	void load(const txtMap::sNpc& npc, bool smap);
	void load(int x20, int y20);
	void loadMusic();

	// 小地图 笛卡尔
	Vec2 toPosition(int x20, int y20);
	void toPosition(const Vec2& vMap, int& x20, int& y20);
	// 这是小地图的笛卡尔20
	bool isObstacle(int x20, int y20);

	void setViewer(cObject* viewer);
	cObject* getViewer() const { return _viewer; }

	Node* getMap() { return _nodeMap; }
	Node* getTrans() { return _menuTrans; }
	Node* getNpcs() { return _nodeNpcs; }
	Node* getMask() { return _nodeMask; }
	
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void onTouchCancelled(Touch *touch, Event *unused_event);
	cObject* getObject(Touch *touch);
protected:
	void update(float delta);

protected:
	eMap _emap = eMap::eNone;
	sMapCache _cache;
	cObject* _viewer = nullptr;
	Node* _nodeMap = nullptr;
	Menu* _menuTrans = nullptr;
	Node* _nodeNpcs = nullptr;
	Node* _nodeMask = nullptr;

	Menu::State _touchState;
	cObject* _selectObj = nullptr;
};