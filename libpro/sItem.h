#pragma once
#include "sStone.h"
#include "cIndexCounter.h"

// 物品
class sItem : public sUnique
{
public:
	// 类型
	bool setData(eIcon type, int id);
	// 填充pro
	void setData();
	// 图标数据
	const txtIcon::sIcon* getIcon() const { return _icon; }
	// 类型
	eIcon getType()const{ return _type; }
	// id
	int getId()const{ return _id; }
	// 价格
	void setPrice(int price){ _price = price; }
	// 价格
	int getPrice()const{ return _price; }
	// 加
	bool add(int count = 1);
	// 减
	bool sub(int count = 1);
	// 清空
	void clear(){ _num = 0; }
	// 有效
	bool isValid() const;
	// 有效
	operator bool()const;
	// 数量
	int getCount()const{ return _num; }
	// 描述
	void toDesc(sDescs& descs)const;
	void toDesc(sDescs& descs, eStone stone)const;
	// 可叠加
	bool isOverly() const;
	// 存档
	void save(bool price)const;
	// 读档
	void load(bool price);
	// 对比
	bool operator!=(const sItem& it)const;
	bool operator==(const sItem& it)const;
private:
	eIcon _type = eIcon::eNone;
	int _id, _num = 0, _price = 0;
	uint _pro;
	const txtIcon::sIcon* _icon = nullptr;
	friend class cEquip;
};
typedef std::vector<sItem*> sItems;