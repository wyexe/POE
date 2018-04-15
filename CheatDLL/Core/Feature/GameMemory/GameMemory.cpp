#include "GameMemory.h"
#include <ProcessLib\Process\Process.h>
#include <InjectorLib\DllInjector\DllInjector.h>
#include <memory>

#pragma comment(lib,"InjectorLib.lib")
#pragma comment(lib,"ProcessLib.lib")


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

std::wstring CGameMemory::ReadProcTextWithLength(_In_ DWORD dwAddr)
{
	WCHAR wszText[64] = { 0 };
	::ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(dwAddr), wszText, sizeof(wszText), NULL);
	return std::wstring(wszText);
}

std::wstring CGameMemory::ReadProcTextWithoutLength(_In_ DWORD dwAddr)
{
	DWORD dwTextLength = ReadProcDWORD(dwAddr + 0x10);

	std::shared_ptr<WCHAR> pwszText(new WCHAR[dwTextLength + 1], [](WCHAR* p) { delete[] p; });
	ZeroMemory(pwszText.get(), dwTextLength + 1);

	::ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(ReadProcDWORD(dwAddr + 0x14) >= 0x7 ? ReadProcDWORD(dwAddr) : dwAddr), pwszText.get(), dwTextLength * sizeof(WCHAR), NULL);
	return std::wstring(pwszText.get());
}

std::string CGameMemory::ReadProcASCIITextWithoutLength(_In_ DWORD dwAddr)
{
	CHAR szText[64] = { 0 };
	::ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(dwAddr), szText, sizeof(szText), NULL);
	return std::string(szText);
}
