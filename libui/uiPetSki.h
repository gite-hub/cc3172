#pragma once
#include "uiDesc.h"

class uiPetSki : public Node
{
public:
	CREATE_FUNC(uiPetSki);
// 	static uiPetSki* create(const eSkis& eskis);
// 
// 	static uiPetSki* create();

	static uiDesc* toDesc(eSki eski, Node* target);

protected:
	bool init(/*const eSkis& eskis*/);

public:
	void load(const eSkis& eskis);


protected:
	Menu* _menu = nullptr;
	std::vector<MenuItem*> _menuItems;
	std::vector<cSprite1*> _sprites;
	cSprite9* _spriteSelect = nullptr;

public:
	static const int c4;
};