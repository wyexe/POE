#ifndef __LFZL_CHEATDLL_CORE_OBJECT_PERSON_H__
#define __LFZL_CHEATDLL_CORE_OBJECT_PERSON_H__

#include "BaseObject.h"

class CPerson : public CBaseObject
{
public:
	CPerson() = default;
	CPerson(_In_ DWORD dwNodeBase);
	~CPerson() = default;

	static CPerson& GetInstance();

	virtual VOID RefreshObjectAttribute() override;


	//  Person Attribute
	DWORD GetPercentHP() CONST;

	//
	DWORD GetPercentMP() CONST;

	//
	DWORD GetPercentShield() CONST;

	//
	DWORD GetLevel() CONST;

	// Current Map
	std::wstring GetMapName();

	//
	DWORD GetLifeAttributeAddr() CONST;

	//
	BOOL IsMoving() CONST;
private:
	DWORD GetPercentValue(_In_ DWORD dwOffset) CONST;
private:
	DWORD _dwLifeAttributeAddr = NULL;
	DWORD _dwPlayerAttributeAddr = NULL;
	DWORD _dwAreaLoadingStateAddr = NULL;
};



#endif // !__LFZL_CHEATDLL_CORE_OBJECT_PERSON_H__
