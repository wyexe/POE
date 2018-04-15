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

	// 药剂
	DWORD		GetPercentCharges() CONST;

	// 数量
	DWORD		GetCount() CONST;
	DWORD		GetPercentCount() CONST;

	// 品质
	DWORD		GetQuality() CONST;

	// 是否绑定账号的物品
	BOOL		IsBindAccount() CONST;

	// 是否未鉴定的物品  未鉴定=TRUE
	BOOL		IsNotAppraisal() CONST;

	// 颜色
	em_Equi_Color GetEquiColor() CONST;

	std::wstring GetEquiColorText() CONST;

	// 等级
	DWORD GetEquiLevel() CONST;

	// 是否装备
	BOOL  IsEqui() CONST;

	// 
	em_Object_Type GetType() CONST;
protected:
	ItemPoint	_ItemPos;
	DWORD		_dwChargesObject = NULL;
	DWORD		_dwStackObject   = NULL;
	DWORD		_dwQualityObject = NULL;
	DWORD		_dwBaseObject    = NULL;
	DWORD		_dwModObject	 = NULL;
	BOOL		_IsEqui			 = FALSE;
	em_Object_Type  _emObjectType = em_Object_Type::Other;
};


#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_ITEM_H__
