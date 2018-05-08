#ifndef __LFZL_CHEATDLL_CORE_OBJECT_BASEOBJECT_H__
#define __LFZL_CHEATDLL_CORE_OBJECT_BASEOBJECT_H__

#include <GameStruct.h>
#include <string>

class CBaseObject
{
public:
	CBaseObject() = default;
	virtual ~CBaseObject() = default;

	DWORD GetNodeBase() CONST;

	VOID SetNodeBase(_In_ DWORD dwNodeBase);

	CONST std::wstring& GetName() CONST;

	VOID SetName(_In_ CONST std::wstring& wsName);

	CONST std::wstring& GetResName() CONST;

	VOID SetResName(_In_ CONST std::wstring& wsName);

	Point GetPoint() CONST;


	// ...........
	virtual VOID RefreshObjectAttribute() = NULL;

	//
	DWORD GetAttributeTablePtr() CONST;

	//
	virtual BOOL MoveToPos(_In_ float fDis = MIN_OBJECT_CLIENT_DIS);

	//
	virtual BOOL Click() CONST;

	//
	virtual float GetDis() CONST;
public:
	bool operator < (CONST CBaseObject& Rparam);
protected:
	DWORD			_dwNodeBase		= NULL;
	DWORD			_dwPositionedObject = NULL;
	std::wstring	_wsName;
	std::wstring	_wsResName;
	
};


#endif // !__LFZL_CHEATDLL_CORE_OBJECT_BASEOBJECT_H__
