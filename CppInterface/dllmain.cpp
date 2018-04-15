#include <Windows.h>
#include <string>
#include <ProcessLib\Process\Process.h>
#include <ProcessLib\KeyboardMsg\KeyboardMsg.h>
#include <CharacterLib\Character.h>

#include <LogLib\Log.h>

#pragma comment(lib,"ProcessLib.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"CharacterLib.lib")
#pragma comment(lib,"LogLib.lib")

#define _SELF L"dllmain.cpp"
BOOL WINAPI DllMain(_In_ HINSTANCE , _In_ DWORD dwReason, _In_ LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Set Capacity = 100
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

	}
	return TRUE;
}

extern "C" __declspec(dllexport) int WINAPIV ExistProcByName(_In_ LPCWSTR pwszProcName)
{
	return libTools::CProcess::IsExistProcName(std::wstring(pwszProcName));
}

extern "C" __declspec(dllexport) int WINAPIV ExistInstanceMutex()
{
	HANDLE hMutex = ::OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"Mutex_LF_Console");
	if (hMutex != NULL)
	{
		::CloseHandle(hMutex);
		return TRUE;
	}

	return FALSE;
}

extern "C" __declspec(dllexport) int WINAPIV ExistCheatMutex()
{
	HANDLE hMutex = ::OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"Mutex_LF_Cheat");
	if (hMutex != NULL)
	{
		::CloseHandle(hMutex);
		return TRUE;
	}
	
	return FALSE;
}

extern "C" __declspec(dllexport) void WINAPIV CreateInstanceMutex()
{
	::CreateMutexW(NULL, NULL, L"Mutex_LF_Console");
}

extern "C" __declspec(dllexport) void WINAPIV ShowWeGame()
{
	HWND hWeGameAD = ::FindWindowW(L"TWINCONTROL", L"今日推荐");
	if (hWeGameAD != NULL)
	{
		::SendMessageW(hWeGameAD, WM_CLOSE, NULL, NULL);
	}


	HWND hWnd = ::FindWindowW(L"TWINCONTROL", L"WeGame");
	if (hWnd != NULL)
	{
		::SwitchToThisWindow(hWnd, TRUE);
	}
}

// 读取内存 Initialize
extern "C" __declspec(dllexport) int WINAPIV Initialize()
{
	//return CGameMemory::GetInstance().InitializeReadMemory();
}



