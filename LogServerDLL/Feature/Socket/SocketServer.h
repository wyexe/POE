#ifndef __LFZL_LOGSERVERDLL_FEATURE_SOCKET_SOCKETSERVER_H__
#define __LFZL_LOGSERVERDLL_FEATURE_SOCKET_SOCKETSERVER_H__

#include <vector>
#include <SocketServerLib/SocketBaseServerService.h>


class CRemoteClient;
class CSocketServer : public libTools::CSocketBaseServerService
{
public:
	CSocketServer();
	~CSocketServer();

	static CSocketServer& GetInstance();

	virtual libTools::CSocketRemoteClient* CreateNewSocketClient(_In_ UINT_PTR ClientSock) override;

	virtual VOID ReleaseSocketClient(_In_ libTools::CSocketRemoteClient* pSocketClient) override;

	virtual BOOL EchoRecive(_In_ libTools::CSocketRemoteClient* pSocketClient, _In_ libTools::CSocketBuffer* pSocketBuffer) override;

	BOOL RunServer();


	std::wstring GetOnLineClientArrayText();
private:
	static DWORD WINAPI _WorkThread(LPVOID lpParam);
private:
	HANDLE						_hWorkThread = NULL;
	CRITICAL_SECTION			_LockVecClient;
	std::vector<CRemoteClient*> _VecClient;
	
};



#endif // !__LFZL_LOGSERVERDLL_FEATURE_SOCKET_SOCKETSERVER_H__
