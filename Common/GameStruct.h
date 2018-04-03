#ifndef __LFZL_COMMON_GAMESTRUCT_H__
#define __LFZL_COMMON_GAMESTRUCT_H__


/*
#define 人物基址				0x013F24F0
#define 人物基址偏移1		0x38
#define 人物基址偏移2		0x14
#define 人物基址偏移3		0x8
#define 人物基址偏移4		0x1C0
#define 人物基址偏移5		0x1D8
#define 人物基址偏移6		0x2C
#define 人物基址偏移7		0x14
#define 人物名字基址			0x1536180
#define 人物等级偏移			0x40

#define 物品遍历偏移1		0x1C4
#define 物品遍历偏移2		0x4AAC
#define 物品遍历偏移3		0xC
#define 物品遍历偏移4		0x4CE8
#define 物品遍历偏移5		0x88
#define 物品遍历偏移6		0x44
#define 物品遍历偏移7		0x84
#define 物品遍历偏移8		0x4CE8
#define 物品遍历偏移9		0x88
#define 物品遍历偏移10		0x30

#define 物品绑定偏移			0x84
#define 物品鉴定偏移			0x54
#define 物品颜色偏移			0x40
#define 物品需求等级偏移		0x1E0

#define 仓库偏移1			0x894
#define 仓库偏移2			0xA78
#define 仓库页偏移1			0x9B4
#define 当前仓库页偏移		0xB08
#define 仓库页偏移2			0xAFC
#define 仓库页索引偏移1		0x708
#define 仓库页索引偏移2		0x8E4
#define 怪物名字偏移			0x58

#define 周围对象遍历偏移1		0x28
#define 周围对象遍历偏移2		0x1D8
#define 周围对象遍历偏移3		0x8E0
#define 周围对象遍历偏移4		0x4A94*/
#define 人物基址 0x13FB540
#define 人物基址偏移1 0x38
#define 人物基址偏移2 0x14
#define 人物基址偏移3 0x8
#define 人物基址偏移4 0x1C0
#define 人物基址偏移5 0x1DC
#define 人物基址偏移6 0x2C
#define 人物基址偏移7 0x14
#define 人物名字基址 0x153F1F8
#define 人物等级偏移 0x40
#define 物品遍历偏移1 0x1C4
#define 物品遍历偏移2 0x4B30
#define 物品遍历偏移3 0xC
#define 物品遍历偏移4 0x4D70
#define 物品遍历偏移5 0x88
#define 物品遍历偏移6 0x44
#define 物品遍历偏移7 0x84
#define 物品遍历偏移8 0x4D70
#define 物品遍历偏移9 0x8889
#define 物品遍历偏移10 0x30
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
#define 人物MAXHP偏移 人物HP偏移 + 0x4
#define 人物MP偏移 0x54
#define 人物MAXMP偏移 人物MP偏移 + 0x4
#define 人物护盾偏移 0x78
#define 人物MAX护盾偏移 人物护盾偏移 + 0x4
#define 人物名字偏移 0xC
#define 物品ID偏移   0x14
#define 物品左上角坐标 0x4
#define 物品右上角坐标 0x8
#define 物品左下角坐标 0xC
#define 物品右下角坐标 0x10
#define 物品属性表偏移 0x0
#define 周围对象遍历偏移5		0x230
#endif // !__LFZL_COMMON_GAMESTRUCT_H__
