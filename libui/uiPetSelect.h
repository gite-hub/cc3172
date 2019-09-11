#pragma once
#include "uiPad.h"
#include "ui/UIScrollView.h"

class cPetSelect
{
public:
	static Node* createHeader(const sPet* pet, int inv);
	static cButton* createButton(const sPet* pet, int inv);
	static void loadHeader(const sPet* pet, Node* node);
	static void loadButton(const sPet* pet, cButton* button);
protected:
	bool init(Node* parent);

	void load(int showSize, Node* parent, const sPets& pets);

	sPets _pets;
	cMenu* _menu = nullptr;
	std::vector<cButton*> _buttons;
	ui::ScrollView* _scrollView = nullptr;

public:
	static const int c5, c8, c56, cTagSprite, cTagName, cTagLv;
	std::function<void(const sPet*, int)> onSelect = nullptr;
};


class uiPetSelect : public Node, public cPetSelect
{
public:
//	static uiPetSelect* create(int showSize, const sPets& pets);
	static uiPetSelect* create(int showSize);
	static uiPetSelect* create();
protected:
	bool init(int showSize/*, const sPets& pets*/);

public:
	void load(const sPets& pets);
	void load(int showSize, const sPets& pets);
};



class uiPetSelector : public uiPad, public cPetSelect
{
public:
//	static uiPetSelector* create(int showSize, const sPets& pets);
	static uiPetSelector* create(int showSize);
	static uiPetSelector* create();
protected:
	bool init(int showSize/*, const sPets& pets*/);

public:
	void load(const sPets& pets);
	void load(int showSize, const sPets& pets);

protected:
	Node* _node = nullptr;
};