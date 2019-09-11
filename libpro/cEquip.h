#pragma once
#include "sItem.h"

class cEquip
{
public:
	enum class eProPerty
	{
		// 为了主技能排序
		eNone = -1,
		hp,
		atk,
		def,
		avoid,
		mp,
		mtk,
		mef,
		hit,
		speed,
	};
	struct sProperty
	{
		eProPerty pro = eProPerty::eNone;
		int value = 0;
		operator bool() const;
		std::string toString(const std::string& str = " ") const;
	};
	typedef std::vector<sProperty> sPropertys;
#pragma pack (push)
#pragma pack (1)
	union sPro
	{
		uint pro;
		struct
		{
			// 主属性
			uint pro1 : 8;
			uint pro2 : 8;
			// 简易
			uint easy : 1;
			// 精致
			uint delicate : 1;
			// 溅射
			uint spurting : 1;
			// 嗜血幡
			uint zhuiji : 1;
			// 石头 +1
			uint stone : 4;
			// 特技 +1
			uint special : 4;
			// 追加 +1
			uint zhuijia : 4;
		};

		void apply(eIcon type);
	};
#pragma pack (pop)
	struct sHead
	{
		eStone stone = eStone::eNone;
		bool isSpurting, isZhuiji;
		eSki specail, zhuijia;
	};
	// 武器/防具
	static bool isEquip(eIcon type);
	// 武器
	static bool isWeapon(eIcon type);
	// 防具
	static bool isArmor(eIcon type);
	// 头盔
//	static bool isHelmet(eIcon type);
	// 项链
//	static bool isNeck(eIcon type);
	// 护腕
	static bool isBracer(eIcon type);
	// 盔甲
	static bool isClothes(eIcon type);
	// 腰带
//	static bool isBelt(eIcon type);
	// 鞋子
	static bool isShoe(eIcon type);

	static void apply(const sItem* equip, sPropertys& pros);
	static void apply(const sItem* equip, sDescs& descs);
	// 携带等级
	static int getTakeLv(const sItem* equip);
	// 装备等级
	static int getLv(const sItem* equip);
	// 取装备栏索引
	static int getIdx(eIcon type);
	// 取装备类型
	static std::vector<eIcon>& getTypes();
	// 取装备by装备栏索引
	static eIcon getType(int idx);
	// 嗜血幡 无心插柳 特技 追加
	static sHead getHead(const sItem* equip);
	// 镶嵌宝石
	static void setStone(eIcon type, std::vector<eStone>& stones);
	// 镶嵌宝石
	static void setStone(eStone stone, sPropertys& pros);
	// 镶嵌宝石
	static void setStone(sItem* equip, eStone stone);
	// 装备总伤害
	int getAtk(const sItems& equips, sStone* stone);
	// 名字
	static std::string getName(eProPerty epro);
	// 套装c3起效
	static const int c2, c4;
};