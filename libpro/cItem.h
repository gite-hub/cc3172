#pragma once
#include "sItem.h"
#include "cIndexCounter.h"

class cShoujue : cUnique<sItem>
{
	friend class cItem;
};
// °ü¹ü
class cItem : public cUnique<sItem>
{
public:
	typedef std::map<int, sItem*> sTable;
	static cItem* getInstance();
	static int find(sItems& items, const sItem* item);
	static sItem* createItem(eIcon type, int id);

	cItem();
	int add(bool equip, sItems& items, const sItem* item, bool onlyCheck = false);
private:
	sTable& getTable(bool equip);
public:
	sItem* createEquip(eIcon type, int id);
	sItem* createShoujue(eSki eski, int count = 1);


	sItem* getEquip(eIcon type, int id);
	sItem* getShoujue(eSki eski, int count = 1);

	sItem* getEquip(int unique);
	sItem* getShoujue(int unique);

	bool removeEquip(int unique);
	bool removeShoujue(int unique);

private:
	cShoujue _shoujues;

public:
	static const int c5, c4, c20;
};