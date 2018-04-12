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
	CAttributeObject::FillObjectAttribute_ResName(this);
	CAttributeObject::FillObjectAttribute_Positioned(this);
	
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

			// 用ResName来判断 是否装备?  强行设置ModsIndex = 2?
			CAttributeObject::FillAttributeTable(dwWorldItemObjectPtr, "Mods", [&](DWORD dwModsIndex) 
			{
				this->_IsEqui = TRUE;
				DWORD dwModsObject = ReadDWORD(ReadDWORD(dwWorldItemObjectPtr + 0x4) + dwModsIndex * 4);
				CAttributeObject::FillObjectAttribute_Color(this, dwModsObject);
				CAttributeObject::FillEquiObjectAttribute_Level(this, dwModsObject);
			});
		}
	});
}

em_Equi_Color CWorldItem::GetEquiColor() CONST
{
	return _emEquiColor;
}

DWORD CWorldItem::GetEquiLevel() CONST
{
	return _dwEquiLevel;
}

VOID CWorldItem::SetEquiLevel(_In_ DWORD dwLevel)
{
	_dwEquiLevel = dwLevel;
}

BOOL CWorldItem::IsEqui() CONST
{
	return _IsEqui;
}
