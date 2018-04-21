#ifndef __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_UI_UIATTRIBUTE_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_UI_UIATTRIBUTE_H__

#include <GameStruct.h>
#include <queue>

class CUiAttribute
{
private:
	struct GameUiNode
	{
		DWORD dwNode;
		UINT uIndex;
		struct GameUiNode* pPreviousNode;
	};

public:
	enum class em_Ui_Type
	{
		DestoryItemConfirm,
		EscapeState,
		UseMapDialog,
		NpcSellDialog,
		NpcTalkDialog,
		BagDialog,
		MouseUseItemFlag, // 使用物品
	};

	struct UiObjectAttribute
	{
		DWORD dwNode;

		BOOL IsShow() CONST;
	};
public:
	CUiAttribute() = default;
	~CUiAttribute() = default;

	static BOOL IsShow(_In_ em_Ui_Type emUiType);
private:
	static BOOL IsShow_By_Offset(_In_ DWORD dwOffset);

	// abandon
	BOOL FindUiObject(_In_ em_Ui_Type emUiType, _Out_ UiObjectAttribute& UiObject);

	GameUiNode * FindUiNode_By_Text(_In_ GameUiNode* pPreviousNode, _In_ CONST std::vector<std::wstring>& VecText);

	GameUiNode * AllocGameUiNode();
	VOID		 CleanGameUiNode();

	CONST std::vector<std::wstring>& GetVecText_By_UiType(_In_ em_Ui_Type emUiType);
private:
	std::queue<GameUiNode*> _VecGameUiNode;
};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_UI_UIATTRIBUTE_H__
