#include "StateAttribute.h"
#include <queue>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>

DWORD CStateAttribute::FindState(_In_ em_State_Type emStateType)
{
	DWORD dwTreeHead	= ReadDWORD(ReadDWORD(CObjectSearcher::GetBaseEnv() + StateÆ«ÒÆ1) + 0x4);
	DWORD dwNode		= NULL;

	switch (emStateType)
	{
	case CStateAttribute::em_State_Type::InGameState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"InGameState");
		break;
	case CStateAttribute::em_State_Type::CreateCharacterState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"CreateCharacterState");
		break;
	case CStateAttribute::em_State_Type::PreGameState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"PreGameState");
		break;
	case CStateAttribute::em_State_Type::AreaLoadingState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"AreaLoadingState");
		break;
	case CStateAttribute::em_State_Type::DeleteCharacterState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"DeleteCharacterState");
		break;
	case CStateAttribute::em_State_Type::LoadingState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"LoadingState");
		break;
	case CStateAttribute::em_State_Type::WaitingState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"WaitingState");
		break;
	case CStateAttribute::em_State_Type::CreditsState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"CreditsState");
		break;
	case CStateAttribute::em_State_Type::EscapeState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"EscapeState");
		break;
	case CStateAttribute::em_State_Type::LoginState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"LoginState");
		break;
	case CStateAttribute::em_State_Type::SelectCharacterState:
		dwNode = FindNode_By_StateText(dwTreeHead, L"SelectCharacterState");
		break;
	default:
		break;
	}

	return dwNode == NULL ? NULL : ReadDWORD(dwNode + StateObjectÆ«ÒÆ);
}

DWORD CStateAttribute::FindNode_By_StateText(_In_ DWORD dwTreeNode, _In_ CONST std::wstring& wsStateText)
{
	std::queue<DWORD> QueTree;
	QueTree.push(dwTreeNode);


	while (!QueTree.empty())
	{
		DWORD dwNode = QueTree.front();
		QueTree.pop();

		if (ReadBYTE(dwNode + 0xD) == 0x0)
		{
			if (CGameMemory::GetInstance().ReadProcTextWithLength(dwNode + 0x10) == wsStateText)
			{
				return dwNode;
			}

			QueTree.push(ReadDWORD(dwNode + 0x0));
			QueTree.push(ReadDWORD(dwNode + 0x8));
		}
	}
	return 0;
}
