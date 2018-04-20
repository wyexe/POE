#ifndef __LFZL_CHEATDLL_CORE_FEATURE_ECHOACTION_PERSONACTION_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_ECHOACTION_PERSONACTION_H__

#include <GameStruct.h>

class CPersonAction
{
public:
	enum class em_Skill_Id
	{
		Q,
		W,
		E,
		R,
		T,
		LeftClick,
		RightClick,
		MiddleClick
	};
public:
	CPersonAction() = default;
	~CPersonAction() = default;

	static VOID UseSkill(_In_ em_Skill_Id emSkillId);

	static VOID UseMouseSkill(_In_ em_Skill_Id emSkillId);

	static VOID MouseClick();

	static VOID MouseMove(_In_ CONST Point& Pos);

	static VOID MouseMoveAndClick(_In_ CONST Point& Pos);

	static VOID MouseCtrlClick();

	static VOID MouseRightClick();

	// 打开背包
	static VOID OpenBag();

	// 关闭所有窗口
	static VOID CloseAllWindows();
};


#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ECHOACTION_PERSONACTION_H__
