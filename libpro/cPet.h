#pragma once
#include "sPet.h"
#include "cIndexCounter.h"

class cPet : public cUnique<sPet>
{
public:
	static cPet* getInstance();

	cPet();

	sPet* createPet(eMod e, const std::string& name = "");

	sPet* getPet(eMod e, const std::string& name = "");

	sPet* getPet(int unique);

	bool removePet(int unique);
};