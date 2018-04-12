#include "Chest.h"
#include "AttributeObject.h"

CChest::CChest()
{
}

CChest::CChest(_In_ DWORD dwNodeBase)
{
	SetNodeBase(dwNodeBase);
}

CChest::~CChest()
{
}

VOID CChest::RefreshObjectAttribute()
{
	CAttributeObject::FillObject_By_AttributeName(this, "Positioned", _dwPositionedObject);
	CAttributeObject::FillObject_By_AttributeName(this, "Chest", _dwChestOpenedAddr);
}

BOOL CChest::IsOpened() CONST
{
	return ReadBYTE(_dwChestOpenedAddr + 0x20) != NULL;
}