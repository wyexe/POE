#ifndef __LFZL_LOGSERVERDLL_FEATURE_ECHOPACKET_ECHOPACKET_H__
#define __LFZL_LOGSERVERDLL_FEATURE_ECHOPACKET_ECHOPACKET_H__

#include <Feature/Socket/Client/RemoteClient.h>
#include <SocketCommon/SocketBuffer.h>

class CEchoPacket
{
public:
	CEchoPacket() = default;
	~CEchoPacket() = default;

	static VOID KeepALive(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer);

	static VOID DownloadFile(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer);

	static VOID SendLog(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer);

	static VOID IsExistCmd(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer);

	static VOID ClientInitialize(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer);
private:

};




#endif // !__LFZL_LOGSERVERDLL_FEATURE_ECHOPACKET_ECHOPACKET_H__
