#pragma once
#include "_inc.h"
#include "eMod.h"
#include "txtAction.h"

class txtMod
{
public:
	typedef txtAction::sAction sAct;
	struct sPart
	{
		ulong color;
		sAct maps, acts;
	};
	struct sMod
	{
		std::string name;
		sAct head, sound;
		std::vector<std::vector<int>> jjs;
		std::vector<sPart> parts;
	};
	txtMod();
private:
	void init(eMod m, const std::string& name);
	void insert(ulong head, ulong dialog);
	void insert(ulong atk, ulong atk2, ulong suffer, ulong magic, ulong def, ulong dead);
//	void insert(int offx, int atk1, int tak2, int atk3, int atk4, int magic);
	void insert(int offx, int atk1, int tak2, int magic);
	void insert(int offx, int atk, int magic);
	void insert(const std::vector<int>& jj1, const std::vector<int>& jj2);
	void insert(ulong color, ulong stand, ulong walk, ulong fight, ulong go, ulong atk, ulong atk2, ulong magic, ulong def, ulong suffer, ulong dead, ulong back);

	sMod* _mod;
	sPart _part;
protected:
	std::map<eMod, sMod> _mods;
public:
	static const std::map<eMod, sMod>& getMods();
};