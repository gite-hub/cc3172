#include "txtIcon.h"

txtIcon::txtIcon()
{
	sIcons table;
	for (int e = (int)eIcon::e0; e <= (int)eIcon::eEnd; ++e)
	{
		_icons.insert(std::make_pair((eIcon)e, table));
	}
	init();
}


void txtIcon::init(eIcon e)
{
	_idx = -1;
	_icon = &_icons.at(e);
}


void txtIcon::insert(ulong uid, const std::string& name, const std::string& desc /* = "" */)
{
	_item.uid = uid;
	_item.name = name;
	_item.desc = desc;
	_icon->insert(std::make_pair(++_idx, _item));
}

void txtIcon::insert(ulong uid, eStone e, const std::string& name, const std::string& desc /*= ""*/)
{
	_item.uid = uid;
	_item.name = name;
	_item.desc = desc;
	_icon->insert(std::make_pair((int)e, _item));
}

void txtIcon::insert(ulong uid, eSki e, const std::string& name, const std::string& desc /* = "" */)
{
	_item.uid = uid;
	_item.name = name;
	_item.desc = desc;
	_icon->insert(std::make_pair((int)e, _item));
}



void txtIcon::init()
{
	init(eIcon::weapon);
	insert(0x090CCA18, "桃印");
	insert(0xAA8F427F, "赭石");
	insert(0x976BFD27, "璧铗");
	insert(0xCC013376, "青铜");
	insert(0xE8F34110, "金错");
	insert(0x0B0AB6FB, "惊涛雪");
	insert(0xE98BD873, "醉浮生");
// 	init(eIcon::helmet);
// 	insert(0x6C180E40, "布帽");
// 	insert(0x20787B2D, "面具");
// 	insert(0x94D9A3E0, "纶巾");
// 	insert(0x48DA4E36, "缨络");
// 	insert(0x42795B75, "羊角");
// 	insert(0x968E1D79, "水晶");
// 	insert(0x69937480, "乾坤");
// 	init(eIcon::neck);
// 	insert(0x164EEEA7, "五色飞石");
// 	insert(0xFC424978, "珍珠链");
// 	insert(0x70D75356, "苍魂珠");
// 	insert(0x117C58D5, "江湖夜雨");
// 	insert(0x5DBB74F3, "高速之星");
// 	insert(0xC88803AD, "八卦坠");
// 	insert(0xEE8F5986, "碧水青龙");
	init(eIcon::bracer);
	insert(0x1C28FB6F, "针腕");
	insert(0x9D0CFE72, "青铜护腕");
	insert(0xDD8EA49F, "玛瑙护腕");
	insert(0xC7A0F7FB, "琉璃护腕");
	insert(0x0B4042DF, "玳瑁护腕");
	insert(0x158E1623, "七星宝腕");
	insert(0x41BCD2C1, "护腕", "狼宝特供");
	init(eIcon::clothes);
	insert(0xEEAA3C26, "皮衣");
	insert(0x87FB5568, "鳞甲");
	insert(0xB09EECF3, "锁子甲");
	insert(0xF045EF07, "紧身衣");
	insert(0x6F015575, "钢甲");
	insert(0x52C4B2BC, "夜魔披风");
	insert(0x67D1D9D8, "龙骨甲");
// 	init(eIcon::belt);
// 	insert(0xF9502CBE, "缎带");
// 	insert(0x618F66ED, "银腰带");
// 	insert(0x28D305DA, "水晶腰带");
// 	insert(0xF0E1864B, "琥珀腰链");
// 	insert(0x0EB143A5, "魔童大牙");
// 	insert(0xA069B155, "双魂引");
// 	insert(0x10C86EA1, "兽王");
	init(eIcon::shoe);
	insert(0x850B4461, "皮靴");
	insert(0xD31EF251, "马靴");
	insert(0x2142F94B, "侠客履");
	insert(0x423882CD, "神行靴");
	insert(0xEE0695FA, "绿靴");
	insert(0xEF75A65E, "追星踏月");
	insert(0x3F383BF8, "九州");

	init(eIcon::medicine);
	insert(0x8EC6D2DD, "金香玉", "加血/复活");
	insert(0xA32D0B05, "蛇蝎美人", "补充魔法");
	insert(0xE24080F3, "五龙丹", "解封");
	init(eIcon::stone);
	insert(0x41656FA0, eStone::guangmang, "光芒石");
	insert(0x750B0C1A, eStone::heibaoshi, "黑宝石");
	insert(0xD9DCF799, eStone::hongmanao, "红玛瑙");
	insert(0xCB7F4075, eStone::shelizi, "舍利子");
	insert(0xC365BC0A, eStone::shenmi, "神秘石");
	insert(0x8FE88E79, eStone::taiyang, "太阳石");
	insert(0xB6D2F539, eStone::yueliang, "月亮石");
	insert(0xA1D20A1D, eStone::feicui, "翡翠石");
	init(eIcon::ski);
	insert(0x3D3D78F3, eSki::fanji, "反击", "受到物理攻击时，有几率自动反击");
	insert(0xE141908F, eSki::fanzhen, "反震", "受到物理攻击时，有几率反弹伤害");
	insert(0x55F4B952, eSki::xixue, "吸血", "物理攻击时，吸取气血");
	insert(0x6C86F4A9, eSki::lianji, "连击", "有几率连续两次物理攻击，物理攻击效果降低，如果受到反震，则攻击中断");
	insert(0xA51CF9C7, eSki::bisha, "必杀", "物理攻击时，必杀几率增加");
	insert(0x11633A2A, eSki::yinshen, "隐身", "自动附加修罗隐身效果，物理攻击能力降低，隐身状态下无法使用法术");
	insert(0xB9908036, eSki::touxi, "偷袭", "免疫反震和反击");

	insert(0x34B4C183, eSki::mozhixin, "魔之心", "法术伤害提高");
	insert(0xDB29D33A, eSki::fashulianji, "法术连击", "使用法术攻击目标时会有几率出现连续2次攻击敌人");
	insert(0x4F639062, eSki::fashubaoji, "法术暴击", "使用法术攻击目标时会有几率使法术伤害值加倍");

	insert(0xCBD47EEA, eSki::shenyou, "神佑", "战斗死亡时有几率复活为正常状态");
	insert(0xF54027B4, eSki::ganzhi, "感知", "破解修罗隐身");
	insert(0x3314B434, eSki::minjie, "敏捷", "速度提高");
	insert(0xD5558C37, eSki::chidun, "迟钝", "速度降低");
	insert(0xBC48A88A, eSki::leixishou, "雷吸收", "有几率免受雷属性法术伤害，并按应受伤害的大小恢复气血，吸收失败也可减少受到的法术伤害");
	insert(0xEEC82E05, eSki::tuxishou, "土吸收", "有几率免受土属性法术伤害，并按应受伤害的大小恢复气血，吸收失败也可减少受到的法术伤害");
	insert(0x7E61822B, eSki::huoxishou, "火吸收", "有几率免受火属性法术伤害，并按应受伤害的大小恢复气血，吸收失败也可减少受到的法术伤害");
	insert(0x2818771C, eSki::shuixishou, "水吸收", "有几率免受水属性法术伤害，并按应受伤害的大小恢复气血，吸收失败也可减少受到的法术伤害");
	// 宝宝
	insert(0x4D730D41, eSki::leiji, "雷击");
	insert(0xF84778EC, eSki::benleizhou, "奔雷咒");
	insert(0x4FFF7EF3, eSki::luoyan, "落岩");
	insert(0xDBCEA859, eSki::taishanyading, "泰山压顶");
	insert(0x856157DC, eSki::shuigong, "水攻");
	insert(0xE4FE37B2, eSki::shuimanjinshan, "水漫金山");
	insert(0x970D2EC6, eSki::liehuo, "烈火");
	insert(0x66EE1142, eSki::diyuliehuo, "地狱烈火");
	insert(0xA0720B84, eSki::siwangzhaohuan, "死亡召唤", "攻击的同时有一定几率使敌人附加死亡禁锢效果，禁锢回合内无法被复活");
	insert(0x6C17AEDA, eSki::lipihuashan, "力劈华山");
	insert(0xE605C61C, eSki::shaneyoubao, "善恶有报", "善报还是恶报，这是个问题");
	insert(0x80C816A0, eSki::fashufangyu, "法术防御");
	// 追加 还有个横扫
	insert(0x7A1407DF, eSki::luanbingzhiji, "乱兵之计"); // 紫
	insert(0xD0BB9A24, eSki::jiandangsifang, "剑荡四方");
	insert(0x2D3B819A, eSki::luoyexiaoxiao, "落叶萧萧"); // 紫
	insert(0x67D5991D, eSki::tianjianglinghu, "天降灵葫");
	insert(0xCE8CB22F, eSki::diyongjinlian, "地涌金莲"); // 紫 红 A0F46876
	// 物理
	insert(0x6B83BDF6, eSki::hengsaoqianjun, "横扫千军", "连续攻击对方,需休息一回合，休息时不会受到控制类法术影响"); // 紫
	insert(0x79653216, eSki::houfazhiren, "后发制人", "蓄力一回合后临时提高伤害和速度，自动攻击目标"); // 红
	insert(0xAB4C2094, eSki::pofuchenzhou, "破釜沉舟", "同时攻击对方多个目标，需休息一回合");
	insert(0xCE16F6B2, eSki::shibo, "狮搏", "穿刺攻击"); // 紫
	insert(0x80CDFA9E, eSki::langyong, "浪涌", "根据对方防御值临时提升一定伤害对多个敌人进行物理攻击");
	// 法术
	insert(0x2676743F, eSki::longjuanyuji, "龙卷雨击"); // 紫 红 D3F19693
	insert(0x9FCD0A4A, eSki::shuanglongxizhu, "双龙戏珠");
	insert(0x388A6945, eSki::xiabing, "虾兵", "召唤小兵助战");
	insert(0x5C67B6E8, eSki::xiejiang, "蟹将", "召唤法师助战");
	insert(0xC9FF5246, eSki::xueyu, "血雨", "终极奥义，需休息1回合");
	insert(0xFFC83C18, eSki::yanhu, "炎护", "用魔法抵御伤害");
	// 治疗
	insert(0x7A4F9A4B, eSki::jijiwaiwai, "唧唧歪歪");
	insert(0x550B87D3, eSki::hufa, "护法", "全面提高攻击力和防御力"); // 紫
	insert(0x02C32C11, eSki::jiedu, "解毒");
	insert(0x3D5E8617, eSki::pudu, "普渡", "目标死亡则复活，目标回血则结算"); // 紫
	insert(0xD6316B38, eSki::tuiqiguogong, "推气过宫"); // 紫
	insert(0xCB25181A, eSki::duomingzhou, "夺命咒"); // 紫
	// 辅助
	insert(0x01A3AB52, eSki::leitingwanjun, "雷霆万钧", "有几率降低法术防御");
	insert(0x02701645, eSki::tianleizhan, "天雷斩", "有几率降低物理防御"); // 紫  红 9E4709EE
	insert(0x332611A0, eSki::wuleihongding, "五雷轰顶", "成功则减少气血及魔法，失败只减少少量气血");
	insert(0x10D1A4D1, eSki::shifudu, "尸腐毒"); // 紫
	insert(0xEEB6C278, eSki::xiuluoyinshen, "修罗隐身", "战斗中隐藏自己或队友的身形，令对手无法攻击，隐身状态下不能施展法术"); // 红
	insert(0xF61D8F27, eSki::youmingguiyan, "幽冥鬼眼", "获得感知能力"); // 红
	// 特技
	insert(0xABC43258, eSki::poxuekuanggong, "破血狂攻", "连续物理穿刺攻击");
	insert(0x900ED6CA, eSki::jingqingjue, "晶清诀", "解除各种异常状态，并恢复气血");
	insert(0x61F085F4, eSki::luohanjinzhong, "罗汉金钟", "受到的法术伤害减半");
	insert(0xBE552849, eSki::cihangpudu, "慈航普渡", "复活所有队友并恢复全部气血，使用者气血减少，魔法清空");
	// boss
	insert(0x4129740E, eSki::sanmeizhenhuo, "三昧真火"); // 紫 红 B0AC2344
	insert(0x3A13D0ED, eSki::longjuanfeng, "龙卷风"); // 紫 红 F661204E

	// 牛刀
	insert(0x2A43146C, eSki::normalAtk, "攻击");
	insert(0x4D104C64, eSki::defense, "防御");

	insert(0x00000000, eSki::protect, "保护");
	insert(0x00000000, eSki::summon, "召唤");
	insert(0x00000000, eSki::grasp, "捕捉");
	insert(0x00000000, eSki::escape, "逃跑");



	init(eIcon::shoujue);
	const auto& skis = _icons.at(eIcon::ski);
	for (int e = (int)eSki::ePet0; e <= (int)eSki::ePetEnd; ++e)
	{
		const auto& ski = skis.at(e);
		insert(ski.uid, (eSki)e, ski.name, "给召唤兽学习技能");
	}
}


std::string txtIcon::getName(eIcon icon)
{
	switch (icon)
	{
// 	case eIcon::eNone:
// 		break;
// 	case eIcon::eIcon0:
// 		break;
// 	case eIcon::equip0:
// 		break;
	case eIcon::weapon:
		return "武器";
// 	case eIcon::eArm0:
// 		break;
// 	case eIcon::helmet:
// 		return "头盔";
// 	case eIcon::neck:
// 		return "项链";
	case eIcon::bracer:
		return "护腕";
	case eIcon::clothes:
		return "盔甲";
// 	case eIcon::belt:
// 		return "腰带";
	case eIcon::shoe:
		return "鞋子";
// 	case eIcon::eArmEnd:
// 		break;
// 	case eIcon::equipEnd:
//		break;
	case eIcon::medicine:
		return "药品";
	case eIcon::shoujue:
		return "兽决";
	case eIcon::ski:
		return "技能";
// 		break;
// 	case eIcon::eIconEnd:
// 		break;
// 	default:
// 		break;
	}
	return "";
}

const std::map<eIcon, txtIcon::sIcons>& txtIcon::getIcons()
{
	static txtIcon s_icons;
	return s_icons._icons;
}