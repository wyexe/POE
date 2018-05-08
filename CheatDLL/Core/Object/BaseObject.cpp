#include "BaseObject.h"
#include "AttributeObject.h"
#include <vector>
#include <algorithm>
#include <MathLib/DistanceCalc.h>
#include <LogLib/Log.h>
#include <Core/Feature/PointConvert/PointConverter.h>
#include <Core/Feature/EchoAction/PersonAction.h>
#include "Person.h"

#define _SELF L"BaseObject.cpp"
DWORD CBaseObject::GetNodeBase() CONST
{
	return _dwNodeBase;
}

VOID CBaseObject::SetNodeBase(_In_ DWORD dwNodeBase)
{
	_dwNodeBase = dwNodeBase;
}

CONST std::wstring& CBaseObject::GetName() CONST
{
	return _wsName;
}

VOID CBaseObject::SetName(_In_ CONST std::wstring& wsName)
{
	_wsName = wsName;
}

CONST std::wstring& CBaseObject::GetResName() CONST
{
	return _wsResName;
}

VOID CBaseObject::SetResName(_In_ CONST std::wstring& wsResName)
{
	_wsResName = wsResName;
}

Point CBaseObject::GetPoint() CONST
{
	return Point(ReadDWORD(_dwPositionedObject + 0x10), ReadDWORD(_dwPositionedObject + 0x14));
}

DWORD CBaseObject::GetAttributeTablePtr() CONST
{
	return ReadDWORD(GetNodeBase() + 0x0);
}

BOOL CBaseObject::MoveToPos(_In_ float fDis)
{
	while (GameRun && GetDis() > fDis)
	{
		if (CPerson::GetInstance().IsMoving())
		{
			::Sleep(1000);
			continue;
		}

		// outside the client
		if (GetDis() > MAX_OBJECT_CLIENT_DIS)
		{
			Point TarPos = CPointConverter::ConvertClientPosToMousePos(CPointConverter::ConvertGamePosToClientPos(GetPoint()));
			Point CurPos = CPointConverter::ConvertClientPosToMousePos(CPointConverter::ConvertGamePosToClientPos(CPerson::GetInstance().GetPoint()));
			Point NextPos = CurPos;


			// Similar triangles
			float K = static_cast<float>(MAX_OBJECT_MOUSE_DIS) / libTools::CDistanceCalc::GetDisBy2D(CurPos, TarPos);
			NextPos.X += static_cast<DWORD>(K * (TarPos.GetFloatX() - CurPos.GetFloatX()));
			NextPos.Y += static_cast<DWORD>(K * (TarPos.GetFloatY() - CurPos.GetFloatY()));
			LOG_C_D(L"Move & Click Pos[%d,%d]", NextPos.X, NextPos.Y);
			CPersonAction::MouseMoveAndClick(NextPos);
			::Sleep(1000);
			continue;
		}

		// Show Npc in the Client
		Point TarPos = CPointConverter::ConvertClientPosToMousePos(CPointConverter::ConvertGamePosToClientPos(GetPoint()));
		LOG_C_D(L"Move & Click Pos[%d,%d]", TarPos.X, TarPos.Y);
		CPersonAction::MouseMoveAndClick(TarPos);
		::Sleep(1000);
	}
	return TRUE;
}

VOID CBaseObject::Click() CONST
{
	CPersonAction::MouseMoveAndClick(CPointConverter::ConvertClientPosToMousePos(CPointConverter::ConvertGamePosToClientPos(GetPoint())));
}

float CBaseObject::GetDis() CONST
{
	return libTools::CDistanceCalc::GetDisBy2D(this->GetPoint(), CPerson::GetInstance().GetPoint());
}

bool CBaseObject::operator<(CONST CBaseObject& Rparam)
{
	return GetDis() < Rparam.GetDis();
}
