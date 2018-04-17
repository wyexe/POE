#include "CmdExpr.h"
#include <LogLib\Log.h>
#include <CharacterLib\Character.h>
#include <Core\Feature\GameMemory\GameMemory.h>
#include <Core\Feature\Searcher\ObjectSearcher.h>
#include <Core\Feature\Attribute\Bag\BagAttribute.h>
#include <Core\Feature\Attribute\Warehouse\WarehouseAttribute.h>
#include <Core\Object\AttributeObject.h>
#include <Core\Feature\EchoAction\GameMouse.h>

#define _SELF L"CmdExpr.cpp"
CCmdExpr::CCmdExpr()
{
}

CCmdExpr::~CCmdExpr()
{

}

CCmdExpr& CCmdExpr::GetInstance()
{
	static CCmdExpr Instance;
	return Instance;
}

std::vector<libTools::ExpressionFunPtr>& CCmdExpr::GetVec()
{
	static std::vector<libTools::ExpressionFunPtr> Vec = 
	{
		{ std::bind(&CCmdExpr::Help, this, std::placeholders::_1), L"Help" },
		{ std::bind(&CCmdExpr::PrintBag, this, std::placeholders::_1), L"PrintBag" },
		{ std::bind(&CCmdExpr::PrintWarehouse, this, std::placeholders::_1), L"PrintWarehouse" },
		{ std::bind(&CCmdExpr::PrintChest, this, std::placeholders::_1), L"PrintChest" },
		{ std::bind(&CCmdExpr::PrintNpc, this, std::placeholders::_1), L"PrintNpc" },
		{ std::bind(&CCmdExpr::PrintMonster, this, std::placeholders::_1), L"PrintMonster" },
		{ std::bind(&CCmdExpr::PrintPlayer, this, std::placeholders::_1), L"PrintPlayer" },
		{ std::bind(&CCmdExpr::PrintWorldItem, this, std::placeholders::_1), L"PrintWorldItem" },
		{ std::bind(&CCmdExpr::MouseMove, this, std::placeholders::_1), L"MouseMove" },
	};

	return Vec;
}

VOID CCmdExpr::Release()
{

}

VOID CCmdExpr::Help(CONST std::vector<std::wstring>&)
{
	auto& Vec = GetVec();
	for (CONST auto& itm : Vec)
	{
		//MessageBoxW(NULL, itm.wsFunName.c_str(), L"", NULL);
		LOG_C_D(L"[%s]", itm.wsFunName.c_str());
	}
}

VOID CCmdExpr::PrintBag(CONST std::vector<std::wstring>&)
{
	libTools::CException::InvokeAction(__FUNCTIONW__, [] 
	{
		std::vector<CItem> VecBagItem;
		CBagAttribute::GetVecBagItem(VecBagItem);
		LOG_C_D(L"VecBagItem.size=%d", VecBagItem.size());
		for (auto& itm : VecBagItem)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Item.Name=[%s], Type=[%s]", itm.GetName().c_str(), CAttributeObject::GetObjectTypeText(itm.GetType()).c_str());

			auto Loc = itm.GetItemLocation();
			LOG_C_D(L"Location=[%d,%d,%d,%d]", Loc.dwLeftTopIndex, Loc.dwRightTopIndex, Loc.dwLeftBottomIndex, Loc.dwRightBottomIndex);
			if (itm.GetQuality() != 0)
			{
				LOG_C_D(L"Quality=[%d]", itm.GetQuality());
			}
			if (itm.IsBindAccount())
			{
				LOG_C_D(L"物品是绑定的");
			}
			if (itm.IsEqui())
			{
				if (itm.IsNotAppraisal())
				{
					LOG_C_D(L"物品是未鉴定的");
				}
				LOG_C_D(L"Color=[%s]", itm.GetEquiColorText().c_str());
				LOG_C_D(L"EquiLevel=[%d]", itm.GetEquiLevel());
			}
			else if (itm.GetType() == em_Object_Type::Flasks)
			{
				LOG_C_D(L"PercentCharges=[%d]", itm.GetPercentCharges());
			}
			if (itm.GetCount() != 0)
			{
				LOG_C_D(L"Count=[%d]/[%d]", itm.GetCount(), itm.GetMaxCount());
			}
		}
	});
}

VOID CCmdExpr::PrintWarehouse(CONST std::vector<std::wstring>&)
{
	if (!CWarehouseAttribute::IsOpenedWarehouse())
	{
		LOG_C_D(L"UnOpened Warehouse!");
		return;
	}


	LOG_C_D(L"PageIndex=[%d], PageCount=[%d]", CWarehouseAttribute::GetCurrentPageIndex(), CWarehouseAttribute::GetWarehousePageCount());

	std::vector<CItem> VecWarehouseItem;
	CWarehouseAttribute::GetCurrentPageItem(VecWarehouseItem);
	for (auto& itm : VecWarehouseItem)
	{
		itm.RefreshObjectAttribute();
		LOG_C_D(L"Item.Name=[%s], Type=[%s]", itm.GetName().c_str(), CAttributeObject::GetObjectTypeText(itm.GetType()).c_str());
		if (itm.GetType() == em_Object_Type::Other)
		{

		}

		auto Loc = itm.GetItemLocation();
		LOG_C_D(L"Location=[%d,%d,%d,%d]", Loc.dwLeftTopIndex, Loc.dwRightTopIndex, Loc.dwLeftBottomIndex, Loc.dwRightBottomIndex);
		if (itm.GetQuality() != 0)
		{
			LOG_C_D(L"Quality=[%d]", itm.GetQuality());
		}
		if (itm.IsBindAccount())
		{
			LOG_C_D(L"物品是绑定的");
		}
		if (itm.IsEqui())
		{
			if (itm.IsNotAppraisal())
			{
				LOG_C_D(L"物品是未鉴定的");
			}
			LOG_C_D(L"Color=[%s]", itm.GetEquiColorText().c_str());
			LOG_C_D(L"EquiLevel=[%d]", itm.GetEquiLevel());
		}
		else if (itm.GetType() == em_Object_Type::Flasks)
		{
			LOG_C_D(L"PercentCharges=[%d]", itm.GetPercentCharges());
		}
		if (itm.GetCount() != 0)
		{
			LOG_C_D(L"Count=[%d]/[%d]", itm.GetCount(), itm.GetMaxCount());
		}
	}
}

VOID CCmdExpr::PrintChest(CONST std::vector<std::wstring>&)
{
	std::vector<CChest> VecChest;
	CObjectSearcher::GetVecChest(VecChest);
	for (auto& itm : VecChest)
	{
		itm.RefreshObjectAttribute();
		LOG_C_D(L"Chest.Name=[%s]", itm.GetName().c_str());
		LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
		LOG_C_D(L"IsOpened=%d", itm.IsOpened());
	}
}

VOID CCmdExpr::PrintNpc(CONST std::vector<std::wstring>&)
{
	std::vector<CNpc> VecNpc;
	CObjectSearcher::GetVecNpc(VecNpc);
	for (auto& itm : VecNpc)
	{
		itm.RefreshObjectAttribute();
		LOG_C_D(L"Npc.Name=[%s]", itm.GetName().c_str());
		LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
	}
}

VOID CCmdExpr::PrintMonster(CONST std::vector<std::wstring>&)
{
	std::vector<CMonster> VecMonster;
	CObjectSearcher::GetVecMonster(VecMonster);
	for (auto& itm : VecMonster)
	{
		itm.RefreshObjectAttribute();
		LOG_C_D(L"Monster.Name=[%s]", itm.GetName().c_str());
		LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
		LOG_C_D(L"IsDead=[%d]", itm.IsDead());
		LOG_C_D(L"IsAllowAttack=[%d]", itm.IsAllowAttack());
		LOG_C_D(L"HP=[%d]", itm.GetPercentHp());
	}
}

VOID CCmdExpr::PrintPlayer(CONST std::vector<std::wstring>&)
{
	std::vector<CPlayer> VecPlayer;
	CObjectSearcher::GetVecPlayer(VecPlayer);
	for (auto& itm : VecPlayer)
	{
		itm.RefreshObjectAttribute();
		LOG_C_D(L"Player.Name=[%s]", itm.GetName().c_str());
		LOG_C_D(L"Pos=[%d,%d]", itm.GetPoint().X, itm.GetPoint().Y);
	}
}

VOID CCmdExpr::PrintWorldItem(CONST std::vector<std::wstring>&)
{
	std::vector<CWorldItem> VecWorldItem;
	CObjectSearcher::GetVecWorlditem(VecWorldItem);
	for (CONST auto& itm : VecWorldItem)
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
}

VOID CCmdExpr::MouseMove(CONST std::vector<std::wstring>&)
{
	CGameMouse::GetInstance().MoveTo(Point(100, 100));
}
