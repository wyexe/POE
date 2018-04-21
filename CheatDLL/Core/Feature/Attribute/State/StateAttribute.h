#ifndef __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_STATE_STATEATTRIBUTE_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_STATE_STATEATTRIBUTE_H__

#include <GameStruct.h>
#include <string>

class CStateAttribute
{
public:
	enum class em_State_Type
	{
		InGameState,
		CreateCharacterState,
		PreGameState,
		AreaLoadingState,
		DeleteCharacterState,
		LoadingState,
		WaitingState,
		CreditsState,
		EscapeState,
		LoginState,
		SelectCharacterState
	};
public:
	CStateAttribute() = default;
	~CStateAttribute() = default;

	static DWORD FindState(_In_ em_State_Type emStateType);
private:
	static DWORD FindNode_By_StateText(_In_ DWORD dwTreeNode, _In_ CONST std::wstring& wsStateText);
private:

};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_STATE_STATEATTRIBUTE_H__
