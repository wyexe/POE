#include "Monster.h"
#include "AttributeObject.h"

CMonster::CMonster()
{
	
}

CMonster::CMonster(_In_ DWORD dwNodeBase)
{
	SetNodeBase(dwNodeBase);
}

CMonster::~CMonster()
{

}

VOID CMonster::RefreshObjectAttribute()
{
	CAttributeObject::FillObject_By_AttributeName(this, "Positioned", _dwPositionedObject);
	CAttributeObject::FillObjectAttribute_Render(this);


	CAttributeObject::FillObject_By_AttributeName(this, "Life", _dwLifeObject);
	CAttributeObject::FillObject_By_AttributeName(this, "Actor", _dwActorObject);
}

BOOL CMonster::IsDead() CONST
{
	return ReadDWORD(_dwPositionedObject + 0x18) == 0x7FFFFFFF;
}

DWORD CMonster::GetPercentHp() CONST
{
	DWORD dwMaxHp = ReadDWORD(_dwLifeObject + 人物HP偏移 + 0x4);
	if (dwMaxHp == NULL)
	{
		return 0;
	}


	return ReadDWORD(_dwLifeObject + 人物HP偏移) * 100 / dwMaxHp;
}

BOOL CMonster::IsAllowAttack()
{
	return ReadBYTE(_dwActorObject + 0x80) != NULL;
}
