#pragma once
#include "_inc.h"
#include "ui/UIScrollView.h"

class cGrids
{
public:
	static cButton* createButton(const sItem* item);
	static void loadButton(cButton* button, const sItem* item);
	static void loadButton(cButton* button, ulong uhead);
	static void loadButton(cButton* button, int count);
	static void loadButton(cButton* button, bool selected);
protected:
	bool init(ui::ScrollView* scrollView);

public:
	void load(const sItems& items);
	void load(int index, int count);
	void setMutex(bool mutex);
	int getSelect() const;
	const std::vector<int>& getSelects() { return _selects; }
	void clearSelects();
	void setButtonString(const std::string& str1, const std::string& str2 = "");
protected:
	bool isValid(int index);
	bool _isMutex = true;
	std::vector<int> _selects;

	sItems _items;

	std::string _str1, _str2;
	Menu* _menu = nullptr;
	std::vector<cButton*> _buttons;
public:
	static const int c72, cTagHead, cTagCount, cTagCountBack, cTagSelect;
	std::function<void(const sItem*, int, bool)> onSelect = nullptr;
	std::function<void(const sItem*, int, int)> onClick = nullptr;
};