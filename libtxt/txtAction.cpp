#include "txtAction.h"

void txtAction::insert(sAction& act, ulong stand, ulong walk, ulong fight, ulong go, ulong atk, ulong atk2, ulong magic, ulong def, ulong suffer, ulong dead, ulong back, bool check0 /* = false */)
{
	if (!check0 || stand > 0)
	act.insert(std::make_pair(eAct::stand, stand));
	if (!check0 || walk > 0)
	act.insert(std::make_pair(eAct::walk, walk));
	if (!check0 || fight > 0)
	act.insert(std::make_pair(eAct::fight, fight));
	if (!check0 || go > 0)
	act.insert(std::make_pair(eAct::go, go));
	if (!check0 || atk > 0)
	act.insert(std::make_pair(eAct::atk, atk));
	if (!check0)
	{
		act.insert(std::make_pair(eAct::atk2, (atk2 == 0) ? atk : atk2));
	}
	else if (atk2 > 0)
	{
		act.insert(std::make_pair((atk == 0) ? eAct::atk : eAct::atk2, atk2));
	}
	if (!check0 || magic > 0)
	act.insert(std::make_pair(eAct::magic, magic));
	if (!check0 || def > 0)
	act.insert(std::make_pair(eAct::def, def));
	if (!check0 || suffer > 0)
	act.insert(std::make_pair(eAct::suffer, suffer));
	if (!check0 || dead > 0)
	act.insert(std::make_pair(eAct::dead, dead));
	if (!check0 || back > 0)
	act.insert(std::make_pair(eAct::back, back));
}

void txtAction::insert(sAction& act, ulong fight, ulong go, ulong atk, ulong atk2, ulong magic, ulong def, ulong suffer, ulong dead, ulong back, bool check0 /* = false */)
{
#if 0
	act.insert(std::make_pair(eAct::Fight, fight));
	act.insert(std::make_pair(eAct::Go, go));
	act.insert(std::make_pair(eAct::Atk, atk));
	act.insert(std::make_pair(eAct::Atk2, (atk2 == 0) ? atk : atk2));
	act.insert(std::make_pair(eAct::Magic, magic));
	act.insert(std::make_pair(eAct::Def, def));
	act.insert(std::make_pair(eAct::Suffer, suffer));
	act.insert(std::make_pair(eAct::Dead, dead));
	act.insert(std::make_pair(eAct::Back, back));
#else
	if (!check0 || fight > 0)
	act.insert(std::make_pair(eAct::fight, fight));
	if (!check0 || go > 0)
	act.insert(std::make_pair(eAct::go, go));
	if (!check0 || atk > 0)
	act.insert(std::make_pair(eAct::atk, atk));
	if (!check0)
	{
		act.insert(std::make_pair(eAct::atk2, (atk2 == 0) ? atk : atk2));
	}
	else if (atk2 > 0)
	{
		act.insert(std::make_pair((atk == 0) ? eAct::atk : eAct::atk2, atk2));
	}
	if (!check0 || magic > 0)
	act.insert(std::make_pair(eAct::magic, magic));
	if (!check0 || def > 0)
	act.insert(std::make_pair(eAct::def, def));
	if (!check0 || suffer > 0)
	act.insert(std::make_pair(eAct::suffer, suffer));
	if (!check0 || dead > 0)
	act.insert(std::make_pair(eAct::dead, dead));
	if (!check0 || back > 0)
	act.insert(std::make_pair(eAct::back, back));
#endif
}

void txtAction::insert(sAction& act, ulong stand, ulong walk)
{
	act.insert(std::make_pair(eAct::stand, stand));
	act.insert(std::make_pair(eAct::walk, walk));
}


void txtAction::insertHead(sAction& act, ulong head, ulong dialog)
{
	act.insert(std::make_pair(eAct::head, head));
	act.insert(std::make_pair(eAct::dialog, dialog));
}



void txtAction::insert(sAction& act, ulong atk, ulong atk2, ulong suffer, ulong magic, ulong def, ulong dead)
{
	act.insert(std::make_pair(eAct::eAtk, atk));
	act.insert(std::make_pair(eAct::eAtk2, (atk2 == 0) ? atk : atk2));
	act.insert(std::make_pair(eAct::eSuffer, suffer));
	act.insert(std::make_pair(eAct::eMagic, magic));
	act.insert(std::make_pair(eAct::eDef, def));
	act.insert(std::make_pair(eAct::eDead, dead));
}