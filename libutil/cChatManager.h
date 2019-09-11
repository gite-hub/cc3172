#pragma once
#include "_inc.h"
#include <stack>

class cChatManager
{
public:
	static cChatManager* getInstance();

	bool init(const s888& firstColor = s888::WHITE);

public:
	void setString(const std::string& text);

private:
	std::stack<s888> _colors;
	s888 _firstColor;
public:
	struct sChar
	{
		s888 color;
		std::string text;
	};
	struct sLine
	{
		std::vector<sChar> chars;
	};
	typedef std::vector<sLine> sLines;
private:
	sLines _lines;

	void setLine(sLine& line, const std::string& text);
public:
	const sLines& getLines() const { return _lines; }
};