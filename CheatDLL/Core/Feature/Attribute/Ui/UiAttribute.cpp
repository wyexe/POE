#include "UiAttribute.h"
#include <map>
#include <LogLib/Log.h>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>

#define _SELF L"UiAttribute.cpp"
BOOL CUiAttribute::IsShow(_In_ em_Ui_Type emUiType)
{
	CONST auto& VecText = GetVecText_By_UiType(emUiType);

	auto pRootNode = AllocGameUiNode();
	pRootNode->dwNode = ReadDWORD(CObjectSearcher::GetGameEnv() + UIÆ«ÒÆ1 + UIÆ«ÒÆ2);
	pRootNode->pPreviousNode = nullptr;
	pRootNode->uIndex = 0;

	auto pResultNode = FindUiNode_By_Text(pRootNode, VecText);
	if (pRootNode != nullptr)
	{
		BOOL bShow = ReadBYTE(pResultNode->pPreviousNode->pPreviousNode->dwNode + UiÏÔÊ¾Æ«ÒÆ);
		CleanGameUiNode();
		return bShow;
	}

	CleanGameUiNode();
	LOG_C_E(L"UnExisT UiText[%s]", VecText.back().c_str());
	return FALSE;
}

CUiAttribute::GameUiNode * CUiAttribute::FindUiNode_By_Text(_In_ GameUiNode* pPreviousNode, _In_ CONST std::vector<std::wstring>& VecText)
{
	if (ReadDWORD(pPreviousNode->dwNode + UIÃû×ÖÆ«ÒÆ) != NULL && ReadDWORD(pPreviousNode->dwNode + UIÃû×ÖÆ«ÒÆ + 0x10) != 0)
	{
		std::wstring wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(pPreviousNode->dwNode + UIÃû×ÖÆ«ÒÆ);
		if (wsUiFormName != VecText.at(pPreviousNode->uIndex))
		{
			return nullptr;
		}
	}
	if (pPreviousNode->uIndex + 1 >= VecText.size())
	{
		return nullptr;
	}


	DWORD dwArrayHeadPtr = pPreviousNode->dwNode + UI±éÀúÆ«ÒÆ1;
	DWORD dwCount = (ReadDWORD(dwArrayHeadPtr + 0x4) - ReadDWORD(dwArrayHeadPtr)) / 4;
	for (DWORD i = 0; i < dwCount; ++i)
	{
		DWORD dwNode = ReadDWORD(ReadDWORD(dwArrayHeadPtr) + i * 4);

		auto pNode = AllocGameUiNode();
		pNode->dwNode = dwNode;
		pNode->pPreviousNode = pPreviousNode;
		pNode->uIndex = pPreviousNode->uIndex + 1;

		std::wstring wsUiFormName;
		if (ReadDWORD(dwNode + UIÃû×ÖÆ«ÒÆ) != NULL && ReadDWORD(dwNode + UIÃû×ÖÆ«ÒÆ + 0x10) != 0)
		{
			wsUiFormName = CGameMemory::GetInstance().ReadProcTextWithLength(dwNode + UIÃû×ÖÆ«ÒÆ);
		}

		if (VecText.at(pNode->uIndex) != wsUiFormName)
		{
			continue;
		}


		if (pNode->uIndex + 1 == VecText.size())
		{
			return pNode;
		}

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
