#include "ReadMemory.h"
#include <ProcessLib\Process\Process.h>
#include <InjectorLib\DllInjector\DllInjector.h>

#pragma comment(lib,"InjectorLib.lib")
#pragma comment(lib,"ProcessLib.lib")

static HANDLE hGameProcess = NULL;
BOOL InitializeReadMemory()
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


	hGameProcess = ::OpenProcess(PROCESS_VM_READ, FALSE, dwPid);
	if (hGameProcess == NULL)
	{
		::MessageBoxW(NULL, L"OpenProcess ß∞‹!", L"", NULL);
		return FALSE;
	}

	return TRUE;
}

template<typename T>
T ReadMemory(_In_ UINT_PTR Addr)
{
	T dwValue = 0;
	if (!::ReadProcessMemory(hGameProcess, reinterpret_cast<LPCVOID>(Addr), &dwValue, sizeof(dwValue), 0))
	{
		return 0;
	}


	return dwValue;
}

DWORD ReadDWORD(_In_ DWORD dwAddr)
{
	return ReadMemory<DWORD>(dwAddr);
}

DWORD ReadBYTE(_In_ DWORD dwAddr)
{
	return ReadDWORD(dwAddr) & 0xFF;
}