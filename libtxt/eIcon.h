#pragma once

// 图标
enum class eIcon
{
	eNone = -1,
	e0,
	equip0 = e0,
	// 武器
	weapon = equip0,
	// 防具
	eArm0,
	// 头盔
//	helmet = eArm0,
	// 项链
//	neck,
	// 护腕
	bracer = eArm0,
	// 盔甲
	clothes,
	// 腰带
//	belt,
	// 鞋子
	shoe,
	eArmEnd = shoe,
	equipEnd = eArmEnd,
	// 药品
	medicine,
	// 兽决
	shoujue,
	// 宝石
	stone,
	// 技能
	ski,
	eEnd = ski,
};

