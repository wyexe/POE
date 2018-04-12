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
	CAttributeObject::FillObjectAttribute_ResName(this);
	CAttributeObject::FillObjectAttribute_Positioned(this);
	CAttributeObject::FillObjectAttribute_Render(this);


	// Set '_dwIsDeadPtr'
	CAttributeObject::FillAttributeTable(GetNodeBase(), "Positioned", [&](DWORD dwIndex)
	{
		DWORD dwPositionedObject = ReadDWORD(ReadDWORD(this->GetNodeBase() + 0x4) + dwIndex * 4);
		_dwIsDeadPtr = dwPositionedObject + 0x18;
	});


	// Set '_dwHpPtr'
	CAttributeObject::FillAttributeTable(GetNodeBase(), "Life", [&](DWORD dwIndex)
	{
		DWORD dwLifeObject = ReadDWORD(ReadDWORD(this->GetNodeBase() + 0x4) + dwIndex * 4);
		_dwHpPtr = dwLifeObject + 0x2C;
	});


	// Set '_dwAllowAttackPtr'
	CAttributeObject::FillAttributeTable(GetNodeBase(), "Actor", [&](DWORD dwIndex)
	{
		DWORD dwActorObject = ReadDWORD(ReadDWORD(this->GetNodeBase() + 0x4) + dwIndex * 4);
		_dwAllowAttackPtr = dwActorObject + 0x80;
	});
}

BOOL CMonster::IsDead() CONST
{
	return ReadDWORD(_dwIsDeadPtr) == 0x7FFFFFFF;
}

DWORD CMonster::GetPercentHp() CONST
{
	DWORD dwMaxHp = ReadDWORD(_dwHpPtr + 0x4);
	if (dwMaxHp == NULL)
	{
		return 0;
	}


	return ReadDWORD(_dwHpPtr) * 100 / dwMaxHp;
}

BOOL CMonster::IsAllowAttack()
{
	return ReadBYTE(_dwAllowAttackPtr) != NULL;
}
