#include "uiAttr.h"
#include "_cc8.h"
#include "_ccu.h"

const int uiAttr::c4 = 4;
const int uiAttr::cInterval = 4;
static int s_spriteX = 0;
int uiAttr::getSpriteX()
{
	if (s_spriteX == 0)
	{
		s_spriteX = cLabel::create(cc8::cPropertyHp)->getContentSize().width;
	}
	return s_spriteX;
}


uiAttr* uiAttr::create(int length, const std::string& field, const std::string& value /* = "" */)
{
	CREATE(uiAttr, length, field, value);
}

uiAttr* uiAttr::create(const std::string& field, const std::string& value /*= ""*/)
{
	CREATE(uiAttr, c4, field, value);
}

bool uiAttr::init(int length, const std::string& field, const std::string& value)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_labelField = cLabel::create(field));
	float w = _labelField->getContentSize().width;
	float h = _labelField->getContentSize().height;
	_labelField->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	_labelField->setPositionX(getSpriteX());

	Sprite9* sprite = Sprite9::create(ccu::cRect);
	sprite->setColor(ccu::cColorRect);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	sprite->setPositionX(_labelField->getPositionX() + 4);
	this->addChild(sprite);



	std::string str;
	for (int k = 0; k <= length; ++k)
	{
		str += '8';
	}
	this->addChild(_labelValue = cLabelEasy::create(str));
	_labelValue->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	int ix = 2;
	_labelValue->setPositionX(sprite->getPositionX() + ix);
	_labelValue->setColor(sColor(0x33, 0x33, 0x33));

	sprite->setContentSize(Size(_labelValue->getContentSize().width + ix, 26));

	this->setContentSize(Size(cc::getRight(sprite), std::max(h, sprite->getContentSize().height)));

	_labelField->setPositionY(_contentSize.height / 2);
	_labelValue->setPositionY(_contentSize.height / 2 + cLabelEasy::cOffy);
	sprite->setPositionY(_contentSize.height / 2 - 1);

	_labelValue->setString(value);
	return true;
}

void uiAttr::load(const std::string& field, const std::string& value)
{
	_labelField->setString(field);
	_labelValue->setString(value);
}

void uiAttr::load(const std::string& field, int value)
{
	_labelField->setString(field);
	_labelValue->setString(cc::toString(value));
}

void uiAttr::load(const std::string& field, u64 value)
{
	_labelField->setString(field);
	_labelValue->setString(cc::toString(value));
}

void uiAttr::load(const std::string& field)
{
	_labelField->setString(field);
}

void uiAttr::setValue(const std::string& value)
{
	_labelValue->setString(value);
}

void uiAttr::setValue(int value)
{
	_labelValue->setString(cc::toString(value));
}

void uiAttr::setValue(int value, int valueMax)
{
	_labelValue->setString(cc::toString(value) + "/" + cc::toString(valueMax));
}

void uiAttr::setValue(u64 value)
{
	_labelValue->setString(cc::toString(value));
}


void uiAttr::setValue(u64 value, u64 valueMax)
{
	_labelValue->setString(cc::toString(value) + "/" + cc::toString(valueMax));
}

//////////////////////////////////////////////////////////////////////////
uiAttribute* uiAttribute::create(bool hpmp, int interval, const sAttribute* attr /*= nullptr*/)
{
	CREATE(uiAttribute, hpmp, interval, attr);
}
uiAttribute* uiAttribute::create(bool hpmp, const sAttribute* attr /*= nullptr*/)
{
	CREATE(uiAttribute, hpmp, uiAttr::cInterval, attr);
}
uiAttribute* uiAttribute::create(int interval, const sAttribute* attr /*= nullptr*/)
{
	CREATE(uiAttribute, false, interval, attr);
}
uiAttribute* uiAttribute::create(const sAttribute* attr /*= nullptr*/)
{
	CREATE(uiAttribute, false, uiAttr::cInterval, attr);
}

bool uiAttribute::init(bool hpmp, int interval, const sAttribute* attr)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_attrHp = uiAttr::create(cc8::cPropertyHp));
	this->addChild(_attrMp = uiAttr::create(cc8::cPropertyMp));
	this->addChild(_attrHit = uiAttr::create(cc8::cPropertyHit));
	this->addChild(_attrAtk = uiAttr::create(cc8::cPropertyAtk));
	this->addChild(_attrDef = uiAttr::create(cc8::cPropertyDef));
	this->addChild(_attrMtk = uiAttr::create(cc8::cPropertyMtk));
	this->addChild(_attrMef = uiAttr::create(cc8::cPropertyMef));
	this->addChild(_attrSpeed = uiAttr::create(cc8::cPropertySpeed));
	this->addChild(_attrAvoid = uiAttr::create(cc8::cPropertyAvoid));

	std::vector<uiAttr*> attrs =
	{
		_attrHp,
		_attrMp,
		_attrHit,
		_attrAtk,
		_attrDef,
		_attrMtk,
		_attrMef,
		_attrSpeed,
		_attrAvoid,
	};

	float h = 0;
	uiAttr* a = nullptr;
	forv(attrs, k)
	{
		a = attrs.at(k);
		if (h == 0)
		{
			h = a->getContentSize().height;
		}
		a->setPosition(0, (_size_ - 1- k) * (h + interval));
	}
	if (hpmp)
	{
		a = _attrHp;
	}
	else
	{
		a = _attrHit;
		_attrHp->setVisible(false);
		_attrMp->setVisible(false);
	}
	setContentSize(Size(a->getContentSize().width, a->getPositionY() + a->getContentSize().height));
	load(attr);
	return true;
}

void uiAttribute::load(const sAttribute* attr)
{
	if (attr == nullptr)
	{
		return;
	}
	_attrHp->setValue(attr->hpMax);
	_attrMp->setValue(attr->mpMax);
	_attrHit->setValue(attr->hit);
	_attrAtk->setValue(attr->atk);
	_attrDef->setValue(attr->def);
	_attrMtk->setValue(attr->mtk);
	_attrMef->setValue(attr->mef);
	_attrSpeed->setValue(attr->speed);
	_attrAvoid->setValue(attr->avoid);
}


int uiAttribute::getSpriteX() const
{
	return _attrHp->getPositionX() + _attrHp->getSpriteX();
}

//////////////////////////////////////////////////////////////////////////
uiPoint* uiPoint::create(bool remain, int interval, const sPoint* point /*= nullptr*/)
{
	CREATE(uiPoint, remain, interval, point);
}
uiPoint* uiPoint::create(bool remain, const sPoint* point /*= nullptr*/)
{
	CREATE(uiPoint, remain, uiAttr::cInterval, point);
}
uiPoint* uiPoint::create(int interval, const sPoint* point /*= nullptr*/)
{
	CREATE(uiPoint, true, interval, point);
}
uiPoint* uiPoint::create(const sPoint* point /*= nullptr*/)
{
	CREATE(uiPoint, true, uiAttr::cInterval, point);
}


bool uiPoint::init(bool remain, int interval, const sPoint* point)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_attrBody = uiAttr::create(cc8::cPointBody));
	this->addChild(_attrMana = uiAttr::create(cc8::cPointMana));
	this->addChild(_attrStr = uiAttr::create(cc8::cPointStr));
	this->addChild(_attrDex = uiAttr::create(cc8::cPointDex));
	this->addChild(_attrAgi = uiAttr::create(cc8::cPointAgi));
	this->addChild(_attrRemain = uiAttr::create(cc8::cPointRemain));

	std::vector<uiAttr*> attrs =
	{
		_attrBody,
		_attrMana,
		_attrStr,
		_attrDex,
		_attrAgi,
		_attrRemain,
	};

	float h = 0;
	uiAttr* a = nullptr;
	if (!remain)
	{
		_attrRemain->setVisible(false);
		attrs.pop_back();
	}
	forv(attrs, k)
	{
		a = attrs.at(k);
		if (h == 0)
		{
			h = a->getContentSize().height;
		}
		a->setPosition(0, (_size_ - 1 - k) * (h + interval));
	}
	setContentSize(Size(_attrBody->getContentSize().width, _attrBody->getPositionY() + _attrBody->getContentSize().height));
	load(point);
	return true;
}

void uiPoint::load(const sPoint* point)
{
	if (point == nullptr)
	{
		return;
	}
	_attrBody->setValue(point->body);
	_attrMana->setValue(point->mana);
	_attrStr->setValue(point->str);
	_attrDex->setValue(point->dex);
	_attrAgi->setValue(point->agi);
	_attrRemain->setValue(point->remain);
}

//////////////////////////////////////////////////////////////////////////
uiZz* uiZz::create(const sZz* zz)
{
	CREATE(uiZz, uiAttr::cInterval, false, zz);
}
uiZz* uiZz::create(int interval, const sZz* zz)
{
	CREATE(uiZz, interval, false, zz);
}
uiZz* uiZz::create(bool is2, const sZz* zz)
{
	CREATE(uiZz, uiAttr::cInterval, is2, zz);
}
uiZz* uiZz::create(int interval, bool is2, const sZz* zz)
{
	CREATE(uiZz, interval, is2, zz);
}

bool uiZz::init(int interval, bool is2, const sZz* zz)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_attrAtk = uiAttr::create(cc8::cZzAtk));
	this->addChild(_attrDef = uiAttr::create(cc8::cZzDef));
	this->addChild(_attrHp = uiAttr::create(cc8::cZzHp));
	this->addChild(_attrMana = uiAttr::create(cc8::cZzMana));
	this->addChild(_attrSpeed = uiAttr::create(cc8::cZzSpeed));
	this->addChild(_attrAviod = uiAttr::create(cc8::cZzAvoid));
	this->addChild(_attrGrow= uiAttr::create(cc8::cZzGrow));

	std::vector<uiAttr*> attrs =
	{
		_attrAtk,
		_attrDef,
		_attrHp,
		_attrMana,
		_attrSpeed,
		_attrAviod,
		_attrGrow,
	};

	float h = 0;
	uiAttr* a = nullptr;
	if (is2)
	{
	//	attrs.erase(attrs.begin() + attrs.size() - 2);
	//	_attrAviod->setVisible(false);
		int i = 2;
		float w;
		for (int k = 0, size = attrs.size(), size2 = std::ceil(size * 1.0f / i) * i; k < size; ++k)
		{
			a = attrs.at(k);
			if (h == 0)
			{
				w = a->getContentSize().width;
				h = a->getContentSize().height;
			}
			a->setPosition((k % i) * (w + 16), ((size2 - 1 - k) / i) * (h + uiAttr::cInterval));
		}
		setContentSize(Size(cc::getRT(_attrDef)));
	}
	else
	{
		forv(attrs, k)
		{
			a = attrs.at(k);
			if (h == 0)
			{
				h = a->getContentSize().height;
			}
			a->setPosition(0, (_size_ - 1 - k) * (h + interval));
		}
		setContentSize(Size(cc::getRT(_attrAtk)));
	}
	load(zz);
	return true;
}

void uiZz::load(const sZz* zz)
{
	if (zz == nullptr)
	{
		return;
	}
	_attrAtk->setValue(zz->atk);
	_attrDef->setValue(zz->def);
	_attrHp->setValue(zz->hp);
	_attrMana->setValue(zz->mana);
	_attrSpeed->setValue(zz->speed);
	_attrAviod->setValue(zz->avoid);
	_attrGrow->setValue(toString("%0.2f", zz->grow * 0.01f));
}
