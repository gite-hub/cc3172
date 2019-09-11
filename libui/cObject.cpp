#include "cObject.h"
#include "_ccu.h"
#include "cScript.h"
#include "uiChannel.h"
#include "uiManager.h"
#include "uiMap.h"



bool cBody::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(56, 72));
//	this->setGlobalZOrder(ccu::zMapObj);
	this->addChild(_nodeInner = Node::create());
	_nodeInner->setPositionX(_contentSize.width / 2);

	_nodeInner->addChild(_nodeBody = Node::create());
	_nodeInner->addChild(_labelName = cLabel::create(" ", eFont::smal));
//	_labelName->setGlobalZOrder(ccu::zMapFont);
	_nodeInner->addChild(_nodeSay = Node::create(), ccu::zMapSay);

	static int hShadow = 0;
	if (hShadow == 0)
	{
		hShadow = cSprite1::create(ccu::uShadow)->getContentSize().height + _labelName->getContentSize().height;
	}
	_labelName->enableShadow();
	_labelName->setPositionY(-hShadow / 2);
	setNameColor(ccu::cColorObj);

	return true;
}


void cBody::load(const sMod::sActs& acts)
{
	_nodeBody->removeAllChildren();
	_bodies.clear();
	cSprite* sprite = nullptr;
	for (const auto& a : acts)
	{
		_nodeBody->addChild(sprite = cSprite::create(a.second));
		_bodies.insert(std::make_pair(a.first, sprite));
		sprite->setVisible(false);
		sprite->setShadow(true);
	//	sprite->setFrameOnly(true);
	//	sprite->play();
	}
}

void cBody::load(const sMod& mod, bool map)
{
	if (!mod)
	{
		return;
	}
	sMod::sActs acts;
	mod.apply(acts, map, false);
	cBody::load(acts);
}

cSprite* cBody::getBody() const
{
	return _body;
}

void cBody::setBody(eAct e, bool reframe /*= true*/)
{
	if (e == _eact)
	{
		return;
	}
	const auto& it = _bodies.find(e);
	if (it == _bodies.end())
	{
		return;
	}
	cSprite* body = nullptr;
	if (_body != nullptr)
	{
		body = _body;
		body->setVisible(false);
	}
	_eact = e;
	_body = it->second;
	_body->setVisible(true);
	if (body != nullptr)
	{
		_body->setDirection(body->getDirection());
	}
//	_body->setBlend(body->getBlend());
	if (reframe || body->getInfo()->framesCountPerDirection >= _body->getInfo()->framesCountPerDirection)
	{
		_body->setFrame(0);
	}
	if (_body != nullptr)
	{
		_hBody = _h1 = _body->getInfo()->height;
		_nodeSay->setPositionY(_hBody);
	}
}

int cBody::getHeight(bool only1st) const
{
	return only1st ? _h1 : _hBody;
}

void cBody::setName(const std::string& name)
{
	Node::setName(name);
	_labelName->setString(name);
}

void cBody::showName(bool show)
{
	_labelName->setVisible(show);
}

void cBody::setNameColor(const sColor& color)
{
	_labelName->setColor(_colorName = color);
}

void cBody::setLight(float delta)
{
	for (auto& body : _bodies)
	{
		body.second->setBlend(eBlend::light);
	}
	this->runAction(Sequence::create(
		DelayTime::create(1), 
		CallFunc::create([this]() 
		{
			for (auto& body : _bodies)
			{
				body.second->setBlend(eBlend::normal);
			}
		}), nullptr));
}

void cBody::say(const std::string& text, bool toast)
{
	Sprite9* sprite = Sprite9::create(ccu::cDesc);
	cText* t = cText::create(eFont::smal, 128);
	t->setString(text);
	sprite->setContentSize(t->getContentSize() + Size(32, 32));
	sprite->addChild(t);
	t->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	t->setPosition(Vec2(16, 16));
	_nodeSay->addChild(sprite);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	float h = sprite->getContentSize().height;
	
	float dt = _hSay * 0.01f;
	sprite->runAction(MoveTo::create(dt, Vec2(sprite->getPositionX(), _hSay)));
	_hSay += h;
	sprite->runAction(Sequence::create(
		DelayTime::create(5),
		CallFuncN::create([this, h, dt](Node* sprite)
	{
		for (auto& n : _nodeSay->getChildren())
		{
			if (n == sprite)
			{
				continue;
			}
			n->runAction(MoveBy::create(dt, Vec2(0, h)));
		}
		_hSay -= h;
	}),
		RemoveSelf::create(),
		nullptr));
	if (toast)
	{
		ccu::getManager()->addChannel(_labelName->getString(), text);
	}
}




//////////////////////////////////////////////////////////////////////////
cObject* cObject::create(const sMod& mod)
{
	CREATE(cObject, mod);
}

bool cObject::init(const sMod& mod)
{
	if (!cBody::init())
	{
		return false;
	}
	this->addChild(_spriteTop = cSprite::create(), ccu::zMapTop);
	load(mod, true);
	stand();
	scheduleUpdate();
	return true;
}

void cObject::loadTop(ulong top)
{
	_spriteTop->load(top);
}

void cObject::setBody(eAct e, bool reframe /*= true*/)
{
	cBody::setBody(e, reframe);
	_spriteTop->setPositionY(_h1);
}


void cObject::stand()
{
//	_isStand = true;
	setBody(eAct::stand);
	setSpeed(1);
}

void cObject::walk()
{
// 	if (_isStand)
// 	{
// 		_isStand = false;
// 		setBody(eAct::walk, false);
// 	}
	setBody(eAct::walk, false);
	setSpeed(1.5f);
}

void cObject::walk(const Vec2& vTo)
{
	walk();
	if (_body != nullptr)
	{
		int d;
		Vec2 v = vTo - _position;
		if (_body->getInfo()->directionsCount == 4)
		{
			d = cDirection::getDirection4(v.x, -v.y);
		}
		else
		{
			d = cDirection::getDirection8(_body->getDirection(), v.x, -v.y);
		}
		_body->setDirection(d);
	}
}


void cObject::setWays(const std::vector<Vec2>& ways)
{
	_ways = ways;
}

void cObject::clearWays()
{
	_ways.clear();
}

bool cObject::isWays() const
{
	return !_ways.empty();
}

void cObject::moving(int speed)
{
	static Vec2 v, v2, v3;
	if (!_ways.empty())
	{
		v = _ways.back();
		v2 = _position;
		v3 = v - v2;

		bool isMove = true;
		if (std::abs(v3.x) < speed && std::abs(v3.y) < speed)
		{
			_ways.pop_back();
			if (_ways.empty())
			{
				stand();
				isMove = false;
			}
			else
			{
				walk(v);
			}
		}

		if (isMove)
		{
			v3.normalize();
			v2 += v3 * speed;
			setPosition(v2);
		}
	}
}

void cObject::setHead(ulong head)
{
	_head = head;
}

void cObject::setScript(const std::string& script)
{
	_script = script;
}

void cObject::runScript()
{
	if (_script.empty())
	{
		return;
	}
	cScript::getInstance()->run(_head, _name, _script);
}

void cObject::update(float delta)
{
	if (!cSpriteDelta::stepDelta(delta))
	{
		return;
	}
// 	static Rect rect(cc::vsOrigin(), cc::vsSize()), r;
// 	r.origin = _parent->convertToWorldSpace(_position - _anchorPointInPoints);
// 	r.size = _contentSize;
// 	this->setVisible(rect.intersectsRect(r));
	if (_body != nullptr)
	{
		if (_body->step())
		{
			_body->setFrame(0);
		}
	}

}
