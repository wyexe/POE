#ifndef __LFZL_LOGSERVERDLL_FEATURE_SOCKET_CLIENT_REMOTECLIENT_H__
#define __LFZL_LOGSERVERDLL_FEATURE_SOCKET_CLIENT_REMOTECLIENT_H__

#include <SocketCommon/SocketRemoteClient.h>

class CRemoteClient : public libTools::CSocketRemoteClient
{
public:
	CRemoteClient(_In_ UINT_PTR Sock);
	~CRemoteClient() = default;

	CONST std::wstring& GetClientName() CONST;

	VOID SetClientName(_In_ CONST std::wstring& wsClientName);

	virtual BOOL IsOnLine() CONST;
private:
	std::wstring _wsClientName;
};



#endif // !__LFZL_LOGSERVERDLL_FEATURE_SOCKET_CLIENT_REMOTECLIENT_H__
