#include "cChatManager.h"


static const std::map<char, s888>& getSharpColors()
{
	static std::map<char, s888> s_colorMap;
	if (s_colorMap.empty())
	{
		s_colorMap.insert(std::make_pair('W', s888::WHITE));
		s_colorMap.insert(std::make_pair('Y', s888::YELLOW));
		s_colorMap.insert(std::make_pair('R', s888::RED));
		s_colorMap.insert(std::make_pair('G', s888::GREEN));
		s_colorMap.insert(std::make_pair('B', s888::BLUE));
		s_colorMap.insert(std::make_pair('M', s888::MAGENTA));
		s_colorMap.insert(std::make_pair('O', s888::ORANGE));
		s_colorMap.insert(std::make_pair('X', s888::BLACK));
	}
	return s_colorMap;
}


cChatManager* cChatManager::getInstance()
{
	static cChatManager* s_chat = new cChatManager();
	return s_chat;
}


bool cChatManager::init(const s888& firstColor /* = s565::WHITE */)
{
	_firstColor = firstColor;
	return true;
}


void cChatManager::setLine(sLine& line, const std::string& text)
{
	int size = text.size();
	int ic = 0;
	for (int k = 0; k < size; ++k)
	{
		if (text[k] != '#' || k + 1 >= size)
		{
			continue;
		}
		const auto& colorMap = getSharpColors();
		if (colorMap.find(text[k + 1]) == colorMap.end())
		{
			continue;
		}
		auto color = colorMap.at(text[k + 1]);
		sChar chr;
		if (_colors.empty())
		{
			chr.color = _firstColor;
			_colors.push(color);
		}
		else if (color == _colors.top())
		{
			chr.color = color;
			_colors.pop();
		}
		else
		{
			chr.color = _colors.top();
			_colors.push(color);
		}
		if (ic < k)
		{
			chr.text = text.substr(ic, k - ic);
			line.chars.push_back(chr);
		}
		ic = k + 2;
		++k;
	}
	if (ic < size)
	{
		sChar chr;
		chr.color = _colors.empty() ? _firstColor : _colors.top();
		chr.text = text.substr(ic, size - ic);
		line.chars.push_back(chr);
	}
}



void cChatManager::setString(const std::string& text)
{
	while (!_colors.empty())
	{
		_colors.pop();
	}

	std::vector<std::string> enters;
	cc::split(text, "\r\n", enters);

	_lines.resize(enters.size());
	forv(_lines, k)
	{
		_lines[k].chars.clear();
		setLine(_lines[k], enters[k]);
	}
}