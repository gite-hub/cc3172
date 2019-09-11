#pragma once
#include "_inc.h"

enum class eFont { smaller = 14, smal = 20, normal = 24, big = 27, bigger = 30, e100, e125, e150, e200 };

class cLabelString
{
public:
	void setNumber(u64 u, bool moneyColor = false);
	u64 getNumber() { return _number; }

	virtual void setString(const std::string& text);
protected:
	virtual void doMoneyColor(const sColor& color);
	u64 _number;
};

class cLabelEasy : public LabelAtlas, public cLabelString
{
public:
	cLabelEasy();
	static cLabelEasy* create(const std::string& text, eFont e);
	static cLabelEasy* create(const std::string& text);
	static cLabelEasy* create(eFont e);
	static cLabelEasy* create();

	

	virtual void setString(const std::string& text);

protected:
	bool init(const std::string& text, eFont e);

public:
	void doMoneyColor(const sColor& color);

	static const int cOffy;
};


class cLabel : public Label, public cLabelString
{
public:
	static cLabel* create(const std::string& text, eFont e);
	static cLabel* create(const std::string& text);
	static cLabel* create(eFont e);
	static cLabel* create();

	virtual void setString(const std::string& text);
protected:
	bool init(const std::string& text, eFont e);

public:
	void doMoneyColor(const Color3B& color);
};
