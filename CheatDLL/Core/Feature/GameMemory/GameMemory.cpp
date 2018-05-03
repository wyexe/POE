#include "GameMemory.h"
#include <ProcessLib\Process\Process.h>
#include <InjectorLib\DllInjector\DllInjector.h>
#include <LogLib\Log.h>
#include <memory>

#pragma comment(lib,"InjectorLib.lib")
#pragma comment(lib,"ProcessLib.lib")

#define _SELF L"GameMemory.cpp"
CGameMemory& CGameMemory::GetInstance()
{
	static CGameMemory Instance;
	return Instance;
}

BOOL CGameMemory::InitializeReadMemory()
{
	DWORD dwPid = libTools::CProcess::FindPidByProcName(L"PathOfExile.exe");
	if (dwPid == NULL)
	{
		::MessageBoxW(NULL, L"UnExist Game Process!", L"", NULL);
		return FALSE;
	}


	if (!libTools::CDllInjector::PromotionAuthority())
	{
		::MessageBoxW(NULL, L"Ã·…˝»®œﬁ ß∞‹!", L"", NULL);
		return FALSE;
	}


	_hProcess = ::OpenProcess(PROCESS_VM_READ, FALSE, dwPid);
	if (_hProcess == NULL)
	{
		::MessageBoxW(NULL, L"OpenProcess ß∞‹!", L"", NULL);
		return FALSE;
	}

	_hWnd = ::FindWindowW(L"POEWindowClass", L"Path of Exile");
	if (_hWnd == NULL)
	{
		::MessageBoxW(NULL, L"FindWindowW ß∞‹!", L"", NULL);
		return FALSE;
	}

	return TRUE;
}

DWORD CGameMemory::ReadProcDWORD(_In_ DWORD dwAddr)
{
	return ReadMemory<DWORD>(dwAddr);
}

DWORD CGameMemory::ReadProcBYTE(_In_ DWORD dwAddr)
{
	return ReadProcDWORD(dwAddr) & 0xFF;
}


float CGameMemory::ReadProcFloat(_In_ DWORD dwAddr)
{
	return ReadMemory<float>(dwAddr);
}

std::wstring CGameMemory::ReadProcTextWithLength(_In_ DWORD dwAddr)
{
	DWORD dwTextLength = ReadProcDWORD(dwAddr + 0x10);
	if (dwTextLength < 128)
	{
		WCHAR wszText[128] = { 0 };
		::ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(ReadProcDWORD(dwAddr + 0x14) > 0x7 ? ReadProcDWORD(dwAddr) : dwAddr), wszText, dwTextLength * sizeof(WCHAR), NULL);
		//LOG_C_D(L"dwAddr=[%X], dwTextLength=[%d]", dwAddr, dwTextLength);
		return std::wstring(wszText);
	}
	else
	{
		LOG_C_E(L"dwAddr=[%X], dwTextLength=[%d]", dwAddr, dwTextLength);
	}
	return L"";
	
}

std::wstring CGameMemory::ReadProcTextWithoutLength(_In_ DWORD dwAddr)
{
	WCHAR wszText[128] = { 0 };
	::ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(dwAddr), wszText, sizeof(wszText), NULL);
	return std::wstring(wszText);
}

std::string CGameMemory::ReadProcASCIITextWithoutLength(_In_ DWORD dwAddr)
{
	CHAR szText[128] = { 0 };
	::ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(dwAddr), szText, sizeof(szText), NULL);
	return std::string(szText);
}

HWND CGameMemory::GetGameWnd() CONST
{
	return _hWnd;
}
