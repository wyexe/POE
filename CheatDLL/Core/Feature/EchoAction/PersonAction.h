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

	static CPersonAction& GetInstance();
public:
	VOID UseSkill(_In_ em_Skill_Id emSkillId);

	VOID UseMouseSkill(_In_ em_Skill_Id emSkillId);

	VOID MouseClick();

	VOID MouseMove(_In_ CONST Point& Pos);

	VOID MouseMoveAndClick(_In_ CONST Point& Pos);

	VOID MouseCtrlClick();

	VOID MouseRightClick();
private:

};


#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ECHOACTION_PERSONACTION_H__
