#ifndef __LFZL_CHEATDLL_CORE_OBJECT_WORLDITEM_H__
#define __LFZL_CHEATDLL_CORE_OBJECT_WORLDITEM_H__

#include "Item.h"

class CWorldItem : public CItem
{
public:
	CWorldItem();
	CWorldItem(_In_ DWORD dwNodeBase);
	~CWorldItem();

	virtual VOID RefreshObjectAttribute() override;
};


#endif // !__LFZL_CHEATDLL_CORE_OBJECT_WORLDITEM_H__
