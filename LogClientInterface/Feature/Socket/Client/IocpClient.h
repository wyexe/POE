#ifndef __LFZL_LOGCLIENTINTERFACE_FEATURE_SOCKET_CLIENT_IOCPCLIENT_H__
#define __LFZL_LOGCLIENTINTERFACE_FEATURE_SOCKET_CLIENT_IOCPCLIENT_H__

#include <LogServerDLL/Common/Common.h>
#include <SocketClientLib/SocketBaseClientService.h>
#include <SocketCommon/SocketBuffer.h>
#include <ProcessLib/Lock/Lock.h>

class CIocpClient : public libTools::CSocketBaseClientService, public libTools::CThreadLock
{
public:
	CIocpClient() = default;
	virtual ~CIocpClient() = default;

	static CIocpClient& GetInstance();

	BOOL AsyncSend(_In_ libTools::CSocketBuffer& SocketBuffer);

	BOOL AsyncSend(_In_ em_Sock_Msg Msg, _In_ std::function<VOID(libTools::CSocketBuffer&)> FillBufferPtr);

	BOOL SyncSend(_In_ libTools::CSocketBuffer& SocketBuffer, _In_ std::function<VOID(libTools::CSocketBuffer&)> EchoPtr);

	VOID SetDisConnectPtr(_In_ std::function<VOID(VOID)> DisConnectPtr);
protected:
	virtual VOID EchoPacket(_In_ libTools::CSocketBuffer& SocketBuffer) override;

	virtual VOID DisConnectServer() override;
private:
	DWORD _dwMsgHead;
	HANDLE _hEvent;
	std::function<VOID(libTools::CSocketBuffer& SocketBuffer)> _EchoPtr;
	std::function<VOID(VOID)> _DisConnectPtr;
};

#endif // !__LFZL_LOGCLIENTINTERFACE_FEATURE_SOCKET_CLIENT_IOCPCLIENT_H__
