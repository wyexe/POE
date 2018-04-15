#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_PERSON_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_PERSON_H__

#include "BaseObject.h"

class CPerson : public CBaseObject
{
public:
	CPerson() = default;
	~CPerson() = default;

	static CPerson& GetInstance();

	virtual VOID RefreshObjectAttribute() override;


	// 
	DWORD GetPercentHP() CONST;
	DWORD GetPercentMP() CONST;
	DWORD GetPercentShield() CONST;

	DWORD GetLevel() CONST;
private:
	DWORD GetPercentValue(_In_ DWORD dwOffset) CONST;
private:
	DWORD _dwLifeAttributeAddr = NULL;
	DWORD _dwPlayerAttributeAddr = NULL;
};



#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_PERSON_H__
