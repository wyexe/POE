#include "RemoteClient.h"

CRemoteClient::CRemoteClient(_In_ UINT_PTR Sock) : CSocketRemoteClient(Sock)
{

}

VOID CRemoteClient::Remove()
{

}

VOID CRemoteClient::Add()
{
	
}

BOOL CRemoteClient::IsOnLine() CONST
{
	return !_wsClientName.empty();
}

CONST std::wstring& CRemoteClient::GetClientName() CONST
{
	return _wsClientName;
}
