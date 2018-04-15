#include <Windows.h>
#include <ProcessLib\Process\Process.h>
#include <ProcessLib\KeyboardMsg\KeyboardMsg.h>
#include <CharacterLib\Character.h>


#include <Core\Feature\GameMemory\GameMemory.h>
#include <Core\Feature\Searcher\ObjectSearcher.h>
#include <Core\Feature\Attribute\Bag\BagAttribute.h>
#include <Core\Feature\Attribute\Warehouse\WarehouseAttribute.h>

#include <LogLib\Log.h>

#pragma comment(lib,"ProcessLib.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"CharacterLib.lib")
#pragma comment(lib,"LogLib.lib")

#define _SELF L"dllmain.cpp"
BOOL WINAPI DllMain(_In_ HINSTANCE, _In_ DWORD dwReason, _In_ LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Set Capacity = 100
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

	}
	return TRUE;
}

enum em_VecObject_Type
{
	em_VecObject_Type_Bag_Item,
	em_VecObject_Type_Warehouse_Item,
	em_VecObject_Type_Chest,
	em_VecObject_Type_Npc,
	em_VecObject_Type_Monster,
	em_VecObject_Type_Player,
	em_VecObject_Type_WorldItem
};


// ±³°üÎïÆ·
extern "C" __declspec(dllexport) int WINAPIV GetVecObject(_In_ int nType)
{
	static std::vector<CItem>		gs_VecBagItem;
	static std::vector<CItem>		gs_VecWarehouseItem;
	static std::vector<CChest>		gs_VecChest;
	static std::vector<CNpc>		gs_VecNpc;
	static std::vector<CMonster>	gs_VecMonster;
	static std::vector<CPlayer>		gs_VecPlayer;
	static std::vector<CWorldItem>	gs_VecWorldItem;

	switch (static_cast<em_VecObject_Type>(nType))
	{
	case em_VecObject_Type_Bag_Item:
		gs_VecBagItem.clear();
		CBagAttribute::GetVecBagItem(gs_VecBagItem);
		for (auto& itm : gs_VecBagItem)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Item.Name=[%s]", itm.GetName().c_str());

			auto Loc = itm.GetItemLocation();
			LOG_C_D(L"Location=[%d,%d,%d,%d]", Loc.dwLeftTopIndex, Loc.dwRightTopIndex, Loc.dwLeftBottomIndex, Loc.dwRightBottomIndex);
			if (itm.IsEqui())
			{
				LOG_C_D(L"Quality=[%d]", itm.GetQuality());
				LOG_C_D(L"IsBind=[%d]", itm.IsBindAccount());
				LOG_C_D(L"IsNotAppraisal=[%d]", itm.IsNotAppraisal());
				LOG_C_D(L"Color=[%s]", itm.GetEquiColorText().c_str());
				LOG_C_D(L"EquiLevel=[%d]", itm.GetEquiLevel());
			}
			else if (itm.GetType() == em_Object_Type::Flasks)
			{
				LOG_C_D(L"PercentCharges=[%d]", itm.GetPercentCharges());
			}

			LOG_C_D(L"Count=[%d]-[%d]", itm.GetCount(), itm.GetPercentCount());
		}
		return static_cast<int>(gs_VecBagItem.size());
	case em_VecObject_Type_Warehouse_Item:
		gs_VecWarehouseItem.clear();
		CWarehouseAttribute::GetCurrentPageItem(gs_VecWarehouseItem);
		for (auto& itm : gs_VecBagItem)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Item.Name=[%s]", itm.GetName().c_str());

			auto Loc = itm.GetItemLocation();
			LOG_C_D(L"Location=[%d,%d,%d,%d]", Loc.dwLeftTopIndex, Loc.dwRightTopIndex, Loc.dwLeftBottomIndex, Loc.dwRightBottomIndex);
			if (itm.IsEqui())
			{
				LOG_C_D(L"Quality=[%d]", itm.GetQuality());
				LOG_C_D(L"IsBind=[%d]", itm.IsBindAccount());
				LOG_C_D(L"IsNotAppraisal=[%d]", itm.IsNotAppraisal());
				LOG_C_D(L"Color=[%s]", itm.GetEquiColorText().c_str());
				LOG_C_D(L"EquiLevel=[%d]", itm.GetEquiLevel());
			}
			else if (itm.GetType() == em_Object_Type::Flasks)
			{
				LOG_C_D(L"PercentCharges=[%d]", itm.GetPercentCharges());
			}
			else
			{
				LOG_C_D(L"Count=[%d]-[%d]", itm.GetCount(), itm.GetPercentCount());
			}
		}
		return static_cast<int>(gs_VecWarehouseItem.size());
	case em_VecObject_Type_Chest:
		gs_VecChest.clear();
		CObjectSearcher::GetVecChest(gs_VecChest);
		for (auto& itm : gs_VecChest)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Chest.Name=[%s]", itm.GetName().c_str());
			LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
			LOG_C_D(L"IsOpened=%d", itm.IsOpened());
		}
		return static_cast<int>(gs_VecChest.size());
	case em_VecObject_Type_Npc:
		gs_VecNpc.clear();
		CObjectSearcher::GetVecNpc(gs_VecNpc);
		for (auto& itm : gs_VecNpc)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Npc.Name=[%s]", itm.GetName().c_str());
			LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
		}
		return static_cast<int>(gs_VecNpc.size());
	case em_VecObject_Type_Monster:
		gs_VecMonster.clear();
		CObjectSearcher::GetVecMonster(gs_VecMonster);
		for (auto& itm : gs_VecMonster)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Monster.Name=[%s]", itm.GetName().c_str());
			LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
			LOG_C_D(L"IsDead=[%d]", itm.IsDead());
			LOG_C_D(L"IsAllowAttack=[%d]", itm.IsAllowAttack());
			LOG_C_D(L"HP=[%d]", itm.GetPercentHp());
		}
		return static_cast<int>(gs_VecMonster.size());
	case em_VecObject_Type_Player:
		gs_VecPlayer.clear();
		CObjectSearcher::GetVecPlayer(gs_VecPlayer);
		for (auto& itm : gs_VecPlayer)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Player.Name=[%s]", itm.GetName().c_str());
			LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
		}
		return static_cast<int>(gs_VecPlayer.size());
	case em_VecObject_Type_WorldItem:
		gs_VecWorldItem.clear();
		CObjectSearcher::GetVecWorlditem(gs_VecWorldItem);
		for (CONST auto& itm : gs_VecWorldItem)
		{
			LOG_C_D(L"WorldItem.Name=[%s]", itm.GetName().c_str());
			LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
			if (itm.IsEqui())
			{
				LOG_C_D(L"Quality=[%d]", itm.GetQuality());
				LOG_C_D(L"IsBind=[%d]", itm.IsBindAccount());
				LOG_C_D(L"IsNotAppraisal=[%d]", itm.IsNotAppraisal());
				LOG_C_D(L"Color=[%s]", itm.GetEquiColorText().c_str());
				LOG_C_D(L"EquiLevel=[%d]", itm.GetEquiLevel());
			}
			else
			{
				LOG_C_D(L"Count=[%d]-[%d]", itm.GetCount(), itm.GetPercentCount());
			}
		}
		return static_cast<int>(gs_VecWorldItem.size());
	default:
		::MessageBoxW(NULL, libTools::CCharacter::MakeFormatText(L"Invalid GetVecObject.nType=%d", nType).c_str(), L"", NULL);
		break;
	}

	return 0;
}