#include <Windows.h>
#include <Feature/Watcher/Watcher.h>
#include <LogLib/Log.h>

#define _SELF L"dllmain.cpp"
BOOL WINAPI DllMain(_In_ HINSTANCE , _In_ DWORD fdwReason, _In_ LPVOID )
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		if (!CCmdWatcher::GetInstance().Run())
		{
			LOG_MSG_CF(L"Connected Server Faild!");
			return FALSE;
		}

		CCmdWatcher::GetInstance().InitializeClientToServer(L"TransferClient");
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		CCmdWatcher::GetInstance().Stop();
	}
	return TRUE;
}