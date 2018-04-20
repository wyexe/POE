#include "PersonAction.h"
#include "GameMouse.h"
#include <ProcessLib/KeyboardMsg/KeyboardMsg.h>
#include <TimeLib/TimeRand.h>
#include <TimeLib/TimeTick.h>
#include <LogLib/Log.h>
#include <Core/Feature/Attribute/Ui/UiAttribute.h>

#define _SELF L"PersonAction.cpp"


VOID CPersonAction::UseSkill(_In_ em_Skill_Id emSkillId)
{
	switch (emSkillId)
	{
	case CPersonAction::em_Skill_Id::Q:
		libTools::CKeyboardMsg::SendKey('Q');
		break;
	case CPersonAction::em_Skill_Id::W:
		libTools::CKeyboardMsg::SendKey('W');
		break;
	case CPersonAction::em_Skill_Id::E:
		libTools::CKeyboardMsg::SendKey('E');
		break;
	case CPersonAction::em_Skill_Id::R:
		libTools::CKeyboardMsg::SendKey('R');
		break;
	case CPersonAction::em_Skill_Id::T:
		libTools::CKeyboardMsg::SendKey('T');
		break;
	default:
		LOG_MSG_CF(L"无效的emSkillId in CPersonAction::UseSkill");
		break;
	}
}

VOID CPersonAction::UseMouseSkill(_In_ em_Skill_Id emSkillId)
{
	switch (emSkillId)
	{
	case CPersonAction::em_Skill_Id::LeftClick:
		MouseClick();
		break;
	case CPersonAction::em_Skill_Id::RightClick:
		MouseRightClick();
		break;
	case CPersonAction::em_Skill_Id::MiddleClick:
		mouse_event(MOUSEEVENTF_MIDDLEDOWN, NULL, NULL, NULL, NULL);
		::Sleep(libTools::CTimeRand::GetRand(100, 300));
		mouse_event(MOUSEEVENTF_MIDDLEUP, NULL, NULL, NULL, NULL);
		break;
	default:
		LOG_MSG_CF(L"无效的emSkillId in CPersonAction::UseSkill");
		break;
	}
}

VOID CPersonAction::MouseClick()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
	::Sleep(libTools::CTimeRand::GetRand(100, 300));
	mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
}

VOID CPersonAction::MouseMove(_In_ CONST Point& Pos)
{
	CGameMouse::GetInstance().MoveTo(Pos);
}

VOID CPersonAction::MouseMoveAndClick(_In_ CONST Point& Pos)
{
	MouseMove(Pos);
	MouseClick();
}

VOID CPersonAction::MouseCtrlClick()
{
	libTools::CKeyboardMsg::SendKey(VK_CONTROL, TRUE);
	MouseClick();
	libTools::CKeyboardMsg::SendKey(VK_CONTROL, FALSE);
}

VOID CPersonAction::MouseRightClick()
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN, NULL, NULL, NULL, NULL);
	::Sleep(libTools::CTimeRand::GetRand(100, 300));
	mouse_event(MOUSEEVENTF_RIGHTUP, NULL, NULL, NULL, NULL);
}

VOID CPersonAction::OpenBag()
{
	libTools::CKeyboardMsg::SendKey('I');
}

VOID CPersonAction::CloseAllWindows()
{
	libTools::CTimeTick TimeTick;
	while (TimeTick.GetSpentTime(libTools::CTimeTick::em_TimeTick::em_TimeTick_Second) < 30)
	{
		if (CUiAttribute::IsShow(CUiAttribute::em_Ui_Type::EscapeState))
		{
			break;
		}


		libTools::CKeyboardMsg::SendKey(VK_ESCAPE);
		::Sleep(1000);
	}


	TimeTick.Reset();
	while (TimeTick.GetSpentTime(libTools::CTimeTick::em_TimeTick::em_TimeTick_Second) < 30)
	{
		if (!CUiAttribute::IsShow(CUiAttribute::em_Ui_Type::EscapeState))
		{
			break;
		}


		libTools::CKeyboardMsg::SendKey(VK_ESCAPE);
		::Sleep(1000);
	}
}
