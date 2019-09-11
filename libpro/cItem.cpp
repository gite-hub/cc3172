#include "cItem.h"
#include "cEquip.h"

const int cItem::c5 = 5;
const int cItem::c4 = 4;
const int cItem::c20 = c5 * c4;
cItem* cItem::getInstance()
{
	static cItem* s_item = new cItem();
	return s_item;
}

int cItem::find(sItems& items, const sItem* item)
{
	if (item == nullptr || !item->isValid())
	{
		return cc::_1;
	}
	forv(items, k)
	{
		const auto& it = items.at(k);
		if (it == nullptr || !it->isValid())
		{
			continue;
		}
		if (*it == *item)
		{
			return k;
		}
	}
	return cc::_1;
}

sItem* cItem::createItem(eIcon type, int id)
{
	auto it = new sItem();
	if (!it->setData(type, id))
	{
		delete it;
		return nullptr;
	}
	return it;
}

cItem::cItem()
{

}

int cItem::add(bool equip, sItems& items, const sItem* item, bool onlyCheck /*= false*/)
{
	if (item == nullptr || !item->isValid())
	{
		return cc::_1;
	}
	std::vector<int> emptys;
	int iSame = cc::_1;
	// ¿Éµþ¼Ó
	bool overlay = item->isOverly();
	forv(items, k)
	{
		const auto& it = items.at(k);
		if (it == nullptr || !it->isValid())
		{
			emptys.push_back(k);
			continue;
		}
		if (overlay && iSame == cc::_1 && *item == *it)
		{
			iSame = k;
			break;
		}
	}
	if (iSame != cc::_1)
	{
		if (!onlyCheck)
		{
			items[iSame]->add(item->getCount());
			if (equip)
			{
				removeEquip(item->unique);
			}
			else
			{
				_shoujues.remove(item->unique);
			}
		}
		return iSame;
	}
	int size = emptys.size();
	int i = cc::_1;
	if (size > 0)
	{
		if (size < item->getCount())
		{
			// return cc::_1;
		}
		iSame = item->getCount();
		for (int k = 0; k < iSame; ++k)
		{
			sItem* it = nullptr;
			if (k == 0)
			{
				it = (sItem*)item;
				it->clear();
				it->add();
			}
			else
			{
				it = createItem(item->getType(), item->getId());
				if (it != nullptr)
				{
					if (equip)
					{
						insert(it);
					}
					else
					{
						_shoujues.insert(it);
					}
				}
			}
			if (k >= emptys.size())
			{
				i = items.size();
				items.push_back(it);
			}
			else
			{
				i = emptys.at(k);
				items.at(i) = it;
			}
		}
	}
	return i;
}


cItem::sTable& cItem::getTable(bool equip)
{
	return equip ? _table : _shoujues._table;
}

sItem* cItem::createEquip(eIcon type, int id)
{
	if (!cEquip::isEquip(type))
	{
		return nullptr;
	}
	return createItem(type, id);
}

sItem* cItem::createShoujue(eSki eski, int count /*= 1*/)
{
	auto it = createItem(eIcon::shoujue, (int)eski);
	if (it != nullptr)
	{
		it->clear();
		it->add(count);
	}
	return it;
}

sItem* cItem::getEquip(eIcon type, int id)
{
	auto it = createEquip(type, id);
	if (it != nullptr)
	{
		insert(it);
	}
	return it;
}

sItem* cItem::getEquip(int unique)
{
	return get(unique);
}

sItem* cItem::getShoujue(eSki eski, int count /*= 1*/)
{
	auto it = createShoujue(eski, count);
	if (it != nullptr)
	{
		_shoujues.insert(it);
	}
	return it;
}

sItem* cItem::getShoujue(int unique)
{
	return _shoujues.get(unique);
}

bool cItem::removeEquip(int unique)
{
	return remove(unique);
}

bool cItem::removeShoujue(int unique)
{
	return _shoujues.remove(unique);
}
