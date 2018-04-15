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
}

CONST std::wstring& CBaseObject::GetName() CONST
{
	return _wsName;
}

VOID CBaseObject::SetName(_In_ CONST std::wstring& wsName)
{
	_wsName = wsName;
}

CONST std::wstring& CBaseObject::GetResName() CONST
{
	return _wsResName;
}

VOID CBaseObject::SetResName(_In_ CONST std::wstring& wsResName)
{
	_wsResName = wsResName;
}

Point CBaseObject::GetPoint() CONST
{
	return Point(ReadDWORD(_dwPositionedObject + 0x10), ReadDWORD(_dwPositionedObject + 0x14));
}