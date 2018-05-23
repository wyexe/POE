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

	virtual BOOL Run(_In_ SHORT shPort, _In_ UINT uMaxAccept) override;

	virtual void Stop() override;


	std::wstring GetOnLineClientArrayText();

	BOOL DoAction_By_ClientName(_In_ CONST std::wstring& wsClientName, _In_ std::function<VOID(CRemoteClient*,libTools::CSocketBuffer&)> Ptr);
private:
	static DWORD WINAPI _WorkThread(LPVOID lpParam);
private:
	HANDLE						_hWorkThread = NULL;
	CRITICAL_SECTION			_LockVecClient;
	std::vector<CRemoteClient*> _VecClient;
	
};



#endif // !__LFZL_LOGSERVERDLL_FEATURE_SOCKET_SOCKETSERVER_H__
