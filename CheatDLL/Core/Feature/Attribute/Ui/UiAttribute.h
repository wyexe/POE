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
	};
public:
	CUiAttribute() = default;
	~CUiAttribute() = default;

	BOOL IsShow(_In_ em_Ui_Type emUiType);
private:
	GameUiNode * FindUiNode_By_Text(_In_ GameUiNode* pPreviousNode, _In_ CONST std::vector<std::wstring>& VecText);

	GameUiNode * AllocGameUiNode();
	VOID		 CleanGameUiNode();

	CONST std::vector<std::wstring>& GetVecText_By_UiType(_In_ em_Ui_Type emUiType);
private:
	std::queue<GameUiNode*> _VecGameUiNode;
};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_UI_UIATTRIBUTE_H__
