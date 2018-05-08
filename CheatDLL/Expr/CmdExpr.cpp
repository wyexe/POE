#include "CmdExpr.h"
#include <stack>
#include <queue>
#include <xmmintrin.h>
#include <LogLib\Log.h>
#include <CharacterLib\Character.h>
#include <Core\Feature\GameMemory\GameMemory.h>
#include <Core\Feature\Searcher\ObjectSearcher.h>
#include <Core\Feature\Attribute\Bag\BagAttribute.h>
#include <Core\Feature\Attribute\Warehouse\WarehouseAttribute.h>
#include <Core\Object\AttributeObject.h>
#include <Core\Feature\EchoAction\GameMouse.h>
#include <Core\Feature\Attribute\Buff\BuffAttribute.h>
#include <Core\Object\Person.h>
#include <Core\Feature\Attribute\Effect\EffectAttribute.h>
#include <Core\Feature\PointConvert\PointConverter.h>
#include <Core\Feature\EchoAction\PersonAction.h>
#include <MathLib\DistanceCalc.h>

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
		{ std::bind(&CCmdExpr::Test, this, std::placeholders::_1), L"Test" },
		{ std::bind(&CCmdExpr::PrintAroundObject, this, std::placeholders::_1), L"PrintAroundObject" },
		{ std::bind(&CCmdExpr::PrintBuff, this, std::placeholders::_1), L"PrintBuff" },
		{ std::bind(&CCmdExpr::PrintEffect, this, std::placeholders::_1), L"PrintEffect" },
		{ std::bind(&CCmdExpr::PrintPerson, this, std::placeholders::_1), L"PrintPerson" },
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

VOID CCmdExpr::PrintPerson(CONST std::vector<std::wstring>&)
{
	libTools::CException::InvokeAction(__FUNCTIONW__, []
	{
		CPerson::GetInstance().RefreshObjectAttribute();
		LOG_C_D(L"Name=[%s], Level=[%d], MapName=[%s]", CPerson::GetInstance().GetName().c_str(), CPerson::GetInstance().GetLevel(), CPerson::GetInstance().GetMapName().c_str());
		LOG_C_D(L"PercentHP=[%d], PercentMP=[%d], PercentShield=[%d]", CPerson::GetInstance().GetPercentHP(), CPerson::GetInstance().GetPercentMP(), CPerson::GetInstance().GetPercentShield());
		LOG_C_D(L"Pos=[%d,%d]", CPerson::GetInstance().GetPoint().X, CPerson::GetInstance().GetPoint().Y);
	});
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

VOID CCmdExpr::PrintAroundObject(CONST std::vector<std::wstring>&)
{
	DWORD dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(CObjectSearcher::GetGameEnv() + 物品遍历偏移1) + 周围对象遍历偏移1) + 周围对象遍历偏移2 + 周围对象遍历偏移3) + 0x4/*RootNode*/);


	std::queue<DWORD> VecStack;
	VecStack.push(dwAddr);


	while (!VecStack.empty())
	{
		DWORD dwNode = VecStack.front();
		VecStack.pop();


		if (ReadBYTE(dwNode + 0xD) != 0)
			continue;


		DWORD dwNodeBase = ReadDWORD(dwNode + 0x14);
		DWORD dwAttributeTablePtr = ReadDWORD(dwNodeBase + 0x0);
		std::wstring wsResName = CGameMemory::GetInstance().ReadProcTextWithLength(dwAttributeTablePtr + 0x10);
		LOG_C_D(L"dwNode=[%X],wsResName=[%s]", dwNodeBase, wsResName.c_str());

		CAttributeObject::FillAttributeTable(dwNodeBase, "Render", [=](DWORD Index)
		{
			DWORD dwRenderObject = ReadDWORD(ReadDWORD(dwNodeBase + 0x4) + Index * 4);
			LOG_C_D(L"Render.Name=%s", CGameMemory::GetInstance().ReadProcTextWithLength(dwRenderObject + 怪物名字偏移).c_str());
		});

		CAttributeObject::FillAttributeTable(dwNodeBase, "Base", [=](DWORD Index)
		{
			DWORD dwBaseObject = ReadDWORD(ReadDWORD(dwNodeBase + 0x4) + Index * 4);
			LOG_C_D(L"Base.Name=%s", CGameMemory::GetInstance().ReadProcTextWithLength(ReadDWORD(dwBaseObject + 0x8) + 0x10).c_str());
		});

		VecStack.push(ReadDWORD(dwNode + 0x0));
		VecStack.push(ReadDWORD(dwNode + 0x8));
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
	LOG_C_D(L"VecNpc.size=%d", VecNpc.size());
	CPerson::GetInstance().RefreshObjectAttribute();
	for (auto& itm : VecNpc)
	{
		itm.RefreshObjectAttribute();
		LOG_C_D(L"Npc.Name=[%s] NodeBase=[%X]", itm.GetName().c_str(), itm.GetNodeBase());
		LOG_C_D(L"Pos=[%d,%d], dis=[%.2f]", itm.GetPoint().X, itm.GetPoint().Y, itm.GetDis());
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
	DWORD dwAddr = CObjectSearcher::GetGameEnv() + UI偏移1;
	LOG_C_D(L"GetUiEnv=%X", dwAddr);

	struct UiNode
	{
		DWORD dwNode;
		UINT  uIndex;
		std::wstring wsText;
	};

	dwAddr = ReadDWORD(dwAddr + UI偏移2);

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
	
	 
	PushPtr(dwAddr + UI遍历偏移1, 0, L"root->");
	while (!VecUiAddr.empty())
	{
		auto dwNode = VecUiAddr.front();
		VecUiAddr.pop();
		
		if (ReadDWORD(dwNode.dwNode + UI名字偏移) != NULL && ReadDWORD(dwNode.dwNode + UI名字偏移 + 0x10) != 0)
		{
			std::wstring wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(dwNode.dwNode + UI名字偏移);
			dwNode.wsText += wsUiFormName;
			LOG_C_D(L"Node=[%d, %X], UI=[%s] [%s]", dwNode.uIndex, dwNode.dwNode, wsUiFormName.c_str(), dwNode.wsText.c_str());
		}
		dwNode.wsText += L"->";
		//LOG_C_D(L"Node=[%d, %X], IsShow=%d", dwNode.uIndex, dwNode.dwNode, ReadBYTE(dwNode.dwNode + 0x754));
		if (dwNode.uIndex < 4 && ReadDWORD(dwNode.dwNode + UI遍历偏移1) != NULL && ReadDWORD(dwNode.dwNode + UI遍历偏移1) != ReadDWORD(dwNode.dwNode + UI遍历偏移1 + 0x4))
		{
			PushPtr(dwNode.dwNode + UI遍历偏移1, dwNode.uIndex, dwNode.wsText);
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
			BOOL IsShow = ReadBYTE(itm.dwNode + Ui显示偏移) != 0;
			if (itm.IsShow != IsShow)
			{
				LOG_C_D(L"Node[%X, %s]  [%d]->[%d]", itm.dwNode, itm.wsText.c_str(), itm.IsShow, ReadBYTE(itm.dwNode + Ui显示偏移));
			}
		}
		return;
	}
	

	DWORD dwAddr = ReadDWORD(CObjectSearcher::GetGameEnv() + UI偏移1 + UI偏移2);
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
			Nd.IsShow = ReadBYTE(Nd.dwNode + Ui显示偏移);
			Nd.uIndex = uIndex + 1;
			Nd.wsText = wsText;
			VecUiAddr.push(Nd);
			VecNode.push_back(Nd);
		}
	};


	VecNode.clear();
	PushPtr(dwAddr + UI遍历偏移1, 0, L"root->");
	while (!VecUiAddr.empty())
	{
		auto dwNode = VecUiAddr.front();
		VecUiAddr.pop();

		if (ReadDWORD(dwNode.dwNode + UI名字偏移) != NULL && ReadDWORD(dwNode.dwNode + UI名字偏移 + 0x10) != 0)
		{
			std::wstring wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(dwNode.dwNode + UI名字偏移);
			dwNode.wsText += wsUiFormName;
			LOG_C_D(L"Node=[%d, %X], UI=[%s] [%s]", dwNode.uIndex, dwNode.dwNode, wsUiFormName.c_str(), dwNode.wsText.c_str());
		}
		dwNode.wsText += L"->";

		if (dwNode.uIndex < 4 && ReadDWORD(dwNode.dwNode + UI遍历偏移1) != NULL && ReadDWORD(dwNode.dwNode + UI遍历偏移1) != ReadDWORD(dwNode.dwNode + UI遍历偏移1 + 0x4))
		{
			PushPtr(dwNode.dwNode + UI遍历偏移1, dwNode.uIndex, dwNode.wsText);
		}
	}

	LOG_C_D(L"VecUiAddr.size=%d", VecUiAddr.size());
}


VOID CCmdExpr::PrintItem(CONST std::vector<std::wstring>&)
{
	DWORD dwAddr = CObjectSearcher::GetGameEnv();
	dwAddr = ReadDWORD(dwAddr + 物品遍历偏移1) + 物品遍历偏移2 + 物品遍历偏移3;
	DWORD dwCount = (ReadDWORD(dwAddr + 4) - ReadDWORD(dwAddr)) / 0x10;
	LOG_C_D(L"dwCount=%X,%d", dwCount, dwCount);
	for (DWORD i = 0; i < dwCount; ++i)
	{
		LOG_C_D(L"------------------------------------------------------------");
		LOG_C_D(L"Index=%d", i);
		DWORD dwItemAddr = ReadDWORD(ReadDWORD(dwAddr) + i * 0x10 + 0x4) + 物品遍历偏移4;

		std::vector<CItem> VecBagItem;
		CObjectSearcher::GetVecItem(dwItemAddr, VecBagItem);
		LOG_C_D(L"VecBagItem.size=%d", VecBagItem.size());
		for (auto& itm : VecBagItem)
		{
			itm.RefreshObjectAttribute();
			LOG_C_D(L"Item.Name=[%s], Type=[%s] Node=[%X]", itm.GetName().c_str(), CAttributeObject::GetObjectTypeText(itm.GetType()).c_str(), itm.GetNodeBase());

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
}

VOID CCmdExpr::PrintBuff(CONST std::vector<std::wstring>&)
{
	CPerson::GetInstance().RefreshObjectAttribute();
	std::vector<CBuffAttribute::BuffObject> Vec;
	CBuffAttribute::GetVecBuff(Vec);
	LOG_C_D(L"vec.size=%d", Vec.size()); 

	for (CONST auto& itm : Vec)
	{
		LOG_C_D(L"Buff.Name=[%s], Text=[%s]", itm.wsBuffName.c_str(), itm.wsBuffText.c_str());
	}
}

VOID CCmdExpr::PrintEffect(CONST std::vector<std::wstring>&)
{
	std::vector<CEffectAttribute::EffectIconObject> Vec;
	CEffectAttribute::GetVecEffect(Vec);
	LOG_C_D(L"vec.size=%d", Vec.size());

	for (auto& itm : Vec)
	{
		LOG_C_D(L"Effect.Index=[%d], Object=[%X], ID=[%X], Count=%d", itm.Index, itm.dwObject, itm.dwId, itm.GetCount());
	}
}

VOID CCmdExpr::Test(CONST std::vector<std::wstring>&)
{
	/*libTools::CException::InvokeAction(__FUNCTIONW__, [] 
	{
		Point Pos;

		Pos = CPointConverter::GetCursorClientPos();
		LOG_C_D(L"当前鼠标的屏幕坐标=[%d,%d]", Pos.X, Pos.Y);

		Pos = CPointConverter::GetCursorGamePos();
		LOG_C_D(L"当前鼠标的游戏坐标=[%d,%d]", Pos.X, Pos.Y);

		Pos = CPointConverter::ConvertClientPosToGamePos(CPointConverter::GetCursorClientPos());
		LOG_C_D(L"将当前鼠标的屏幕坐标转换成游戏坐标=[%d,%d]", Pos.X, Pos.Y);

		if (!CPointConverter::ConvertGamePosToClientPos(CPointConverter::GetCursorGamePos(), Pos))
		{
			LOG_C_D(L"鼠标超出屏幕范围!");
			return;
		}

		LOG_C_D(L"将当前鼠标的游戏坐标转换成屏幕坐标=[%d,%d]", Pos.X, Pos.Y);
	});*/
	Point Pos = CPointConverter::ConvertGamePosToClientPos(Point(734, 1065));
	Pos = CPointConverter::ConvertClientPosToMousePos(Pos);
	LOG_C_D(L"Warehouse.MousePos=[%d,%d]", Pos.X, Pos.Y);

	CPerson::GetInstance().RefreshObjectAttribute();
	Point PersonPos = CPointConverter::ConvertGamePosToClientPos(CPerson::GetInstance().GetPoint());
	PersonPos = CPointConverter::ConvertClientPosToMousePos(PersonPos);
	LOG_C_D(L"dis=%.2f,PersonPos=[%d,%d]",libTools::CDistanceCalc::GetDisBy2D(PersonPos, Pos), PersonPos.X, PersonPos.Y);
	if (libTools::CDistanceCalc::GetDisBy2D(PersonPos, Pos) < MAX_OBJECT_MOUSE_DIS)
	{
		LOG_C_D(L"In Client Warehouse.MousePos=[%d,%d]", Pos.X, Pos.Y);
		::Sleep(2 * 1000);
		CPersonAction::MouseMoveAndClick(Pos);
	}
	else
	{
		// 相似三角形
		Point C = PersonPos;
		float K = static_cast<float>(MAX_OBJECT_MOUSE_DIS) / libTools::CDistanceCalc::GetDisBy2D(PersonPos, Pos);
		C.X += static_cast<DWORD>(K * (Pos.GetFloatX() - PersonPos.GetFloatX()));
		C.Y += static_cast<DWORD>(K * (Pos.GetFloatY() - PersonPos.GetFloatY()));

		LOG_C_D(L"Out Client Next.MousePos=[%d,%d]", C.X, C.Y);
		::Sleep(2 * 1000);
		CPersonAction::MouseMoveAndClick(C);
	}
}