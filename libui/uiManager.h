#pragma once
#include "_inc.h"

class uiManager;
namespace ccu
{
	uiManager* getManager();
	void setManager(uiManager* ui);
}

class uiAddpointer;
class uiChannel;
class uiChat;
class uiDialog;
class uiDye;
class uiHeader;
class uiInput;
class uiItem;
class uiJob;
class uiMenu;
class uiModSelect;
class uiRole;
class uiPets;
class uiPetSelector;
class uiSee;
class uiShichen;
class uiShop;
class uiSkiSelect;
class uiSmap;
// ui管理器
class uiManager : public Node
{
public:
	CREATE_FUNC(uiManager);

protected:
	bool init();

public:
	void load(sRole* role);

public:
	uiAddpointer* getAddpointer() { return _addpointer; }
protected:
	uiAddpointer* _addpointer = nullptr;
 
	// 添加频道(频道类型, 名字, 文本)
	// #0~#119 表情
	// #W #Y #R #G #B #M #O 颜色
public:
	void addChannel(const std::string& name, const std::string& text);
	void addChannel(const std::string& text);
	void addChannelSys(const std::string& text);

	uiChannel* getChannel() { return _channel; }
protected:
	uiChannel* _channel = nullptr;
	cButton* _buttonMsg = nullptr;
public:
	uiChat* getChat() { return _chat; }
protected:
	uiChat* _chat = nullptr;

	// 对话
public:
	uiDialog* getDialog(){ return _dialog; }
protected:
	uiDialog* _dialog = nullptr;

	// 右上角的头像和血条
public:
	uiHeader* getHeader(bool pet) { return pet ? _headerPet : _headerRole; }
protected:
	uiHeader* _headerRole = nullptr;
	uiHeader* _headerPet = nullptr;

	// 输入
public:
	uiInput* getInput() { return _input; }
protected:
	uiInput* _input = nullptr;

	//物品
public:
	uiItem* getItem() { return _item; }
protected:
	uiItem* _item = nullptr;

	// 添加任务(标题, 内容)
	// 重复的标题会被认为更新任务
public:
	void addJob(const std::string& title, const std::string& text);
protected:
	uiJob* _job = nullptr;

	// 菜单 窗口下方的一排图标
public:
	uiMenu* getMenu(){ return _menu; }
protected:
	uiMenu* _menu = nullptr;

public:
	uiModSelect* getModSelect() { return _modSelect; }
protected:
	uiModSelect* _modSelect = nullptr;

	// 宝宝
public:
	uiPets* getPet(){ return _pet; }
protected:
	uiPets* _pet = nullptr;

public:
	uiPetSelector* getPetSelector() { return _petSelector; }
protected:
	uiPetSelector* _petSelector = nullptr;
	// 角色
public:
	uiRole* getRole() { return _uirole; }
protected:
	uiRole* _uirole = nullptr;

	// 查看
public:
	uiSee* getSee(){ return _see; }
protected:
	uiSee* _see = nullptr;

	// 时辰 左上角
public:
	uiShichen* getShichen(){ return _shichen; }
protected:
	uiShichen* _shichen = nullptr;

	// 购买
public:
	uiShop* getShop(){ return _shop; }
protected:
	uiShop* _shop = nullptr;

	// 技能选择
public:
	uiSkiSelect* getSkiSelect(){ return _skillSelect; }
protected:
	uiSkiSelect* _skillSelect = nullptr;

 	// 小地图
public:
	uiSmap* getSmap(){ return _smap; }
protected:
	uiSmap* _smap = nullptr;


	// 添加提示(文本, 停留:秒)
public:
	void toast(const std::string& text, float second = 5);

public:
	void show(bool shown);

	bool isFight();

protected:
	bool _isShown = true;
	sRole* _role = nullptr;
public:
	std::function<bool()> onFight = nullptr;
};