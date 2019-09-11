#include "uiAddpoint.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiManager.h"

uiAddpoint5* uiAddpoint5::create(bool is5)
{
	CREATE(uiAddpoint5, is5)
}

bool uiAddpoint5::init(bool is5)
{
	if (!Node::init())
	{
		return false;
	}
	_is5 = is5;
	_point5.reset(0);
	_point5.remain = 10;
	cMenu* menuKeep = cMenu::create();
	menuKeep->scheduleUpdate();
	this->addChild(menuKeep);

	menuKeep->addChild(_buttonConfirm = cButton::create(cc8::cConfirm, eFont::bigger));
	_buttonConfirm->setPosition(_buttonConfirm->getContentSize() / 2);
	_buttonConfirm->onClick = [this]()
	{
		if (onPoint == nullptr)
		{
			return;
		}
		if (!_is5)
		{
			onPoint(_point + _lv);
			return;
		}
		_point5 = _point;
		sPoint point;
		forv(_points, k)
		{
			point.get((ePoint)k) = _point.get((ePoint)k) * _lv / 2;
		}
		point += _lv;
		point.correctRemain(_lv);
		onPoint(point);
	};
	_buttonConfirm->onKeep = [this](bool first)
	{
		if (first && onLong != nullptr)
		{
			onLong();
		}
	};
	int inv = 16;
	float h = _buttonConfirm->getContentSize().height + inv;

	this->addChild(_labelBody = cLabelEasy::create(eFont::e200));
	this->addChild(_labelMana = cLabelEasy::create(eFont::e200));
	this->addChild(_labelStr = cLabelEasy::create(eFont::e200));
	this->addChild(_labelDex = cLabelEasy::create(eFont::e200));
	this->addChild(_labelAgi = cLabelEasy::create(eFont::e200));
	this->addChild(_labelRemian = cLabelEasy::create("5689", eFont::e200));


//	float h2 = _labelRemian->getContentSize().height;
	_labelRemian->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_labelRemian->setPositionY(_buttonConfirm->getPositionY());
	_labelRemian->setVisible(false/*!is5*/);

	std::vector<cLabel*> labelNames =
	{
		cLabel::create(cc8::cPointBody),
		cLabel::create(cc8::cPointMana),
		cLabel::create(cc8::cPointStr),
		cLabel::create(cc8::cPointDex),
		cLabel::create(cc8::cPointAgi),
	};

	std::vector<cLabelEasy*> labels =
	{
		_labelBody,
		_labelMana,
		_labelStr,
		_labelDex,
		_labelAgi,
		_labelRemian,
	};



	cButton* button = nullptr;
	cButton* btn = nullptr;
	cLabel* label = nullptr;
	cLabelEasy* labelEasy = nullptr;
	Size s = Size::ZERO;
	forv(_buttonAdds, k)
	{
		menuKeep->addChild(btn = _buttonAdds.at(k) = cButton::create2(ccu::cAddpoint));
		menuKeep->addChild(button = _buttonSubs.at(k) = cButton::create2(ccu::cSubpoint));
		this->addChild(label = labelNames.at(k));
		label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

		labelEasy = labels.at(k);
		labelEasy->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

		button->setEasy(true);
		btn->setEasy(true);
		if (s.equals(Size::ZERO))
		{
			s = button->getContentSize();
		}

		button->setPosition(Vec2(0, h + (_size_ - 1 - k) * (s.height + inv)) + s / 2);
		if (is5 && false)
		{
			label->setVisible(false);
		}
		else
		{
			button->setPositionX(button->getPositionX() + label->getContentSize().width + 16);
		}
		btn->setPosition(cc::getRight(button) + _labelRemian->getContentSize().width /*h2 * (is5 ? 2 : 2.4f)*/ + s.width / 2, button->getPositionY());
		label->setPositionY(button->getPositionY());
		labelEasy->setPosition(button->getPositionX() / 2 + btn->getPositionX() / 2, button->getPositionY() + cLabelEasy::cOffy);

		button->onClick = [this, k]()
		{
			auto& point = _point;
			ePoint e = (ePoint)k;
			if (!point.sub(e, true))
			{
				return;
			}
			point.sub(e, false);
			_pointShow.get(e) = _point.get(e) + _lv;
			_isPointed = true;
			updatePoint();
		};

		btn->onClick = [this, k]()
		{
			auto& point = _point;
			ePoint e = (ePoint)k;
			if (!point.add(e, true))
			{
				return;
			}
			point.add(e, false);
			_pointShow.get(e) = _point.get(e) + _lv;
			_isPointed = true;
			updatePoint();
		};
	}
	h += _buttonAdds.size() * (s.height + inv);
	button = _buttonAdds.back();
	setContentSize(Size(button->getPositionX() + s.width / 2, h - inv));

	_labelRemian->setPositionX(_labelBody->getPositionX());
	_buttonConfirm->setPositionX(_labelBody->getPositionX());

	this->addChild(label = cLabel::create(cc8::cSupportLong, eFont::smaller));
	label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	label->setPosition(cc::getLB(_buttonConfirm));
	return true;
}

static void setString(cLabelEasy* label, int point)
{
	if (point % 2 == 1)
	{
		label->setString(toString("%.1f", point / 2.0f));
	}
	else
	{
		label->setString(cc::toString(point / 2));
	}
}

void uiAddpoint5::updatePoint()
{
	if (_is5)
	{
		setString(_labelBody, _point.body);
		setString(_labelMana, _point.mana);
		setString(_labelStr, _point.str);
		setString(_labelDex, _point.dex);
		setString(_labelAgi, _point.agi);

		if (_point.remain % 2 == 1)
		{
			_buttonConfirm->setString(toString("%.1f", _point.remain / 2.0f));
		}
		else
		{
			_buttonConfirm->setString(cc::toString(_point.remain / 2));
		}
	}
	else
	{
		_labelBody->setString(cc::toString(_pointShow.body));
		_labelMana->setString(cc::toString(_pointShow.mana));
		_labelStr->setString(cc::toString(_pointShow.str));
		_labelDex->setString(cc::toString(_pointShow.dex));
		_labelAgi->setString(cc::toString(_pointShow.agi));
		_buttonConfirm->setString(cc::toString(_point.remain));
	}
	_labelRemian->setString(cc::toString(_point.remain));


	forv(_buttonAdds, k)
	{
		_buttonAdds[k]->setVisible(_points[k] != nullptr && _point.remain > 0);
		_buttonSubs[k]->setVisible(_points[k] != nullptr && *_points[k] > 0);
	}
}

void uiAddpoint5::load(const sPoint& point, int lv)
{
	if (!point.check(lv))
	{
		return;
	}
	_point = point;
	_point += -lv;
	_lv = lv;
	forv(_points, k)
	{
		_points[k] = &_point.get((ePoint)k);
	}
	_pointShow = point;
	updatePoint();
}

void uiAddpoint5::load(int lv)
{
	_point = _point5;
	_lv = lv;
	forv(_points, k)
	{
		_points[k] = &_point.get((ePoint)k);
	}
	_pointShow = _point;
	updatePoint();
}


//////////////////////////////////////////////////////////////////////////
bool cAddpoint::init(Node* parent)
{
	parent->addChild(_attr = uiAttribute::create(true, 14));
	parent->addChild(_point = uiAddpoint5::create(false));
	parent->addChild(_point5 = uiAddpoint5::create(true));

	_point->setPositionX(_attr->getPositionX() + _attr->getContentSize().width + 72);
	_point5->setPositionX(_point->getPositionX() + _point->getContentSize().width - _point5->getContentSize().width);
	parent->setContentSize(Size(_point5->getPositionX() + _point5->getContentSize().width, _point->getContentSize().height));
	_attr->setPositionY(parent->getContentSize().height - _attr->getContentSize().height - cButton::create2(ccu::cAddpoint)->getContentSize().height + uiAttr::create(cc8::cPropertyHp)->getContentSize().height * 3 / 2);


	_point->onLong = [this]()
	{
		_point->setVisible(false);
		_point5->setVisible(true);
	};
	_point5->onLong = [this]()
	{
		_point->setVisible(true);
		_point5->setVisible(false);
	};
	_point5->onLong();
	return true;
}


void cAddpoint::loadAttr(const sProperty* pro)
{
	sPropertys pros;
	ccp::apply(pros, pro);
	_attr->load(&pros.attr);
}

void cAddpoint::load(const sProperty* pro)
{
	_pro = pro;
	if (pro == nullptr)
	{
		return;
	}
	loadAttr(pro);
	_point->load(pro->point, pro->lv);
	_point5->load(pro->lv);

	_point->onPoint = [this](const sPoint& point)
	{
		if (_pro == nullptr)
		{
			return;
		}
		if (ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		if (onPoint != nullptr && onPoint(_pro, point))
		{
			loadAttr(_pro);
		}
	};

	_point5->onPoint = [this](const sPoint& point)
	{
		if (_pro == nullptr)
		{
			return;
		}
		if (ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		_point->load(point, _pro->lv);
		_point->onPoint(point);
	};
}



//////////////////////////////////////////////////////////////////////////
uiAddpoint* uiAddpoint::create(const sProperty* pro)
{
	CREATE(uiAddpoint, pro);
}

bool uiAddpoint::init(const sProperty* pro)
{
	if (!Node::create())
	{
		return false;
	}
	cAddpoint::init(this);
	load(pro);
	return true;
}


//////////////////////////////////////////////////////////////////////////
uiAddpointer* uiAddpointer::create(const sProperty* pro)
{
	CREATE(uiAddpointer, pro);
}

bool uiAddpointer::init(const sProperty* pro)
{
	if (!uiPad::init(ccu::cPad))
	{
		return false;
	}
	uiPad::setContentSize(uiPad::cSize);
	Node* node = Node::create();
	this->addChild(node);
	cAddpoint::init(node);
	// БъЬт
	node->setPosition(_contentSize / 2 - node->getContentSize() / 2 - Size(0, 8));
	load(pro);
	return true;
}
