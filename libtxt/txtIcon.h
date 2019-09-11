#pragma once
#include "_inc.h"
#include "eIcon.h"
#include "eSki.h"

class txtIcon
{
public:
	enum class eStone
	{
		eNone = -1,
		guangmang,
		heibaoshi,
		hongmanao,
		shelizi,
		taiyang,
		yueliang,
		feicui,
		shenmi,
	};
	struct sIcon
	{
		ulong uid;
		std::string name;
		std::string desc;
	};
	typedef std::map<int, sIcon> sIcons;
	txtIcon();
private:
	void init();
	void init(eIcon e);
	void insert(ulong uid, const std::string& name, const std::string&  desc = "");
	void insert(ulong uid, eStone e, const std::string&  name, const std::string&  desc = "");
	void insert(ulong uid, eSki e, const std::string&  name, const std::string&  desc = "");

	int _idx;
	sIcon _item;
	sIcons* _icon = nullptr;
protected:
	std::map<eIcon, sIcons> _icons;
public:
	static std::string getName(eIcon icon);
	static const std::map<eIcon, sIcons>& getIcons();
};