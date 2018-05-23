#include "RemoteClient.h"

CRemoteClient::CRemoteClient(_In_ UINT_PTR Sock) : CSocketRemoteClient(Sock)
{
	
}

CONST std::wstring& CRemoteClient::GetClientName() CONST
{
	return _wsClientName;
}

VOID CRemoteClient::SetClientName(_In_ CONST std::wstring& wsClientName)
{
	_wsClientName = wsClientName;
}

BOOL CRemoteClient::IsOnLine() CONST
{
	return !_wsClientName.empty();
}
