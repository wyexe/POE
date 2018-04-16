#ifndef __LFZL_CHEATDLL_CORE_OBJECT_CHEST_H__
#define __LFZL_CHEATDLL_CORE_OBJECT_CHEST_H__

#include "BaseObject.h"

class CChest : public CBaseObject
{
public:
	CChest();
	CChest(_In_ DWORD dwNodeBase);
	~CChest();

	virtual VOID RefreshObjectAttribute() override;

	// 被打开过 ?
	BOOL IsOpened() CONST;
private:
	DWORD _dwChestOpenedAddr = NULL;
};




#endif // !__LFZL_CHEATDLL_CORE_OBJECT_CHEST_H__
