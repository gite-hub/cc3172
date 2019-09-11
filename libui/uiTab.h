#pragma once
#include "_inc.h"


class uiTab : public Node
{
public:
	CREATE_FUNC(uiTab);
// 	static uiTab* create(const std::string& tab, const std::string& tab2, const std::string& tab3 = "", const std::string& tab4 = "", const std::string& tab5 = "");
// 	static uiTab* create(const std::vector<std::string>& tabs);
protected:
	bool init(/*const std::vector<std::string>& tabs*/);

public:
	void load(const std::string& tab, const std::string& tab2, const std::string& tab3 = "", const std::string& tab4 = "", const std::string& tab5 = "");
	void load(const std::vector<std::string>& tabs);
protected:
	int _select;
	Menu* _menu = nullptr;
	Sprite* _spriteDark = nullptr;
	std::vector<MenuItem*> _menuItems;
	std::vector<Sprite*> _spriteLights;
	std::vector<cLabel*> _labels;
public:
	static const int c40;
	std::function<void(int, int)> onTab = nullptr;
};