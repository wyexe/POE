#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_NPC_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_NPC_H__

#include "BaseObject.h"

class CNpc : public CBaseObject
{
public:
	CNpc();
	CNpc(_In_ DWORD dwNodeBase);
	~CNpc();

	virtual VOID RefreshObjectAttribute() override;
private:
	
};


#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_NPC_H__
