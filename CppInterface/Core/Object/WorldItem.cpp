#include "WorldItem.h"
#include "AttributeObject.h"
#include <LogLib/Log.h>
#include "Item.h"

#define _SELF L"WorldItem.cpp"
CWorldItem::CWorldItem()
{
	
}

CWorldItem::CWorldItem(_In_ DWORD dwNodeBase)
{
	SetNodeBase(dwNodeBase);
}

CWorldItem::~CWorldItem()
{
}

VOID CWorldItem::RefreshObjectAttribute()
{
	CAttributeObject::FillObject_By_AttributeName(this, "Positioned", _dwPositionedObject);

	CAttributeObject::FillAttributeTable(GetNodeBase(), "WorldItem", [&](DWORD dwIndex)
	{
		DWORD dwWorldItemObject = ReadDWORD(ReadDWORD(this->GetNodeBase() + 0x4) + dwIndex * 4);
		DWORD dwWorldItemObjectPtr = ReadDWORD(dwWorldItemObject + 0x14);
		if (dwWorldItemObjectPtr != 0)
		{
			if (!CAttributeObject::FillObjectAttribute_Base(this, dwWorldItemObjectPtr) && !CAttributeObject::FillObjectAttribute_Render(this, dwWorldItemObjectPtr))
			{
				LOG_C_D(L"Empty WorldItem Name!");
			}


			if (CAttributeObject::FillObject_By_AttributeName(dwWorldItemObjectPtr, "Mods", _dwModObject))
			{
				_IsEqui = TRUE;
			}
		}
	});
}


