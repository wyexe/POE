#include "Person.h"
#include "AttributeObject.h"
#include <Core/Feature/Attribute/State/StateAttribute.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>
#include <LogLib/Log.h>

#define _SELF L"Person.cpp"

CPerson::CPerson(_In_ DWORD dwNodeBase)
{
	SetNodeBase(dwNodeBase);
}

CPerson& CPerson::GetInstance()
{
	static CPerson Instance;
	return Instance;
}

VOID CPerson::RefreshObjectAttribute()
{
	SetNodeBase(ReadDWORD(CObjectSearcher::GetGameEnv() + 人物基址偏移4) + 人物基址偏移5);

	// [[GetNodeBase()]+2C]+1c,20 = Current Point
	CAttributeObject::FillObject_By_AttributeName(this, "Positioned", _dwPositionedObject);
	CAttributeObject::FillObject_By_AttributeName(this, "Life", _dwLifeAttributeAddr);
	CAttributeObject::FillObject_By_AttributeName(this, "Player", _dwPlayerAttributeAddr);
	CAttributeObject::FillObject_By_AttributeName(this, "Pathfinding", _dwPathfindingAddr);
	CAttributeObject::FillObjectAttribute_Player(this);
	_dwAreaLoadingStateAddr = CStateAttribute::FindState(CStateAttribute::em_State_Type::AreaLoadingState);
	if (_dwAreaLoadingStateAddr == NULL)
	{
		LOG_MSG_CF(L"FindState AreaLoadingState = NULL!");
	}
}

DWORD CPerson::GetPercentHP() CONST
{
	return GetPercentValue(人物HP偏移);
}

DWORD CPerson::GetPercentMP() CONST
{
	return GetPercentValue(人物MP偏移);
}

DWORD CPerson::GetPercentShield() CONST
{
	return GetPercentValue(人物护盾偏移);
}

DWORD CPerson::GetLevel() CONST
{
	return ReadBYTE(_dwPlayerAttributeAddr + 人物等级偏移);
}

std::wstring CPerson::GetMapName()
{
	return CGameMemory::GetInstance().ReadProcTextWithLength(_dwAreaLoadingStateAddr + 当前地图偏移);
}

DWORD CPerson::GetLifeAttributeAddr() CONST
{
	return _dwLifeAttributeAddr;
}


BOOL CPerson::IsMoving() CONST
{
	return ReadBYTE(_dwPathfindingAddr + 是否走路中偏移) == 1 ? TRUE : FALSE;
}

DWORD CPerson::GetPercentValue(_In_ DWORD dwOffset) CONST
{
	DWORD dwMaxValue = ReadDWORD(_dwLifeAttributeAddr + dwOffset + 0x4);
	if (dwMaxValue == 0)
	{
		return 0;
	}


	return ReadDWORD(_dwLifeAttributeAddr + dwOffset) * 100 / dwMaxValue;
}
