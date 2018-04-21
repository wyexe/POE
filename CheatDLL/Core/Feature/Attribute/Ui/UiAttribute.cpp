#include "UiAttribute.h"
#include <map>
#include <LogLib/Log.h>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>

#define _SELF L"UiAttribute.cpp"
BOOL CUiAttribute::IsShow(_In_ em_Ui_Type emUiType)
{
	switch (emUiType)
	{
	case CUiAttribute::em_Ui_Type::DestoryItemConfirm:
		return IsShow_By_Offset(丢弃物品确认窗口偏移);
	case CUiAttribute::em_Ui_Type::EscapeState:
		return CObjectSearcher::GetCurrentStateText() == L"EscapeState";
	case em_Ui_Type::UseMapDialog:
		return IsShow_By_Offset(异界地图宝鉴偏移);
	case em_Ui_Type::NpcSellDialog:
		return IsShow_By_Offset(Npc出售窗口偏移);
	case em_Ui_Type::NpcTalkDialog:
		return IsShow_By_Offset(Npc对话窗口偏移);
	case em_Ui_Type::BagDialog:
		return IsShow_By_Offset(背包UI偏移);
	case em_Ui_Type::MouseUseItemFlag:
		return ReadBYTE(ReadDWORD(ReadDWORD(CObjectSearcher::GetGameEnv() + 人物UI偏移) + 鼠标右键使用物品UI偏移) + 鼠标是否使用物品偏移) != 0;
	default:
		break;
	}

	LOG_MSG_CF(L"Invalid emUiType");
	return FALSE;
}


BOOL CUiAttribute::IsShow_By_Offset(_In_ DWORD dwOffset)
{
	return ReadBYTE(ReadDWORD(ReadDWORD(CObjectSearcher::GetGameEnv() + 人物UI偏移) + dwOffset) + Ui显示偏移) != 0;
}


BOOL CUiAttribute::FindUiObject(_In_ em_Ui_Type emUiType, _Out_ UiObjectAttribute& UiObject)
{
	CONST auto& VecText = GetVecText_By_UiType(emUiType);

	auto pRootNode = AllocGameUiNode();
	pRootNode->dwNode = ReadDWORD(CObjectSearcher::GetGameEnv() + UI偏移1 + UI偏移2);
	pRootNode->pPreviousNode = nullptr;
	pRootNode->uIndex = 0;

	// 深度优先…… 递归
	auto pResultNode = FindUiNode_By_Text(pRootNode, VecText);
	if (pRootNode != nullptr)
	{
		UiObject.dwNode = pResultNode->pPreviousNode->pPreviousNode->dwNode;
		CleanGameUiNode();
		return TRUE;
	}

	CleanGameUiNode();
	LOG_C_E(L"UnExisT UiText[%s]", VecText.back().c_str());
	return FALSE;
}

CUiAttribute::GameUiNode * CUiAttribute::FindUiNode_By_Text(_In_ GameUiNode* pPreviousNode, _In_ CONST std::vector<std::wstring>& VecText)
{
	if (ReadDWORD(pPreviousNode->dwNode + UI名字偏移) != NULL && ReadDWORD(pPreviousNode->dwNode + UI名字偏移 + 0x10) != 0)
	{
		std::wstring wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(pPreviousNode->dwNode + UI名字偏移);
		if (wsUiFormName != VecText.at(pPreviousNode->uIndex))
		{
			return nullptr;
		}
	}
	if (pPreviousNode->uIndex + 1 >= VecText.size())
	{
		return nullptr;
	}


	DWORD dwArrayHeadPtr = pPreviousNode->dwNode + UI遍历偏移1;
	DWORD dwCount = (ReadDWORD(dwArrayHeadPtr + 0x4) - ReadDWORD(dwArrayHeadPtr)) / 4;
	for (DWORD i = 0; i < dwCount; ++i)
	{
		DWORD dwNode = ReadDWORD(ReadDWORD(dwArrayHeadPtr) + i * 4);

		auto pNode = AllocGameUiNode();
		pNode->dwNode = dwNode;
		pNode->pPreviousNode = pPreviousNode;
		pNode->uIndex = pPreviousNode->uIndex + 1;

		std::wstring wsUiFormName;
		if (ReadDWORD(dwNode + UI名字偏移) != NULL && ReadDWORD(dwNode + UI名字偏移 + 0x10) != 0)
		{
			wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(dwNode + UI名字偏移);
		}

		if (VecText.at(pNode->uIndex) != wsUiFormName)
		{
			continue;
		}


		if (pNode->uIndex + 1 == VecText.size())
		{
			return pNode;
		}

		// 递归搜索...
		auto pNextNode = FindUiNode_By_Text(pNode, VecText);
		if (pNextNode != nullptr)
		{
			return pNextNode;
		}
	}

	return nullptr;
}

CUiAttribute::GameUiNode * CUiAttribute::AllocGameUiNode()
{
	auto p = new GameUiNode;
	_VecGameUiNode.push(p);
	return p;
}

VOID CUiAttribute::CleanGameUiNode()
{
	while (!_VecGameUiNode.empty())
	{
		delete _VecGameUiNode.front();
		_VecGameUiNode.pop();
	}
}

CONST std::vector<std::wstring>& CUiAttribute::GetVecText_By_UiType(_In_ em_Ui_Type emUiType)
{
	CONST static std::map<em_Ui_Type, std::vector<std::wstring>> Vec = 
	{
		{ em_Ui_Type::DestoryItemConfirm, { L"root",L"",L"",L"confirmation_window",L"action_two_button" } }
	};

	auto itr = Vec.find(emUiType);
	if (itr != Vec.end())
	{
		return itr->second;
	}

	CONST static std::vector<std::wstring> VecEmpty;
	LOG_MSG_CF(L"Invalid emUiType!!!");
	return VecEmpty;
}

BOOL CUiAttribute::UiObjectAttribute::IsShow() CONST
{
	return ReadBYTE(this->dwNode + Ui显示偏移) != 0 ? TRUE : FALSE;
}
