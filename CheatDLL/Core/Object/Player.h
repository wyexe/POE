#ifndef __LFZL_CHEATDLL_CORE_OBJECT_PLAYER_H__
#define __LFZL_CHEATDLL_CORE_OBJECT_PLAYER_H__

#include "BaseObject.h"

class CPlayer : public CBaseObject
{
public:
	CPlayer();
	CPlayer(_In_ DWORD dwNodeBase);
	~CPlayer();

	virtual VOID RefreshObjectAttribute() override;
private:

};



#endif // !__LFZL_CHEATDLL_CORE_OBJECT_PLAYER_H__
