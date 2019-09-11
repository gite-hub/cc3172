#include "sItem.h"
#include "cEquip.h"

bool sItem::setData(eIcon type, int id)
{
	if (type == eIcon::eNone)
	{
		return false;
	}
	const auto& icons = txtIcon::getIcons().at(type);
	const auto& it = icons.find(id);
	if (it == icons.end())
	{
		return false;
	}
	_type = type;
	_id = id;
	_icon = &it->second;
	_num = 1;
	setData();
//	_price = _icon->price;
	return true;
}

void sItem::setData()
{
	if (cEquip::isEquip(_type))
	{
		cEquip::sPro head;
		head.apply(_type);
		// 70Мђвз
		if (cEquip::getLv(this) == 70)
		{
			head.easy = 1;
		}
		_pro = head.pro;
	}
}


bool sItem::add(int count /*= 1*/)
{
	_num += count;
	return true;
}

bool sItem::sub(int count /*= 1*/)
{
	if (_num < count)
	{
		return false;
	}
	_num -= count;
	return true;
}

bool sItem::isValid() const
{
	return _num > 0 && _type != eIcon::eNone && _icon != nullptr && (_pro > 0 || !cEquip::isEquip(_type));
}

sItem::operator bool() const
{
	return isValid();
}

void sItem::toDesc(sDescs& descs)const
{
	descs.clear();
	if (!isValid())
	{
		return;
	}
	sDesc d;
	descs.clear();

	descs.uhead = _icon->uid;
	descs.name = _icon->name;

	if (!_icon->desc.empty())
	{
		d.text = _icon->desc;
		d.color = s888::WHITE;
		descs.push(d);
	}
}


void sItem::toDesc(sDescs& descs, eStone stone) const
{
	toDesc(descs);
	if (!cEquip::isEquip(_type))
	{
		return;
	}
	sItem it = *this;
	eStone old = cEquip::getHead(this).stone;
	cEquip::setStone(&it, stone);
	cEquip::apply(&it, descs);
}

bool sItem::isOverly() const
{
	return _type == eIcon::shoujue;
}


void sItem::save(bool price)const
{
	sStream& sav = *cSave::getSave();
// 	if (!*this)
// 	{
// 		sav << 0 << s_space;
// 		return;
// 	}
	sUnique::save();
	sav << _num << s_space << (int)_type << s_space << _id << s_space;
	if (price)
	{
		sav << _price << s_space;
	}
	if (cEquip::isEquip(_type))
	{
		sav << _pro << s_space;
	}
}

void sItem::load(bool price)
{
	sStream& sav = *cSave::getLoad();
	sUnique::load();
	sav >> _num;
// 	if (_num == 0)
// 	{
// 		return;
// 	}
	int type;
	sav >> type >> _id;
	if (price)
	{
		sav >> _price;
	}
	_type = (eIcon)type;
	if (cEquip::isEquip(_type))
	{
		sav >> _pro;
	}
	_icon = &txtIcon::getIcons().at(_type).at(_id);
}


bool sItem::operator!=(const sItem& it) const
{
	return !(_type == it._type && _id == it._id);
}


bool sItem::operator==(const sItem& it) const
{
	return _type == it._type && _id == it._id;
}