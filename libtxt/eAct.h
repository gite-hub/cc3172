#pragma once

// 模型动作
enum class eAct
{
	// 站(地图)
	stand,
	// 走(地图)
	walk,
	// 站(战斗)
	fight,
	// 前进(战斗)
	go,
	// 攻击(战斗)
	atk,
	// 攻击2(战斗)
	atk2,
	// 施法(战斗)
	magic,
	// 防御(战斗)
	def,
	// 被打(战斗)
	suffer,
	// 死亡(战斗)
	dead,
	// 返回(战斗)
	back,

	// 头像
	head,
	// 对话头像
	dialog,

	// 攻击(音效)
	eAtk,
	// 攻击2(音效)
	eAtk2,
	// 施法(音效)
	eMagic,
	// 防御(音效)
	eDef,
	// 被打(音效)
	eSuffer,
	// 死亡(音效)
	eDead,

};