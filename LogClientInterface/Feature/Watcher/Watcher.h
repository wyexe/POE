#ifndef __LFZL_LOGCLIENTINTERFACE_FEATURE_WATCHER_WATCHER_H__
#define __LFZL_LOGCLIENTINTERFACE_FEATURE_WATCHER_WATCHER_H__

#include <queue>
#include <string>
#include <ProcessLib/Lock/Lock.h>

class CCmdWatcher : public libTools::CThreadLock
{
public:
	CCmdWatcher() = default;
	~CCmdWatcher();

	static CCmdWatcher GetInstance();

	BOOL Run();

	VOID Stop();

	VOID InitializeClientToServer(_In_ CONST std::wstring& wsClientName);

	VOID DownloadCheatFile();
private:
	VOID Release();

	BOOL SendKeepALive();

	VOID CheckExcuteCmd();

	VOID ExcuteCmd(_In_ CONST std::wstring& wsCmd);
private:
	static DWORD WINAPI _WatchThread(LPVOID lpParam);
private:
	BOOL   _IsRun		= FALSE;
	HANDLE _hThread		= NULL;
	std::queue<std::wstring> _VecCmd;
};




#endif // !__LFZL_LOGCLIENTINTERFACE_FEATURE_WATCHER_WATCHER_H__
