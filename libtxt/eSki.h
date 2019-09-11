#pragma once

// 自己,己方,对方
enum class eSkiSelect { self, owner, other };
// 显示: 顶部,中,底部, 画面
enum class eSkiPos{ top, mid, z1, z_1, screen };
// 无,封印,良性,恶性,读
enum class eSkiBuff { eNone = -1, seal, good, bad, poison, other };
// 技能消耗
struct sSkiCost 
{ 
	int hp = 0, mp = 0, ap = 0;
	operator bool() const
	{
		return hp > 0 || mp > 0 || ap > 0;
	}
};
// 技能
enum class eSki
{
	eNone = -1,
	e0,
	// 被动技能
	eSkied0 = e0,
	// 物理被动
	eAtkd0 = eSkied0, 
	// 反击
	fanji = eAtkd0,
	// 反震
	fanzhen,
	// 吸血
	xixue,
	// 连击
	lianji,
	// 必杀
	bisha,
	// 隐身
	yinshen,
	// 偷袭
	touxi,
	eAtkdEnd = touxi,
	// 法术被动
	eMagicd0,
	// 魔之心
	mozhixin = eMagicd0,
	// 法术连击
	fashulianji,
	// 法术暴击
	fashubaoji,
	eMagicdEnd = fashubaoji,
	// 神佑
	shenyou,
	// 感知
	ganzhi,
	// 敏捷
	minjie,
	// 迟钝
	chidun,
	// 法术吸收
	leixishou,
	tuxishou,
	huoxishou,
	shuixishou,
	eSkiedEnd = shuixishou,
	// 宝宝技能
	ePet0,
	// 雷击
	leiji = ePet0,
	// 奔雷咒
	benleizhou,
	// 落岩
	luoyan,
	// 泰山压顶
	taishanyading,
	// 水攻
	shuigong,
	// 水漫金山
	shuimanjinshan,
	// 烈火
	liehuo,
	// 地狱烈火
	diyuliehuo,
	// 死亡召唤
	siwangzhaohuan,
	// 力劈华山
	lipihuashan,
	// 善恶有报
	shaneyoubao,
	// 法术防御
	fashufangyu,
	ePetEnd = fashufangyu,
	// 追加
	eZhuijia0, 
	// 乱兵之计
	luanbingzhiji = eZhuijia0,
	// 剑荡四方
	jiandangsifang,
	// 落叶萧萧
	luoyexiaoxiao,
	// 天降灵葫
	tianjianglinghu,
	// 地涌金莲
	diyongjinlian,
	eZhuijiaEnd = diyongjinlian,
	// 物理
	ePhysics0,
	// 横扫千军
	hengsaoqianjun = ePhysics0,
	// 后发制人
	houfazhiren,
	// 破釜沉舟
	pofuchenzhou,
	// 狮搏
	shibo,
	// 浪涌
	langyong,
	ePhysicsEnd = langyong,
	// 法师
	eMagic0,
	// 龙卷雨击
	longjuanyuji = eMagic0,
	// 双龙戏珠
	shuanglongxizhu,
	// 虾兵
	xiabing,
	// 蟹将
	xiejiang,
	// 血雨
	xueyu,
	// 炎护
	yanhu,
	eMagicEnd = yanhu,
	// 治疗
	eTreat0,
	// 叽叽歪歪
	jijiwaiwai = eTreat0,
	// 护法
	hufa,
	// 解毒
	jiedu,
	// 普渡
	pudu,
	// 推气过宫
	tuiqiguogong,
	// 夺命咒
	duomingzhou,
	eTreatEnd = duomingzhou,
	// 辅助
	eAssist0,
	// 雷霆万钧
	leitingwanjun = eAssist0,
	// 天雷斩
	tianleizhan,
	// 五雷轰顶
	wuleihongding,
	// 尸腐毒
	shifudu,
	// 修罗隐身
	xiuluoyinshen,
	// 幽冥鬼眼
	youmingguiyan,
	eAssistEnd = youmingguiyan,
	// 特技
	eSpecial0,
	// 破血狂攻
	poxuekuanggong,
	// 晶清诀
	jingqingjue = eSpecial0,
	// 罗汉金钟
	luohanjinzhong,
	// 慈航普渡
	cihangpudu,
	eSpecialEnd = cihangpudu,
	eBoss0,
	// 三昧真火
	sanmeizhenhuo = eBoss0,
	// 龙卷风
	longjuanfeng,
	eBossEnd = longjuanfeng,
	// 普通攻击
	normalAtk,
	// 暴击攻击
	criAtk,
	// 善报
	shanbao,
	// 天降灵葫1
	tianjianglinghu1,
	// 天降灵葫23
	tianjianglinghu2,
	// 杨刘甘霖
	yangliuganlin,
	// 自在心法
	zizaixinfa,
	// 药品红
	medicineHp,
	// 药品蓝
	medicineMp,
	// 药品解封
	medicineSeal,
	// 防御
	defense,
	// 保护
	protect,
	// 召唤
	summon,
	// 捕捉
	grasp,
	// 逃跑
	escape,
};
