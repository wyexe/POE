#include "BaseObject.h"
#include "AttributeObject.h"
#include <vector>
#include <algorithm>

DWORD CBaseObject::GetNodeBase() CONST
{
	return _dwNodeBase;
}

VOID CBaseObject::SetNodeBase(_In_ DWORD dwNodeBase)
{
	_dwNodeBase = dwNodeBase;
	/*if (_dwNodeBase != NULL)
	{
		CAttributeObject::FillObjectAttribute_ResName(this);
	}*/
}

CONST std::wstring& CBaseObject::GetName() CONST
{
	return _wsName;
}

VOID CBaseObject::SetName(_In_ LPCWSTR pwszName)
{
	_wsName = pwszName;
}

CONST std::wstring& CBaseObject::GetResName() CONST
{
	return _wsResName;
}

VOID CBaseObject::SetResName(_In_ LPCWSTR pwszResName)
{
	_wsResName = pwszResName;
}

Point CBaseObject::GetPoint() CONST
{
	return Point(ReadDWORD(_dwPositionedObject + 0x10), ReadDWORD(_dwPositionedObject + 0x14));
}