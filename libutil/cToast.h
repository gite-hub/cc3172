#pragma once
#include "cSprite.h"

class cToast : public Sprite9
{
public:
	static cToast* create(const std::string& text, float second){ CREATE(cToast, text, second); }

protected:
	virtual bool init(const std::string& text, float second);

public:
	void updateOnce(float dt);
};


class cToastManager
{
public:
	static cToastManager* getInstance();

	bool add(Node* parent, const std::string& text, float second);

	bool remove(cToast* tag);

private:
	std::list<cToast*> _tags;
};