#pragma once
#include "uiPad.h"

class uiDesc : public uiPad
{
public:
	static uiDesc* create(int width);
	static uiDesc* create();
protected:
	bool init(int width);
public:
	void load(bool scale, const sDescs& descs);

	void load(const std::string& desc, const sColor& color = sColor::WHITE);

	void show(bool head, bool back9);
	
	void correctPosition();
	void correctPosition(const Node* target);
protected:
	int _width;
	cSprite1* _spriteHead = nullptr;
	Node* _nodeContent = nullptr;
	Node* _nodeInner = nullptr;
public:
	static const int cInv, c56, c192;
};
