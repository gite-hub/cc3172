#include "txtSki.h"
#include "_cc8.h"


const int txtSki::cTargetMax = 20;

sSkiCost txtSki::sCost::getCost(int hpMax, int ulv, int targetsCount)
{
	sSkiCost cost;
	if (ap > 0)
	{
		cost.ap = ap;
		return cost;
	}
	if (hpper > 0)
	{
		cost.hp += hpMax * hpper / 100;
	}
	if (lv > 0)
	{
		cost.mp += ulv / lv + mp;
	}
	else if (mp > 0)
	{
		cost.mp += mp;
	}
	else if (mps > 0)
	{
		cost.mp += mps * targetsCount;
	}
	return cost;
}


void txtSki::init(ulong act, ulong state, ulong sound, eSki e, int count /* = 1 */)
{
	sSki ski;
	ski.act = act;
	ski.state = state;
	ski.sound = sound;
	ski.count = count;
	_skis.insert(std::make_pair(_e = e, ski));
	_ski = &_skis.at(e);
}

void txtSki::insert(eSkiSelect select, eSkiPos pos)
{
	_ski->select = select;
	_ski->pos = pos;
	_ski->buff = eSkiBuff::eNone;
}

void txtSki::insert(eSkiSelect select, eSkiPos pos, eSkiBuff buff, eSkiPos buffpos)
{
	_ski->select = select;
	_ski->pos = pos;
	_ski->buff = buff;
	_ski->buffpos = buffpos;

}

void txtSki::insert(int ap_per, int mps, int lv /* = 0 */, int mp /* = 0 */)
{
	auto& c = _ski->cost;
	auto& d = _ski->descCost;
	if (isSpecial(_e))
	{
		c.ap = ap_per;
		d = cc::toString(c.ap) + "点" + cc8::cPropertyAp;
		return;
	}
	c.hpper = ap_per;
	c.mps = mps;
	c.lv = lv;
	c.mp = mp;
	if (c.hpper > 0)
	{
		// 最大气血
		d = toString("%d%%", c.hpper) + cc8::cPropertyHp;
	}
	if (c.lv > 0)
	{
		d += toString(",(%s/%d+%d)点", cc8::cLv.c_str(), c.lv, c.mp) + cc8::cPropertyMp;
	}
	else if (c.mp > 0)
	{
		d += cc::toString(c.mp) +"点" + cc8::cPropertyMp;
	}
	else if (c.mps > 0)
	{
		d += cc::toString(c.mps) + "点" + cc8::cPropertyMp + "×目标数";
	}
	if (d.front() == ',')
	{
		d.erase(d.begin());
	}
}

eSki txtSki::get0(eMenpai mp)
{
	switch (mp)
	{
//	case eMenpai::eNone:
//	case eMenpai::eMenpai0:
	case eMenpai::physics:
		return eSki::ePhysics0;
	case eMenpai::magic:
		return  eSki::eMagic0;
	case eMenpai::treat:
		return eSki::eTreat0;
	case eMenpai::assist:
		return eSki::eAssist0;
//	case eMenpai::eMenpaiEnd:
	}
	return eSki::eNone;
}

eSki txtSki::getEnd(eMenpai mp)
{
	switch (mp)
	{
//	case eMenpai::eNone:
//	case eMenpai::eMenpai0:
	case eMenpai::physics:
		return eSki::ePhysicsEnd;
	case eMenpai::magic:
		return eSki::eMagicEnd;
	case eMenpai::treat:
		return eSki::eTreatEnd;
	case eMenpai::assist:
		return eSki::eAssistEnd;
//	case eMenpai::eMenpaiEnd:
	}
	return eSki::eNone;
}



bool txtSki::isEd(eSki e)
{
	return e >= eSki::eSkied0 && e <= eSki::eSkiedEnd;
}

bool txtSki::isMenpai(eSki e)
{
	for (int mp = (int)eMenpai::e0; mp <= (int)eMenpai::eEnd; ++mp)
	{
		if (isMenpai(e, (eMenpai)mp))
		{
			return true;
		}
	}
	return false;
}

bool txtSki::isMenpai(eSki e, eMenpai mp)
{
	switch (mp)
	{
//	case eMenpai::eNone:
//	case eMenpai::eMenpai0:
	case eMenpai::physics:
		return e >= eSki::ePhysics0 && e <= eSki::ePhysicsEnd;
	case eMenpai::magic:
		return e >= eSki::eMagic0 && e <= eSki::eMagicEnd;
	case eMenpai::treat:
		return e >= eSki::eTreat0 && e <= eSki::eTreatEnd;
	case eMenpai::assist:
		return e >= eSki::eAssist0 && e <= eSki::eAssistEnd;
//	case eMenpai::eMenpaiEnd:
	}
	return false;
}

bool txtSki::isPet(eSki e)
{
	return e >= eSki::ePet0 && e <= eSki::ePetEnd;
}

bool txtSki::isSpecial(eSki e)
{
	return e >= eSki::eSpecial0 && e <= eSki::eSpecialEnd;
}


txtSki::txtSki()
{
	// 雷击
	init(0x0E30CD44, 0x00000000, 0xDDD270F5, eSki::leiji);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(0, 30);
	// 奔雷咒 2A997658 F1F26922
	init(0xF54C4025, 0x00000000, 0x040584F3, eSki::benleizhou, 3);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 30);
	// 落岩
	init(0x0AC30DE6, 0x00000000, 0x564F1090, eSki::luoyan);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 30);
	// 泰山压顶
	init(0x783F9D20, 0x00000000, 0x22FEF25E, eSki::taishanyading, 3);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 30);
	// 水攻
	init(0xF933209B, 0x00000000, 0x0071B681, eSki::shuigong);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 30);
	// 水漫金山 90E8589F 6EFC43B9 E99401D7  龙卷? 3D74BE12
	init(0x97311BAD, 0x00000000, 0x4F09C15D, eSki::shuimanjinshan, 3);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 30);
	// 烈火
	init(0xD112913D, 0x00000000, 0x3E2A375C, eSki::liehuo);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 30);
	// 地狱烈火 EB325D99 
	init(0x139426B5, 0x00000000, 0x2E88DCF4, eSki::diyuliehuo, 3);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 30);
	// 死亡召唤
	init(0x4E02EC44, 0x2C6223D4, 0x739A0BAB, eSki::siwangzhaohuan);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 0, 1, 10);
	// 力劈华山
	init(0xFF33B0EE, 0x00000000, 0x00000000, eSki::lipihuashan);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 0, 2, 50);
	// 法术防御
	init(0x00000000, 0xDEDEE983, 0x00000000, eSki::fashufangyu);
	insert(eSkiSelect::self, eSkiPos::mid, eSkiBuff::other, eSkiPos::mid);
	insert(0, 0, 1, 10);
	// 善恶有报
	init(0x8D8A818D, 0x00000000, 0x2174467F, eSki::shaneyoubao);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(0, 0, 1, 10);
	init(0x6B59951D, 0x00000000, 0x00000000, eSki::shanbao);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(0, 0, 1, 10);
	////////////////////////////////////////////////////////////////////////// 追加
	// 乱兵之计 0x6B934898
	init(0xE1E5EA57, 0x00000000, 0x0B2ED764, eSki::luanbingzhiji);
	insert(eSkiSelect::other, eSkiPos::mid, eSkiBuff::seal, eSkiPos::mid);
	insert(0, 30);
	// 剑荡四方
	init(0x729ADE62, 0x00000000, 0x0504D379, eSki::jiandangsifang, 3);
	insert(eSkiSelect::other, eSkiPos::mid);
	// 落叶萧萧
	init(0xBD677226, 0x00000000, 0x6061BB93, eSki::luoyexiaoxiao, 3);
	insert(eSkiSelect::other, eSkiPos::screen);
	// 天降灵葫 小 0xDCD7A875 
	init(0xF99822CE, 0x00000000, 0x00000000, eSki::tianjianglinghu, 5);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 0, 3, 30);
	init(0x75331968, 0x00000000, 0x00000000, eSki::tianjianglinghu, 4);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 0, 3, 30);
	init(0x75331968, 0x00000000, 0x00000000, eSki::tianjianglinghu2, 3);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 0, 3, 30);
	init(0xF99822CE, 0x00000000, 0x00000000, eSki::tianjianglinghu2, 2);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 0, 3, 30);
	init(0xDCD7A875, 0x00000000, 0x00000000, eSki::tianjianglinghu1, 1);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 0, 3, 30);
	// 地涌金莲
	init(0xC0A21E7F, 0x00000000, 0x00000000, eSki::diyongjinlian);
	insert(eSkiSelect::owner, eSkiPos::z1);
	insert(3, /*5*/0);
	////////////////////////////////////////////////////////////////////////// 物理
	// 横扫千军
	init(0x19C102D1, 0x56E05B32, 0x30D78CEF, eSki::hengsaoqianjun, 3);
	insert(eSkiSelect::other, eSkiPos::mid, eSkiBuff::other, eSkiPos::z1);
	insert(5, 0);
	// 后发制人
	init(0x22DFD2EA, 0x85B3D6F1, 0x39D047A5, eSki::houfazhiren);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(5, 0);
	// 破釜沉舟
	init(0x559C8ECF, 0x56E05B32, 0x795E59BA, eSki::pofuchenzhou, 4);
	insert(eSkiSelect::other, eSkiPos::z1, eSkiBuff::other, eSkiPos::z1);
	insert(5, 0);
	// 鹰击
//	init(0x82C9074A, 0x56E05B32, 0x61688718, eSki::pofuchenzhou2, 3);
//	insert(eSkiSelect::other, eSkiPos::mid, eSkiBuff::other, eSkiPos::z1);
//	insert(5, 0);
	// 狮搏
	init(0x096766A8, 0x00000000, 0xF3626BEC, eSki::shibo);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 30);
	// 浪涌
	init(0x3F820E0C, 0x00000000, 0x00000000, eSki::langyong, 3);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(0, 20);
	////////////////////////////////////////////////////////////////////////// 法师
	// 龙卷雨击 升龙 D4974969  闪电 E926E4D8 雷 F1F26922 
	// 水柱 D1772AED 6C5F8376  D61E2519 水漫? 56F9A205 
	init(0xA19EAB31, 0x00000000, 0xA39B4CA3, eSki::longjuanyuji, 5);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(0, 20);
	// 双龙戏珠
	init(0xA680A821, 0x00000000, 0x6F872F79, eSki::shuanglongxizhu, 2);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(0, 0, 0, 70);
	// 虾兵 召唤
	init(0x00000000, 0x00000000, 0x40E67E07, eSki::xiabing);
	insert(eSkiSelect::self, eSkiPos::mid);
	insert(0, 40);
	// 蟹将 召唤
	init(0x00000000, 0x00000000, 0x40E67E07, eSki::xiejiang);
	insert(eSkiSelect::self, eSkiPos::mid);
	insert(0, 40);
	// 血雨
	init(0x70758FA3, 0x56E05B32, 0x00000000, eSki::xueyu);
	insert(eSkiSelect::other, eSkiPos::mid, eSkiBuff::other, eSkiPos::z1);
	// 炎护
	init(0x6F18C62C, 0x8B468339, 0x00000000, eSki::yanhu);
	insert(eSkiSelect::owner, eSkiPos::mid, eSkiBuff::good, eSkiPos::top);
	////////////////////////////////////////////////////////////////////////// 奶爸
	// 唧唧歪歪
	init(0xC12C2663, 0x00000000, 0xDBB88662, eSki::jijiwaiwai);
	insert(eSkiSelect::owner, eSkiPos::mid);
	insert(1, 0);
	// 护法
	init(0xAB5DAE52, 0x061869D7, 0x2550B4D0, eSki::hufa, 3);
	insert(eSkiSelect::owner, eSkiPos::z1, eSkiBuff::good, eSkiPos::mid);
	insert(0, 0, 0, 100);
	// 解毒
	init(0xDE34B83E, 0x00000000, 0x57726FFB, eSki::jiedu);
	insert(eSkiSelect::owner, eSkiPos::mid);
	insert(0, 40);
	// 普渡众生 
	init(0x2FF74578, 0xD8857128, 0x2550B4D0, eSki::pudu);
	insert(eSkiSelect::owner, eSkiPos::z1, eSkiBuff::good, eSkiPos::top);
	insert(0, 50);
	// 杨刘甘霖
	init(0x380337C1, 0xD8857128, 0xA4B9B11E, eSki::yangliuganlin);
	insert(eSkiSelect::owner, eSkiPos::z1, eSkiBuff::good, eSkiPos::top);
	insert(0, 50);
	// 自在心法
	init(0x77592664, 0x00000000, 0x2550B4D0, eSki::zizaixinfa);
	insert(eSkiSelect::owner, eSkiPos::z1);
	insert(0, 50);
	// 推气过宫
	init(0x7EEC276B, 0x00000000, 0x04E42236, eSki::tuiqiguogong, 4);
	insert(eSkiSelect::owner, eSkiPos::screen);
	insert(0, 0, 0, 100);
	// 夺命咒
	init(0xA0E70F87, 0x00000000, 0x00000000, eSki::duomingzhou, 4);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(0, 20);
	////////////////////////////////////////////////////////////////////////// 辅助
	// 雷霆万钧
	init(0x279AF873, 0x5525C5FB, 0x040584F3, eSki::leitingwanjun, 3);
	insert(eSkiSelect::other, eSkiPos::z1, eSkiBuff::bad, eSkiPos::top);
	insert(0, 0, 0, 100);
	// 天雷斩  狗爪印 0xA5D7B0F7
	init(0x885ACBE1, 0xA5D7B0F7, 0x251670FB, eSki::tianleizhan, 3);
	insert(eSkiSelect::other, eSkiPos::z1, eSkiBuff::bad, eSkiPos::top);
	insert(0, 30);
	// 五雷轰顶
	init(0xFFD64CCA, 0x00000000, 0xDB4F9338, eSki::wuleihongding);
	insert(eSkiSelect::other, eSkiPos::z1);
	insert(0, 50);
	// 尸腐毒
	init(0x9F81494F, 0x839CC29A, 0x98BDEC63, eSki::shifudu);
	insert(eSkiSelect::owner, eSkiPos::z1, eSkiBuff::poison, eSkiPos::z1);
	insert(0, 30);
	// 修罗隐身
	init(0xBA7D5CD7, 0x00000000, 0x00000000, eSki::xiuluoyinshen);
	insert(eSkiSelect::owner, eSkiPos::mid, eSkiBuff::other, eSkiPos::mid);
	insert(0, 150);
	// 幽冥鬼眼
	init(0x07DF52CA, 0x21435203, 0xFBA099F0, eSki::youmingguiyan, 5);
	insert(eSkiSelect::owner, eSkiPos::mid, eSkiBuff::good, eSkiPos::mid);
	insert(0, 30);
	////////////////////////////////////////////////////////////////////////// 特技
	// 破血狂攻
	init(0x171544B2, 0x00000000, 0x4B800708, eSki::poxuekuanggong);
	insert(eSkiSelect::other, eSkiPos::mid);
	insert(64, 0);
	// 晶清诀 
	init(0x66150076, 0x00000000, 0xFBD946FB, eSki::jingqingjue, cTargetMax);
	insert(eSkiSelect::owner, eSkiPos::z_1);
	insert(120, 0);
	// 罗汉金钟
	init(0x62999D3D, 0x5C5C1544, 0x3BF3590C, eSki::luohanjinzhong, cTargetMax);
	insert(eSkiSelect::owner, eSkiPos::mid, eSkiBuff::other, eSkiPos::z_1);
	insert(120, 0);
	// 慈航普渡
	init(0xE1084D39, 0x00000000, 0x00000000, eSki::cihangpudu, cTargetMax);
	insert(eSkiSelect::owner, eSkiPos::z1);
	insert(120, 0);
	////////////////////////////////////////////////////////////////////////// BOSS
	// 三昧真火
	init(0x774B7CEF, 0x00000000, 0xF4A86696, eSki::sanmeizhenhuo);
	insert(eSkiSelect::other, eSkiPos::z_1);
	insert(0, 30);
	// 龙卷风
	init(0x4DB67680, 0x00000000, 0x550EEC3F, eSki::longjuanfeng, 4);
	insert(eSkiSelect::other, eSkiPos::screen);
	insert(0, 30);
	//////////////////////////////////////////////////////////////////////////
	// 普通攻击
	init(0x1D3FF13C, 0x00000000, 0x00000000, eSki::normalAtk);
	insert(eSkiSelect::other, eSkiPos::mid);
	// 必杀攻击 新0x4C117B7C 法术 0xDAD8AC20
	init(0xECD0E003, 0x00000000, 0x00000000, eSki::criAtk); // 居然和四法里的新暴击反了
	insert(eSkiSelect::other, eSkiPos::mid);
	// 药品红
	init(0x77D2082D, 0x00000000, 0xAFE0E635, eSki::medicineHp);
	insert(eSkiSelect::owner, eSkiPos::mid);
	// 药品蓝
	init(0x3E912705, 0x00000000, 0xAFE0E635, eSki::medicineMp);
	insert(eSkiSelect::owner, eSkiPos::mid);
	// 药品解封
	init(0x808CEB72, 0x00000000, 0xAFE0E635, eSki::medicineSeal);
	insert(eSkiSelect::owner, eSkiPos::mid);
	// 防御 0xF90D5594 ? 0x3622636F ? 默认声音呢
	init(0xAC3D253B, 0x00000000, 0x00000000, eSki::defense);
	insert(eSkiSelect::self, eSkiPos::mid);
	// 保护
	init(0xF013CEDF, 0x00000000, 0x4ADFB0ED, eSki::protect);
	insert(eSkiSelect::self, eSkiPos::mid);
	// 召唤
	init(0xF90D5594, 0x00000000, 0x40E67E07, eSki::summon);
	insert(eSkiSelect::self, eSkiPos::mid);
	// 捕捉 BE7DDF16
	init(0x6BA62F2C, 0x00000000, 0x00000000, eSki::grasp);
	insert(eSkiSelect::other, eSkiPos::z1);
	// 强身术 0x2BAD3C49
};


std::string txtSki::getName(eMenpai mp)
{
	switch (mp)
	{
// 	case eMenpai::eNone:
// 		break;
// 	case eMenpai::eMenpai0:
// 		break;
	case eMenpai::physics:
		return "攻系";
	case eMenpai::magic:
		return "法系";
	case eMenpai::treat:
		return "奶系";
	case eMenpai::assist:
		return "辅助";
// 	case eMenpai::eMenpaiEnd:
// 		break;
// 	default:
// 		break;
	}
	return "无";
}

const std::map<eSki, txtSki::sSki>& txtSki::getSkis()
{
	static txtSki s_skis;
	return s_skis._skis;
}


