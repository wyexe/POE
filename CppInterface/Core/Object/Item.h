#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_ITEM_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_ITEM_H__

#include "BaseObject.h"

class CItem : public CBaseObject
{
public:
	struct ItemPoint
	{
		DWORD dwLeftTopIndex;
		DWORD dwRightTopIndex;
		DWORD dwLeftBottomIndex;
		DWORD dwRightBottomIndex;
	};
public:
	CItem();
	CItem(_In_ DWORD dwNodeBase);
	~CItem();

	virtual VOID RefreshObjectAttribute() override;

	// 位置
	ItemPoint	GetItemLocation() CONST;
	VOID		SetItemLocation(_In_ DWORD dwLeftTop, _In_ DWORD dwRightTop, _In_ DWORD dwLeftBottom, _In_ DWORD dwRightBottom);

	// 药剂
	DWORD		GetPercentCharges() CONST;
	VOID		SetChargesAddr(_In_ DWORD dwChargesObject);

	// 数量
	DWORD		GetCount() CONST;
	DWORD		GetPercentCount() CONST;
	VOID		SetStackAddr(_In_ DWORD dwStackObject);

	// 品质
	DWORD		GetQuality() CONST;
	VOID		SetQuality(_In_ DWORD dwQuality);

	// 是否绑定账号的物品
	BOOL		IsBindAccount() CONST;
	VOID		SetIsBindAccount(_In_ BOOL bBindAccount);

	// 是否未鉴定的物品
	BOOL		IsNotAppraisal() CONST;
	VOID		SetIsNotAppraisal(_In_ BOOL bValue);

private:
	ItemPoint	_ItemPos;
	DWORD		_dwChargesObject = NULL;
	DWORD		_dwStackObject   = NULL;
	DWORD		_dwQuality       = NULL;
	BOOL		_bIsBindAccount  = FALSE;
	BOOL		_IsNotAppraisal  = FALSE;
};


#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_ITEM_H__
