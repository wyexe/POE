#ifndef __LFZL_CHEATDLL_CORE_FEATURE_SEARCHER_OBJECTFILTER_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_SEARCHER_OBJECTFILTER_H__

#include <string>
#include <functional>
#include <GameStruct.h>
#include <vector>


class CNpc;
class CMonster;
class CPlayer;
class CChest;
class CFilterConfig;
class CWorldItem;
class CItem;
class CObjectFilter
{
public:
	CObjectFilter() = default;
	~CObjectFilter() = default;

	// Npc
	static BOOL FindNpc_By_Name(_In_ CONST std::wstring& wsNpcName, _Out_ CNpc& Npc);

	
	// Monster
	static BOOL FindMonster_By_Name(_In_ CONST std::wstring& wsMonsterName, _Out_ CMonster& Monster);
	static BOOL GetNearestAttackMonster_By_Filter(_Out_ CMonster& Monster, _In_opt_ CFilterConfig* pFilterConfig = nullptr);

	// Item
	static BOOL FindBagItem_By_Name(_In_ CONST std::wstring& wsItemName, _Out_ CItem& Item);

	// Chest
	static BOOL FindChest_By_Name(_In_ CONST std::wstring& wsChestName, _Out_ CChest& Chest);
	

	// Player
	static BOOL FindPlayer_By_Name(_In_ CONST std::wstring& wsPlayerName, _Out_ CPlayer& Player);


	// WorldItem
	static BOOL GetNearestWorldItem_By_Filter(_Out_ CWorldItem& WorldItem, _In_opt_ CFilterConfig* pFilterConfig = nullptr);


private:
	//
	static BOOL FindNpc_By_Func(_Out_ CNpc& Npc, _In_ std::function<BOOL(CONST CNpc&)> Ptr);

	//
	static BOOL FindMonster_By_Func(_Out_ CMonster& Monster, _In_ std::function<BOOL(CONST CMonster&)> Ptr);

	//
	static BOOL FindPlayer_By_Func(_Out_ CPlayer& Player, _In_ std::function<BOOL(CONST CPlayer&)> Ptr);

	//
	static BOOL FindChest_By_Func(_Out_ CChest& Chest, _In_ std::function<BOOL(CONST CChest&)> Ptr);

	//
	static BOOL FindWorldItem_By_Func(_Out_ CWorldItem& WorldItem, _In_ std::function<BOOL(CONST CWorldItem&)> Ptr);

	//
	static BOOL FindItem_By_Func(_Out_ CItem& Item, _In_ std::function<BOOL(CONST CItem&)> Ptr);
private:
	template<typename T>
	static BOOL FindObject_By_FuncPtr(_In_ std::function<UINT(std::vector<T>&)> FuncPtr, _Out_ T& Instance, _In_ std::function<BOOL(CONST T &)> Ptr)
	{
		BOOL bExist = FALSE;
		std::vector<T> Vec;

		std::sort(Vec.begin(), Vec.end());
		if (FuncPtr(Vec) != 0)
		{
			auto itr = std::find_if(Vec.begin(), Vec.end(), Ptr);
			if (itr != Vec.end())
			{
				Instance = *itr;
				bExist = TRUE;
			}
		}

		return bExist;
	}
};


#endif // !__LFZL_CHEATDLL_CORE_FEATURE_SEARCHER_OBJECTFILTER_H__
