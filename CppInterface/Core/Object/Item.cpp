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
	CAttributeObject::FillEquiObjectAttribute_Stack(this);
	
	// 药剂
	if (GetType() == em_Object_Type::Flasks)
	{
		CAttributeObject::FillFlasksObjectAttribute_Charges(this);
	}

	// 品质
	CAttributeObject::FillEquiObjectAttribute_Quality(this);

	// 是否绑定
	CAttributeObject::FillObjectAttribute_IsBindAccount(this);

	// 是否未鉴定
	CAttributeObject::FillEquiObjectAttribute_Appraisal(this);
}

CItem::ItemPoint CItem::GetItemLocation() CONST
{
	return _ItemPos;
}

VOID CItem::SetItemLocation(_In_ DWORD dwLeftTop, _In_ DWORD dwRightTop, _In_ DWORD dwLeftBottom, _In_ DWORD dwRightBottom)
{
	_ItemPos.dwLeftTopIndex = dwLeftTop;
	_ItemPos.dwRightTopIndex = dwRightTop;
	_ItemPos.dwLeftBottomIndex = dwLeftBottom;
	_ItemPos.dwRightBottomIndex = dwRightBottom;
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

VOID CItem::SetChargesAddr(_In_ DWORD dwChargesObject)
{
	_dwChargesObject = dwChargesObject;
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

VOID CItem::SetStackAddr(_In_ DWORD dwStackObject)
{
	_dwStackObject = dwStackObject;
}

DWORD CItem::GetQuality() CONST
{
	return _dwQuality;
}

VOID CItem::SetQuality(_In_ DWORD dwQuality)
{
	_dwQuality = dwQuality;
}

BOOL CItem::IsBindAccount() CONST
{
	return _bIsBindAccount;
}

VOID CItem::SetIsBindAccount(_In_ BOOL bBindAccount)
{
	_bIsBindAccount = bBindAccount;
}

BOOL CItem::IsNotAppraisal() CONST
{
	return _IsNotAppraisal;
}

VOID CItem::SetIsNotAppraisal(_In_ BOOL bValue)
{
	_IsNotAppraisal = bValue;
}
