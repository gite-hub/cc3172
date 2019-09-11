#include "cScript.h"

#include "_cc8.h"
#include "_ccu.h"

#include "cObject.h"
#include "uiMap.h"
#include "uiDialog.h"
#include "uiManager.h"

#include "../libtxt/txtMap.h"
#include "../libtxt/txtZz.h"


cScript* cScript::getInstance()
{
	static cScript* s_script = new cScript();
	return s_script;
}

static void goMap(ulong head, const std::string& name, const std::string& talk, eMap e, int x, int y)
{
	ccu::getManager()->getDialog()->load(head, name, talk, { cc8::cConfirm, cc8::cCancel }, [e, x, y](int select)
	{
		if (select == 0)
		{
			ccu::getMap()->load(e);
			ccu::getMap()->load(x, y);
		}
	});
}

static void goMap(ulong head, const std::string& name, eMap e, int x, int y)
{
	goMap(head, name, cc8::cGoMap + " #Y" + txtMap::getMaps().at(e).mapname, e, x, y);
}


static void goMap(ulong head, const std::string& name, const std::string& e, const std::string& x, const std::string& y)
{
	goMap(head, name, (eMap)std::atoi(e.c_str()), std::atoi(x.c_str()), std::atoi(y.c_str()));
}



bool cScript::run(ulong head, const std::string& name, const std::string& script)
{
	std::vector<std::string> strs;
	cc::split(script, "_", strs);
	const std::string& str = strs.front();
	int size = strs.size();
	if (str == txtMap::cTransmit)
	{
		goMap(head, name, strs.at(1), strs.at(2), strs.at(3));
		return true;
	}
	if (str == "mine")
	{
		eMod e = (eMod)std::atoi(strs.at(1).c_str());
		auto pet = cPet::getInstance()->getPet(e);
		auto skis = pet->eskis;
		pet->lvupEasy(txtZz::getZzs().at(e).takelv + ccp::lvGap);
		cRole::getInstance()->getHero()->addPet(pet);
		ccu::getManager()->toast(name + "+1");
	}
	return false;
}