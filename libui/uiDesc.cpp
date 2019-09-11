#include "uiDesc.h"
#include "_ccu.h"

const int uiDesc::cInv = 16;
const int uiDesc::c56 = 56;
const int uiDesc::c192 = 320;
uiDesc* uiDesc::create(int width)
{
	CREATE(uiDesc, width);
}

uiDesc* uiDesc::create()
{
	CREATE(uiDesc, c192);
}


bool uiDesc::init(int width)
{
	if (!uiPad::init(ccu::cDesc, false))
	{
		return false;
	}
	setClose(false);
	setRemoveOnClose(true);
	setCloseOnOut(true);
	setAlpha(false);
	_width = width;

	this->addChild(_nodeInner = Node::create());
	_nodeContent = Sprite9::create(ccu::cRect);
	_nodeInner->addChild(_spriteHead = cSprite1::create());
	_spriteHead->addChild(_nodeContent, -1);
	_nodeInner->addChild(_nodeContent = Node::create());
	
	_nodeInner->setVisible(false);
	_nodePad->setVisible(false);
	setContentSize(Size::ZERO);
	return true;
}

void uiDesc::load(const std::string& desc, const sColor& color /*= sColor::WHITE*/)
{
	sDescs descs;
	descs.push(desc, s888(color.r, color.g, color.b));
	load(false, descs);
}


void uiDesc::load(bool scale, const sDescs& descs)
{
	auto uhead = descs.uhead;
	const auto& name = descs.name;

	int wLabel = _width;
	if (uhead == cSp::c0)
	{
		_spriteHead->setVisible(false);
	}
	else
	{
		wLabel -= c56;
		_spriteHead->setVisible(true);
		_spriteHead->load(uhead);
		_spriteHead->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);


		Node* node = _spriteHead->getChildren().front();
		node->setVisible(scale);
		if (scale)
		{
			int wh = std::max(_spriteHead->getContentSize().width, _spriteHead->getContentSize().height);
			node->setContentSize(Size(wh, wh));
			node->setPosition(_spriteHead->getContentSize() / 2);
			_spriteHead->setScale(c56 * 1.0f / wh);
		}
		else
		{
			_spriteHead->setScale(1);
		}
	}

	_nodeContent->removeAllChildren();
	float wmax = 0, hmax = 0;
	cLabel* label = nullptr;
	Size s;
	forr(descs.descs, k)
	{
		auto& d = descs.descs.at(k);
		_nodeContent->addChild(label = cLabel::create(d.text, eFont::smal));
		label->setColor(cc::to3B(d.color));
		label->setDimensions(wLabel, 0);
		s = label->getContentSize();
		label->setPosition(Vec2(0, hmax) + s / 2);
		wmax = std::max(wmax, s.width);
		hmax += s.height + 4;
	}
	_nodeContent->addChild(label = cLabel::create(name));
	label->setColor(sColor::YELLOW);
	s = label->getContentSize();
	label->setPosition(Vec2(0, hmax) + s / 2);
	wmax = std::max(wmax, s.width);
	hmax += s.height;
	_nodeContent->setContentSize(Size(wmax, hmax));
}

void uiDesc::show(bool head, bool back9)
{
	_nodeInner->setVisible(true);
	_nodePad->setVisible(back9);
	_spriteHead->setVisible(head);
	if (head)
	{
		_nodeContent->setPositionX(c56 + cInv);
		_nodeInner->setContentSize(Size(cc::getRight(_nodeContent), std::max(c56 * 1.0f, _nodeContent->getContentSize().height)));
		_spriteHead->setPosition(0, _nodeInner->getContentSize().height);
	}
	else
	{
		_nodeContent->setPosition(Vec2::ZERO);
		_nodeInner->setContentSize(Size(cc::getRT(_nodeContent)));
	}
	if (back9)
	{
		_nodeInner->setPosition(cInv, cInv);
		this->setContentSize(_nodeInner->getContentSize() + Size(cInv, cInv) * 2);
	}
	else
	{
		_nodeInner->setPosition(Vec2::ZERO);
		this->setContentSize(_nodeInner->getContentSize());
	}
}


void uiDesc::correctPosition()
{
	Vec2 v = _parent->convertToWorldSpace(_position - _anchorPointInPoints);
	Vec2 o = cc::vsOrigin();
	Vec2 s = cc::vsSize(1, 1);
	float x = std::max(0.0f, o.x - v.x);
	float y = std::max(0.0f, o.y - v.y);
	x = std::min(x, s.x - v.x - _contentSize.width);
	y = std::min(y, s.y - v.y - _contentSize.height);
	setPosition(_position + Vec2(x, y));
}

void uiDesc::correctPosition(const Node* target)
{
	Vec2 v = target->getParent()->convertToWorldSpace(target->getPosition()/* - target->getAnchorPointInPoints()*/);
	if (v.x < cc::vsCenter().x)
	{
		_position.x = v.x + target->getContentSize().width + _anchorPointInPoints.x;
	}
	else
	{
		_position.x = v.x - target->getContentSize().width - _contentSize.width + _anchorPointInPoints.x;
	}
	_position.y = v.y - _contentSize.height / 2 + _anchorPointInPoints.y;

	correctPosition();
}
