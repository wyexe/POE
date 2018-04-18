#ifndef __LFZL_COMMON_GAMESTRUCT_H__
#define __LFZL_COMMON_GAMESTRUCT_H__

#include <Windows.h>

#define 人物基址 0x13F9760
#define 人物基址偏移1 0x38
#define 人物基址偏移2 0x14
#define 人物基址偏移3 0x8
#define 人物基址偏移4 0x1C0
#define 人物基址偏移5 0x1DC
#define 人物基址偏移6 0x2C
#define 人物基址偏移7 0x14
#define 人物名字基址 0x153D430
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
#define 周围对象遍历偏移1 0x28
#define 周围对象遍历偏移2 0x1D8
#define 周围对象遍历偏移3 0x8E0
#define 周围对象遍历偏移4 0x4B18


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
#define 周围对象遍历偏移5		0x230


#define ReadDWORD(x) CGameMemory::GetInstance().ReadProcDWORD(x)
#define ReadBYTE(x)  CGameMemory::GetInstance().ReadProcBYTE(x)
#define GameRun      TRUE
#define StopGame	 ::Sleep(1)


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

struct Point
{
	DWORD X, Y;

	Point()
	{
		X = Y = NULL;
	}

	Point(_In_ DWORD dwX, _In_ DWORD dwY) : X(dwX), Y(dwY)
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

	DWORD Encode()
	{
		return X << 16 | Y;
	}

	static Point Decode(_In_ DWORD dwValue)
	{
		Point Pt;
		Pt.Y = dwValue & 0xFFFF;
		Pt.X = dwValue >> 16;
		return Pt;
	}

	BOOL IsZero() CONST
	{
		return X == 0 || Y == 0;
	}
};








#endif // !__LFZL_COMMON_GAMESTRUCT_H__
