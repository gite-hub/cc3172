#pragma once
#include "uiPad.h"

class uiPet;
class uiPetCompose;
class uiPets : public uiPad
{
public:
	static uiPets* create(sRole* role);

protected:
	bool init(sRole* role);

public:
	void load(sRole* role);

	uiPet* getuiPet() const { return _pet; }
protected:
	int _select;
	sRole* _role = nullptr;
	uiPet* _pet = nullptr;
	uiPetCompose* _petCompose = nullptr;
};