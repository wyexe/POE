#ifndef __LFZL_CHEATDLL_CORE_FEATURE_CONFIG_FILTERCONFIG_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_CONFIG_FILTERCONFIG_H__

#include <GameStruct.h>

class CWorldItem;
class CMonster;
class CItem;
class CFilterConfig
{
public:
	CFilterConfig() = default;
	~CFilterConfig() = default;

	static CFilterConfig& GetInstance();
public:
	BOOL Initialize();
public:
	// 是否拾取地面物品
	BOOL IsTakeWorldItem(_In_ CONST CWorldItem& WorldItem) CONST;

	// 是否保留该物品(背包|仓库)
	BOOL IsKeepItem(_In_ CONST CItem& Item) CONST;

	// 是否攻击该怪物
	BOOL IsAttackMonster(_In_ CONST CMonster& Monster) CONST;
private:

};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_CONFIG_FILTERCONFIG_H__
