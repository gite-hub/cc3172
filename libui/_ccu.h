#pragma once
#include "../libutil/_ccu.h"

namespace ccu
{
	// 地图全局
	static const float zMap = -1.0f;
	static const float zMapObj = zMap + 0.1f;
	static const float zMapMask = zMap + 0.2f;
	static const float zMapFont = zMap + 0.3f;
	// 地图局部
	static const int zMapTop = 1;
	static const int zMapSay = 2;
	// toast INT_MAX
	static const int zDialog = INT_MAX - 1;



	static const ulong uDialogName = 0x804455A1;
	static const ulong uItemSelect = 0x10921CA7;
	static const ulong uRed = 0x00000227;
	static const ulong uRed2 = 0x30F737D8;
	static const ulong uGreen = 0xC52B2dE3;
	static const ulong uGreen2 = 0x3CF8F9FE;
//	static const ulong uPack = 0xA393A808;
//	static const ulong uHeadRole = 0x2178F38B;
//	static const ulong uHeadPet = 0x203CE1F7;
	static const ulong uWait = 0x4EE0010A;
	static const ulong uStrong = 0x2BAD3C49;
	static const ulong uTransmit = 0x7F4CBC8C;
	static const ulong uMapClick = 0x0D98AC0A;

	// 面板
	static const std::string cPad = "pad.png";
	static const std::string cRect = "rect.png";
	static const std::string cRect2 = "rect2.png";
	static const std::string cTitle = "title.png";
	static const std::string cClose = "close.png";

	// 头像
	static const std::string cHeader = "header.png";

	// 血条
	static const std::string cBarBack = "bar_back.png";
	static const std::string cBarHp = "bar_hp.png";
	static const std::string cBarMp = "bar_mp.png";
	static const std::string cBarAp = "bar_ap.png";
	static const std::string cBarExp = "bar_exp.png";

	// 菜单
// 	static const std::string cMenuAtk = "attack.png";
// 	static const std::string cMenuAct = "action.png";
// 	static const std::string cMenuAchieve = "achieve.png";
	static const std::string cMenuJob = "menu_job.png";
	static const std::string cMenuTeam = "menu_team.png";
	static const std::string cMenuPack = "menu_pack.png";
	static const std::string cMenuSys = "menu_sys.png";
//	static const std::string cMenuFriend = "friend.png";
	static const std::string cMenuVisible = "menu_switch.png";

	// 消息
	static const std::string cMessageFold = "msg_fold.png";
	static const std::string cMessageUnfold = "msg_unfold.png";

	static const std::string cJobFold = "job_fold.png";
	static const std::string cJobUnfold = "jbo_unfold.png";

	// 加点
	static const std::string cAddpoint = "addpoint.png";
	static const std::string cSubpoint = "subpoint.png";

	// 分页
	static const std::string cTabDark = "tab_dark.png";
	static const std::string cTabLight = "tab_light.png";

	// 格子 翻页
	static const std::string cGrids = "grids.png";
	static const std::string cAddpage = "addpage.png";
	static const std::string cSubpage = "subpage.png";

	// 装备
	static const std::string cEquipBracer = "equip_bracer.png";
	static const std::string cEquipWeapon = "equip_weapon.png";
	static const std::string cEquipClothes = "equip_clothes.png";
	static const std::string cEquipShoe = "equip_shoe.png";

	// 宝宝
	static const std::string cFight = "fight.png";

	// 合
	static const std::string cAddBaby = "addbaby.png";
	static const std::string cCompose = "compose.png";
}