#include "Person.h"
#include "AttributeObject.h"

CPerson& CPerson::GetInstance()
{
	static CPerson Instance;
	Instance.SetNodeBase(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3) + 人物基址偏移4) + 人物基址偏移5));
	return Instance;
}

VOID CPerson::RefreshObjectAttribute()
{
	CAttributeObject::FillObject_By_AttributeName(this, "Positioned", _dwPositionedObject);
	CAttributeObject::FillObjectAttribute_Base(this);
	CAttributeObject::FillObject_By_AttributeName(this, "Life", _dwLifeAttributeAddr);
	CAttributeObject::FillObject_By_AttributeName(this, "Player", _dwPlayerAttributeAddr);
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

DWORD CPerson::GetPercentValue(_In_ DWORD dwOffset) CONST
{
	DWORD dwMaxValue = ReadDWORD(_dwLifeAttributeAddr + dwOffset + 0x4);
	if (dwMaxValue == 0)
	{
		return 0;
	}


	return ReadDWORD(_dwLifeAttributeAddr + dwOffset) * 100 / dwMaxValue;
}
