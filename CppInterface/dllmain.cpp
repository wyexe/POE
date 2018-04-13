#include <Windows.h>
#include <string>
#include <ProcessLib\Process\Process.h>
#include <ProcessLib\KeyboardMsg\KeyboardMsg.h>
#include <CharacterLib\Character.h>
#include <Core\Feature\ReadMemory\ReadMemory.h>

#pragma comment(lib,"ProcessLib.lib")
#pragma comment(lib,"user32.lib")

#pragma comment(lib,"CharacterLib.lib")

BOOL WINAPI DllMain(_In_ HINSTANCE , _In_ DWORD dwReason, _In_ LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{

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
	HWND hWeGameAD = ::FindWindowW(L"TWINCONTROL", L"�����Ƽ�");
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


// ��ȡ�ڴ� Initialize
extern "C" __declspec(dllexport) int WINAPIV Initialize()
{
	return InitializeReadMemory();
}


/*


extern "C" __declspec(dllexport) void WINAPIV ReadText(_In_ DWORD dwAddr, _Out_ LPWSTR pwszText)
{
	DWORD dwTextLen = ReadDWORD(dwAddr + 0x10);
	if (dwTextLen >= 32)
	{
		::MessageBoxW(NULL, L"Text.Length >= 32.... Really?", L"", NULL);
		return;
	}


	::ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(ReadDWORD(dwAddr + 0x14) >= 0xF ? ReadDWORD(dwAddr) : dwAddr), pwszText, dwTextLen, 0);
}

extern "C" __declspec(dllexport) void WINAPIV ReadOnlyText(_In_ DWORD dwAddr, _Out_ LPWSTR pwszText)
{
	::ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dwAddr), pwszText, 32, 0);
	pwszText[30] = '\0';
	pwszText[31] = '\0';
}

extern "C" __declspec(dllexport) void WINAPIV ReadASCIIText(_In_ DWORD dwAddr, _Out_ LPWSTR pwszText)
{
	CHAR szText[32] = { 0 };
	::ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dwAddr), szText, _countof(szText), 0);
	szText[_countof(szText) - 1] = '\0';

	libTools::CCharacter::strcpy_my(pwszText, libTools::CCharacter::ASCIIToUnicode(std::string(szText)).c_str(), _countof(szText));
}

*/