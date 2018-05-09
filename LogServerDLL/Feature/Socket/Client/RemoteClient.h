#ifndef __LFZL_LOGSERVERDLL_FEATURE_SOCKET_CLIENT_REMOTECLIENT_H__
#define __LFZL_LOGSERVERDLL_FEATURE_SOCKET_CLIENT_REMOTECLIENT_H__

#include <SocketCommon/SocketRemoteClient.h>

class CRemoteClient : public libTools::CSocketRemoteClient
{
public:
	CRemoteClient(_In_ UINT_PTR Sock);
	~CRemoteClient() = default;

	virtual VOID Remove() override;

	virtual VOID Add() override;

	virtual BOOL IsOnLine() CONST override;

	CONST std::wstring& GetClientName() CONST;
private:
	std::wstring _wsClientName;
};



#endif // !__LFZL_LOGSERVERDLL_FEATURE_SOCKET_CLIENT_REMOTECLIENT_H__
