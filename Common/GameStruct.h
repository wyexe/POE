#ifndef __LFZL_COMMON_GAMESTRUCT_H__
#define __LFZL_COMMON_GAMESTRUCT_H__

#include <Windows.h>

#define 人物基址 0x13F9780
#define 人物基址偏移1 0x38
#define 人物基址偏移2 0x14
#define 人物基址偏移3 0x8
#define 人物基址偏移4 0x1C0
#define 人物基址偏移5 0x1DC
#define 人物基址偏移6 0x2C
#define 人物基址偏移7 0x14
#define 人物名字基址 0x153D450
#define 人物等级偏移 0x40
#define 物品遍历偏移1 0x1C4
#define 物品遍历偏移2 0x4D70
#define 物品遍历偏移3 0x88
#define 物品遍历偏移4 0x30
#define 物品绑定偏移 0x84
#define 物品鉴定偏移 0x54
#define 物品需求等级偏移 0x1E0
#define 物品颜色偏移 0x40
#define 仓库偏移1 0x898
#define 仓库偏移2 0xA78
#define 仓库页偏移1 0x9B4
#define 仓库页偏移2 0xAFC
#define 仓库页索引偏移1 0x708
#define 仓库页索引偏移2 0x8E4
#define 当前仓库页偏移 0xB08
#define 怪物名字偏移 0x58
#define UI偏移1 0x1E4
#define UI偏移2 0xAA4
#define UI遍历偏移1 0x708
#define Ui显示偏移 0x754
#define 人物UI偏移 0x1978
#define 背包UI偏移 0xA88
#define 异界地图宝鉴偏移 0xB20
#define Npc出售窗口偏移 0xB18
#define Npc对话窗口偏移 0xB08
#define 丢弃物品确认窗口偏移 0xAE0
#define 鼠标右键使用物品UI偏移 0x9C4
#define 鼠标是否使用物品偏移 0x964
#define State偏移1 0x24
#define StateObject偏移 0x28
#define 当前地图偏移 0xB6C
#define 周围对象遍历偏移1 0x4B18
#define 周围对象遍历偏移2 0x234
#define Buff遍历偏移 0x98
#define EffectUI偏移 0xB68
#define Effect数组偏移 0x8E8
#define EffectID数组偏移 0x8F4
#define 游戏坐标比例基址 0x12F7C78
#define 当前屏幕坐标Y偏移 0x1938
#define 当前屏幕坐标X偏移 0x1934
#define 游戏坐标转换偏移1 0x1644
#define 坐标转换基址2 0x12F7DC8
#define 游戏坐标X转换偏移 0x1944
#define 游戏坐标Y转换偏移 0x1948
#define 游戏坐标转换偏移2 0x1924
#define 游戏坐标转换偏移3 0x1B4
#define 游戏坐标转换偏移4 0x64
#define 当前鼠标游戏坐标X 0x193C
#define 是否走路中偏移 0x480

////一些固定的偏移//////////////////////////////////////////////////////////////////////
#define 人物基址偏移8		0xC
#define 人物HP偏移 0x2C
#define 人物MAXHP偏移 0x2C + 0x4
#define 人物MP偏移 0x54
#define 人物MAXMP偏移 0x54 + 0x4
#define 人物护盾偏移 0x78
#define 人物MAX护盾偏移 0x78 + 0x4
#define 人物名字偏移 0xC
#define 物品ID偏移   0x14
#define 物品左上角坐标 0x4
#define 物品右上角坐标 0x8
#define 物品左下角坐标 0xC
#define 物品右下角坐标 0x10
#define 物品属性表偏移 0x0
#define UI名字偏移	Ui显示偏移 - 0x20
#define 周围对象遍历偏移3 0xC
#define 游戏坐标转换偏移5 游戏坐标转换偏移4 - 0x14
#define 当前鼠标游戏坐标Y 当前鼠标游戏坐标X + 0x4

#define ReadDWORD(x) CGameMemory::GetInstance().ReadProcDWORD(x)
#define ReadBYTE(x)  CGameMemory::GetInstance().ReadProcBYTE(x)
#define ReadFloat(x) CGameMemory::GetInstance().ReadProcFloat(x)
#define GameRun      TRUE
#define StopGame	 ::Sleep(1)

#define MAX_OBJECT_CLIENT_DIS 70.0f
#define MIN_OBJECT_CLIENT_DIS 7.0f
#define MAX_OBJECT_MOUSE_DIS  300
#define BAG_ITEM_CELL_WIDTH   37
#define BAG_ITEM_CELL_HEIGHT  38





enum em_Equi_Color
{
	None,
	White,
	Magic,
	Rate,
	Legend,

};

enum class em_Object_Type
{
	// 头盔
	Helmets, 
	// 戒指
	Ring,
	// 衣服
	BodyArmours,
	// 武器
	Weapons,
	// 宝石
	Gems,
	// 护身符
	Amulets,
	// 护盾
	Shields,
	// 手套
	Gloves,
	// 腰带
	Belts,
	// 鞋子
	Boots,
	// 药剂
	Flasks,
	// 命运卡
	DivinationCards,
	// 普通物品
	Currency,
	// 玩家
	Player,
	// Npc
	Npc,
	// 活动Npc或者任务物品
	QuestObjects,
	// 怪物
	Monster,
	// 地面物品
	WorldItem,
	// 箱子
	Chests,
	// 传送点
	Waypoint,
	// 传送门
	AreaTransition,
	// 杂物
	MiscellaneousObjects,
	// 地图
	Maps,
	// 地图碎片
	MapFragment,
	// 珠宝(天赋宝石)
	Jewels,
	//
	Other
};

enum em_ItemPtrArrayIndex : DWORD
{
	em_ItemPtrArrayIndex_Bag				= 0x0,
	em_ItemPtrArrayIndex_Equi_BodyArmours	= 0x1,
	em_ItemPtrArrayIndex_Equi_Weaspon		= 0x2,
	em_ItemPtrArrayIndex_Equi_Shields		= 0x3,
	em_ItemPtrArrayIndex_Helmets			= 0x4,
	em_ItemPtrArrayIndex_Amulets			= 0x5,
	em_ItemPtrArrayIndex_Ring1				= 0x6,
	em_ItemPtrArrayIndex_Ring2				= 0x7,
	em_ItemPtrArrayIndex_Gloves				= 0x8,
	em_ItemPtrArrayIndex_Boots				= 0x9,
	em_ItemPtrArrayIndex_Belts				= 0xA,
	em_ItemPtrArrayIndex_Flasks				= 0xB,
	em_ItemPtrArrayIndex_Cursor				= 0xC, // 鼠标点击后的物品
	em_ItemPtrArrayIndex_Jweels				= 0x17, // 天赋页上的珠宝
};

struct Point
{
	int X, Y;

	Point()
	{
		X = Y = NULL;
	}

	Point(_In_ int dwX, _In_ int dwY) : X(dwX), Y(dwY)
	{

	}

	bool operator == (CONST Point& Point_) CONST
	{
		return this->X == Point_.X && this->Y == Point_.Y;
	}

	bool operator != (CONST Point& Point_) CONST
	{
		return this->X != Point_.X || this->Y != Point_.Y;
	}

	BOOL IsZero() CONST
	{
		return X == 0 || Y == 0;
	}

	float GetFloatX() CONST
	{
		return static_cast<float>(X);
	}
	float GetFloatY() CONST
	{
		return static_cast<float>(Y);
	}
};



/// -------------------------------------------------------

CONST static Point g_BagUi_Item_StartPos(819, 432);

#define ITEM_ATTRIBUTE_RES_INDEX_BASE 0


#endif // !__LFZL_COMMON_GAMESTRUCT_H__
