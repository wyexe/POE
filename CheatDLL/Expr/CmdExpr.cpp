#include "CmdExpr.h"
#include <LogLib\Log.h>
#include <CharacterLib\Character.h>
#include <Core\Feature\GameMemory\GameMemory.h>
#include <Core\Feature\Searcher\ObjectSearcher.h>
#include <Core\Feature\Attribute\Bag\BagAttribute.h>
#include <Core\Feature\Attribute\Warehouse\WarehouseAttribute.h>
#include <Core\Object\AttributeObject.h>
#include <Core\Feature\EchoAction\GameMouse.h>
#include <stack>
#include <queue>

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
		{ std::bind(&CCmdExpr::PrintUi, this, std::placeholders::_1), L"PrintUi" },
		{ std::bind(&CCmdExpr::WatchUi, this, std::placeholders::_1), L"WatchUi" },
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
				LOG_C_D(L"ÎïÆ·ÊÇ°ó¶¨µÄ");
			}
			if (itm.IsEqui())
			{
				if (itm.IsNotAppraisal())
				{
					LOG_C_D(L"ÎïÆ·ÊÇÎ´¼ø¶¨µÄ");
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
			LOG_C_D(L"ÎïÆ·ÊÇ°ó¶¨µÄ");
		}
		if (itm.IsEqui())
		{
			if (itm.IsNotAppraisal())
			{
				LOG_C_D(L"ÎïÆ·ÊÇÎ´¼ø¶¨µÄ");
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


VOID CCmdExpr::PrintUi(CONST std::vector<std::wstring>&)
{
	DWORD dwAddr = CObjectSearcher::GetGameEnv() + UIÆ«ÒÆ1;
	LOG_C_D(L"GetUiEnv=%X", dwAddr);

	struct UiNode
	{
		DWORD dwNode;
		UINT  uIndex;
		std::wstring wsText;
	};

	dwAddr = ReadDWORD(dwAddr + UIÆ«ÒÆ2);

	std::queue<UiNode> VecUiAddr;
	auto PushPtr = [&VecUiAddr](DWORD dwArrayHeadPtr, UINT uIndex, _In_ CONST std::wstring& wsText)
	{
		DWORD dwCount = (ReadDWORD(dwArrayHeadPtr + 0x4) - ReadDWORD(dwArrayHeadPtr)) / 4;
		//LOG_C_D(L"dwCount=%d", dwCount);
		if (dwCount >= 1000)
		{
			LOG_C_E(L"Exception dwCount=%d", dwCount);
			return;
		}

		for (DWORD i = 0;i < dwCount; ++i)
		{
			VecUiAddr.push(UiNode{ ReadDWORD(ReadDWORD(dwArrayHeadPtr) + i * 4) , uIndex + 1, wsText });
		}
	};
	
	 
	PushPtr(dwAddr + UI±éÀúÆ«ÒÆ1, 0, L"root->");
	while (!VecUiAddr.empty())
	{
		auto dwNode = VecUiAddr.front();
		VecUiAddr.pop();
		
		if (ReadDWORD(dwNode.dwNode + UIÃû×ÖÆ«ÒÆ) != NULL && ReadDWORD(dwNode.dwNode + UIÃû×ÖÆ«ÒÆ + 0x10) != 0)
		{
			std::wstring wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(dwNode.dwNode + UIÃû×ÖÆ«ÒÆ);
			dwNode.wsText += wsUiFormName;
			LOG_C_D(L"Node=[%d, %X], UI=[%s] [%s]", dwNode.uIndex, dwNode.dwNode, wsUiFormName.c_str(), dwNode.wsText.c_str());
		}
		dwNode.wsText += L"->";
		//LOG_C_D(L"Node=[%d, %X], IsShow=%d", dwNode.uIndex, dwNode.dwNode, ReadBYTE(dwNode.dwNode + 0x754));
		if (dwNode.uIndex < 4 && ReadDWORD(dwNode.dwNode + UI±éÀúÆ«ÒÆ1) != NULL && ReadDWORD(dwNode.dwNode + UI±éÀúÆ«ÒÆ1) != ReadDWORD(dwNode.dwNode + UI±éÀúÆ«ÒÆ1 + 0x4))
		{
			PushPtr(dwNode.dwNode + UI±éÀúÆ«ÒÆ1, dwNode.uIndex, dwNode.wsText);
		}
	}

	LOG_C_D(L"Done!");
}



VOID CCmdExpr::WatchUi(CONST std::vector<std::wstring>& Vec)
{
	struct Node
	{
		DWORD dwNode;
		BOOL  IsShow;
		UINT  uIndex;
		std::wstring wsText;
	};
	static std::vector<Node> VecNode;


	if (Vec.size() == 0)
	{
		LOG_C_D(L"WatchUi(0[StopWatch] | 1[StartWatch])");
		return;
	}


	if (Vec.at(0) == L"0")
	{
		for (auto& itm : VecNode)
		{
			BOOL IsShow = ReadBYTE(itm.dwNode + UiÏÔÊ¾Æ«ÒÆ) != 0;
			if (itm.IsShow != IsShow)
			{
				LOG_C_D(L"Node[%X, %s]  [%d]->[%d]", itm.dwNode, itm.wsText.c_str(), itm.IsShow, ReadBYTE(itm.dwNode + UiÏÔÊ¾Æ«ÒÆ));
			}
		}
		return;
	}
	

	DWORD dwAddr = ReadDWORD(CObjectSearcher::GetGameEnv() + UIÆ«ÒÆ1 + UIÆ«ÒÆ2);
	std::queue<Node> VecUiAddr;
	auto PushPtr = [&VecUiAddr](DWORD dwArrayHeadPtr, UINT uIndex, _In_ CONST std::wstring& wsText)
	{
		DWORD dwCount = (ReadDWORD(dwArrayHeadPtr + 0x4) - ReadDWORD(dwArrayHeadPtr)) / 4;
		//LOG_C_D(L"dwCount=%d", dwCount);
		if (dwCount >= 1000)
		{
			LOG_C_E(L"Exception dwCount=%d", dwCount);
			return;
		}

		for (DWORD i = 0; i < dwCount; ++i)
		{
			Node Nd;
			Nd.dwNode = ReadDWORD(ReadDWORD(dwArrayHeadPtr) + i * 4);
			Nd.IsShow = ReadBYTE(Nd.dwNode + UiÏÔÊ¾Æ«ÒÆ);
			Nd.uIndex = uIndex + 1;
			Nd.wsText = wsText;
			VecUiAddr.push(Nd);
			VecNode.push_back(Nd);
		}
	};


	VecNode.clear();
	PushPtr(dwAddr + UI±éÀúÆ«ÒÆ1, 0, L"root->");
	while (!VecUiAddr.empty())
	{
		auto dwNode = VecUiAddr.front();
		VecUiAddr.pop();

		if (ReadDWORD(dwNode.dwNode + UIÃû×ÖÆ«ÒÆ) != NULL && ReadDWORD(dwNode.dwNode + UIÃû×ÖÆ«ÒÆ + 0x10) != 0)
		{
			std::wstring wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(dwNode.dwNode + UIÃû×ÖÆ«ÒÆ);
			dwNode.wsText += wsUiFormName;
			LOG_C_D(L"Node=[%d, %X], UI=[%s] [%s]", dwNode.uIndex, dwNode.dwNode, wsUiFormName.c_str(), dwNode.wsText.c_str());
		}
		dwNode.wsText += L"->";

		if (dwNode.uIndex < 4 && ReadDWORD(dwNode.dwNode + UI±éÀúÆ«ÒÆ1) != NULL && ReadDWORD(dwNode.dwNode + UI±éÀúÆ«ÒÆ1) != ReadDWORD(dwNode.dwNode + UI±éÀúÆ«ÒÆ1 + 0x4))
		{
			PushPtr(dwNode.dwNode + UI±éÀúÆ«ÒÆ1, dwNode.uIndex, dwNode.wsText);
		}
	}

	LOG_C_D(L"VecUiAddr.size=%d", VecUiAddr.size());
}
 