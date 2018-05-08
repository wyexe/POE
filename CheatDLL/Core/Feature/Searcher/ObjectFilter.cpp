#include "ObjectFilter.h"
#include "ObjectSearcher.h"
#include <algorithm>
#include <Core/Feature/Config/FilterConfig.h>
#include <Core/Object/Item.h>
#include <Core/Feature/Attribute/Bag/BagAttribute.h>

BOOL CObjectFilter::FindNpc_By_Name(_In_ CONST std::wstring& wsNpcName, _Out_ CNpc& Npc)
{
	return FindNpc_By_Func(Npc, [wsNpcName](CONST CNpc& Instance) { return wsNpcName == Instance.GetName(); });
}

BOOL CObjectFilter::FindMonster_By_Name(_In_ CONST std::wstring& wsMonsterName, _Out_ CMonster& Monster)
{
	return FindMonster_By_Func(Monster, [wsMonsterName](CONST CMonster& Instance) { return Instance.GetName() == wsMonsterName; });
}

BOOL CObjectFilter::GetNearestAttackMonster_By_Filter(_Out_ CMonster& Monster, _In_opt_ CFilterConfig* pFilterConfig /*= nullptr*/)
{
	return FindMonster_By_Func(Monster, [pFilterConfig](CONST CMonster& Instance) { return pFilterConfig == nullptr ? TRUE : pFilterConfig->IsAttackMonster(Instance); });
}

BOOL CObjectFilter::FindBagItem_By_Name(_In_ CONST std::wstring& wsItemName, _Out_ CItem& Item)
{
	return FindItem_By_Func(Item, [wsItemName](CONST CItem& Instance) { return Instance.GetName() == wsItemName; });
}

BOOL CObjectFilter::FindChest_By_Name(_In_ CONST std::wstring& wsChestName, _Out_ CChest& Chest)
{
	return FindChest_By_Func(Chest, [wsChestName](CONST CChest& Instance) { return Instance.GetName() == wsChestName; });
}

BOOL CObjectFilter::FindPlayer_By_Name(_In_ CONST std::wstring& wsPlayerName, _Out_ CPlayer& Player)
{
	return FindPlayer_By_Func(Player, [wsPlayerName](CONST CPlayer& Instance) { return Instance.GetName() == wsPlayerName; });
}

BOOL CObjectFilter::GetNearestWorldItem_By_Filter(_Out_ CWorldItem& WorldItem, _In_opt_ CFilterConfig* pFilterConfig /*= nullptr*/)
{
	return FindWorldItem_By_Func(WorldItem, [pFilterConfig](CONST CWorldItem& Instance) {  return pFilterConfig == nullptr ? TRUE : pFilterConfig->IsTakeWorldItem(Instance); });
}

BOOL CObjectFilter::FindNpc_By_Func(_Out_ CNpc& Npc, _In_ std::function<BOOL(CONST CNpc&)> Ptr)
{
	return FindObject_By_FuncPtr([]() -> std::function<UINT(std::vector<CNpc>&)> { return CObjectSearcher::GetVecNpc; }(), Npc, Ptr);
}

BOOL CObjectFilter::FindMonster_By_Func(_Out_ CMonster& Monster, _In_ std::function<BOOL(CONST CMonster&)> Ptr)
{
	return FindObject_By_FuncPtr([]() -> std::function<UINT(std::vector<CMonster>&)> { return CObjectSearcher::GetVecMonster; }(), Monster, Ptr);
}

BOOL CObjectFilter::FindPlayer_By_Func(_Out_ CPlayer& Player, _In_ std::function<BOOL(CONST CPlayer&)> Ptr)
{
	return FindObject_By_FuncPtr([]() -> std::function<UINT(std::vector<CPlayer>&)> { return CObjectSearcher::GetVecPlayer; }(), Player, Ptr);
}

BOOL CObjectFilter::FindChest_By_Func(_Out_ CChest& Chest, _In_ std::function<BOOL(CONST CChest&)> Ptr)
{
	return FindObject_By_FuncPtr([]() -> std::function<UINT(std::vector<CChest>&)> { return CObjectSearcher::GetVecChest; }(), Chest, Ptr);
}

BOOL CObjectFilter::FindWorldItem_By_Func(_Out_ CWorldItem& WorldItem, _In_ std::function<BOOL(CONST CWorldItem&)> Ptr)
{
	return FindObject_By_FuncPtr([]() -> std::function<UINT(std::vector<CWorldItem>&)> { return CObjectSearcher::GetVecWorlditem; }(), WorldItem, Ptr);
}

BOOL CObjectFilter::FindItem_By_Func(_Out_ CItem& Item, _In_ std::function<BOOL(CONST CItem&)> Ptr)
{
	return FindObject_By_FuncPtr([]() -> std::function<UINT(std::vector<CItem>&)> { return CBagAttribute::GetVecBagItem; }(), Item, Ptr);
}
