#include "Item.h"
#include "AttributeObject.h"

CItem::CItem()
{
	
}

CItem::CItem(_In_ DWORD dwNodeBase)
{
	SetNodeBase(dwNodeBase);
}

CItem::~CItem()
{

}

VOID CItem::RefreshObjectAttribute()
{
	// Name
	CAttributeObject::FillObjectAttribute_Base(this);

	// 数量
	CAttributeObject::FillObject_By_AttributeName(this, "Stack", _dwStackObject);

	
	// 药剂
	if (GetType() == em_Object_Type::Flasks)
	{
		CAttributeObject::FillObject_By_AttributeName(this, "Charges", _dwChargesObject);
	}

	// 品质
	CAttributeObject::FillObject_By_AttributeName(this, "Quality", _dwQualityObject);

	// 
	CAttributeObject::FillObject_By_AttributeName(this, "Base", _dwBaseObject);

	// 
	_IsEqui = CAttributeObject::FillObject_By_AttributeName(this, "Mods", _dwModObject);
}

CItem::ItemPoint CItem::GetItemLocation() CONST
{
	return ItemPoint{ ReadDWORD(GetNodeBase() + 物品左上角坐标),ReadDWORD(GetNodeBase() + 物品右上角坐标),ReadDWORD(GetNodeBase() + 物品左下角坐标),ReadDWORD(GetNodeBase() + 物品右下角坐标) };
}

DWORD CItem::GetPercentCharges() CONST
{
	DWORD dwMaxCharges = ReadDWORD(ReadDWORD(_dwChargesObject + 0x8) + 0xC);
	if (dwMaxCharges == NULL)
	{
		return 0;
	}


	return ReadDWORD(_dwChargesObject + 0xC) * 100 / dwMaxCharges;
}

DWORD CItem::GetCount() CONST
{
	return ReadDWORD(_dwStackObject + 0xC) & 0xFF;
}

DWORD CItem::GetPercentCount() CONST
{
	DWORD dwMaxCount = ReadDWORD(ReadDWORD(_dwStackObject + 0x8) + 0x18) & 0xFF;
	if (dwMaxCount == 0)
	{
		return 0;
	}


	return GetCount() * 100 / dwMaxCount;
}

DWORD CItem::GetQuality() CONST
{
	return ReadBYTE(_dwQualityObject + 0xC);
}

BOOL CItem::IsBindAccount() CONST
{
	return ReadBYTE(_dwBaseObject + 物品绑定偏移) != 0;
}

BOOL CItem::IsNotAppraisal() CONST
{
	return ReadBYTE(_dwModObject + 物品鉴定偏移) == 0;
}

em_Equi_Color CItem::GetEquiColor() CONST
{
	switch (ReadBYTE(_dwModObject + 0x18 + 物品颜色偏移))
	{
	case 0:
		return em_Equi_Color::White;
	case 1:
		return em_Equi_Color::Magic;
	case 2:
		return em_Equi_Color::Rate;
	case 3:
		return em_Equi_Color::Legend;
	default:
		break;
	}

	return em_Equi_Color::None;
}

DWORD CItem::GetEquiLevel() CONST
{
	return ReadBYTE(_dwModObject + 物品需求等级偏移 - 0x4);
}


BOOL CItem::IsEqui() CONST
{
	return _IsEqui;
}