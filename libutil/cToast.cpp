#include "cToast.h"
#include "_ccu.h"
#include "cLabel.h"
#include "cText.h"


bool cToast::init(const std::string& text, float second)
{
	if (!Sprite9::init(ccu::cDesc))
	{
		return false;
	}
	if (text.empty())
	{
		return false;
	}
	auto chat = cChatManager::getInstance();
	chat->init();
	chat->setString(text);
	const auto& lines = chat->getLines();
	if (lines.empty())
	{
		return false;
	}
	const auto& cs = lines.front().chars;
	if (lines.size() == 1 && cs.empty())
	{
		return false;
	}
	const auto& c = cs.front();
	Node* node = nullptr;
	if (lines.size() == 1 && cs.size() == 1)
	{
		cLabel* label = cLabel::create(c.text);
		label->setColor(cc::to3B(c.color));
		node = label;
	}
	else
	{
		cText* t = cText::create();
		t->setString(lines);
		node = t;
	}

	const int c8 = 8;
	Size size(node->getContentSize().width + c8 * 4, std::max(32.0f, node->getContentSize().height + c8));
	this->addChild(node);
	this->setContentSize(size);
	node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	node->setPosition(size / 2);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(cToast::updateOnce), second);
	return true;
}


void cToast::updateOnce(float dt)
{
	cToastManager::getInstance()->remove(this);
}




//////////////////////////////////////////////////////////////////////////
cToastManager* cToastManager::getInstance()
{
	static cToastManager* s_tag = new cToastManager();
	return s_tag;
}

bool cToastManager::add(Node* parent, const std::string& text, float second)
{
	cToast* tag = cToast::create(text, second);
	tag->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	int x = cc::vsCenter().x;
	int y;
	if (_tags.empty())
	{
		y = cc::vsY(0.9f);
	}
	else
	{
		y = _tags.back()->getPositionY() + _tags.back()->getAnchorPointInPoints().y - _tags.back()->getContentSize().height - 2;
	}
	_tags.push_back(tag);
	tag->setPosition(x, y - tag->getAnchorPointInPoints().y);
	parent->addChild(tag, INT_MAX);
	return true;
}


bool cToastManager::remove(cToast* tag)
{
	tag->removeFromParent();
	const auto& it = ccc_find_it(_tags, tag);
	if (it != _tags.end())
	{
		_tags.erase(it);
	}
	return true;
}