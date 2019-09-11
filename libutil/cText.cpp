#include "cText.h"
#include "_ccu.h"

cText* cText::create(int width /* = 0 */)
{
	CREATE(cText, eFont::normal, width);
}

bool cText::init(eFont e, int width)
{
	if (!ui::RichText::init())
	{
		return false;
	}
	_efnt = e;
	ignoreContentAdaptWithSize(false);
	setFontSize((int)e);
	setFontFace(ccu::cArial);
	_index = width == 0 ? cc::vsSize().width : width;
	setContentSize(Size(_index, 0));
	return true;
}


void cText::setString(const std::string& text)
{
	setString("", text);
}


void cText::setString(const std::string& name, const std::string& text)
{
	auto chat = cChatManager::getInstance();
	chat->init();

	if (name.empty())
	{
		chat->setString(text);
	}
	else
	{
		chat->setString("[" + name + "]" + text);
	}
	setString(chat->getLines());
}

void cText::setString(const cChatManager::sLines& lines)
{
	_richElements.clear();
	_formatTextDirty = true;
	setContentSize(Size(_index, 0));
	int index = -1;
	forv(lines, k)
	{
		const auto& cs = lines.at(k).chars;
		forv(cs, i)
		{
			const auto& c = cs.at(i);
			cLabel* label = cLabel::create(c.text, _efnt);
			label->setColor(cc::to3B(c.color));
#if 0
			ui::RichElementCustomNode* text = ui::RichElementCustomNode::create(++index, label->getColor(), 0xFF, label);
#else
			ui::RichElementText* text = ui::RichElementText::create(++index, label->getColor(), 0xFF, label->getString(), ccu::cFnt, (int)_efnt);
#endif
			pushBackElement(text);
		}
		if (k < _size_ - 1)
		{
			pushBackElement(ui::RichElementNewLine::create(++index, Color3B::WHITE, 0xFF));
		}
	}
	formatText();
	float w = 0, h = 0;
	for (const auto& node : _protectedChildren)
	{
		w = std::max(w, node->getPositionX() - node->getAnchorPointInPoints().x + node->getContentSize().width);
		h = std::max(h, node->getPositionY() - node->getAnchorPointInPoints().y + node->getContentSize().height);
	}
	setContentSize(Size(w, h));
}