#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_BASEOBJECT_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_BASEOBJECT_H__


#include <GameStruct.h>

class CBaseObject
{
public:
	CBaseObject() = default;
	virtual ~CBaseObject() = default;

	DWORD GetNodeBase() CONST;

	VOID SetNodeBase(_In_ DWORD dwNodeBase);

	CONST std::wstring& GetName() CONST;

	VOID SetName(_In_ LPCWSTR pwszName);

	CONST std::wstring& GetResName() CONST;

	VOID SetResName(_In_ LPCWSTR pwszResName);

	Point GetPoint() CONST;


	// ...........
	virtual VOID RefreshObjectAttribute() = NULL;
protected:
	DWORD			_dwNodeBase		= NULL;
	DWORD			_dwPositionedObject = NULL;
	std::wstring	_wsName;
	std::wstring	_wsResName;
	
};


#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_BASEOBJECT_H__