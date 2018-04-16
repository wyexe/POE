#include <Windows.h>
#include <LogLib/Log.h>
#include <LogLib/CmdLog.h>
#include "Expr.h"

#pragma comment(lib,"LogLib.lib")
BOOL WINAPI DllMain(_In_ HINSTANCE ,_In_ DWORD fdwReason,_In_ LPVOID )
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		//::MessageBoxW(NULL, L"Run Log...", L"", NULL);
		libTools::CLog::GetInstance().SetClientName(L"TestDLL", L"Z:\\");
		//::MessageBoxW(NULL, L"Run Cmd...", L"", NULL);
		libTools::CCmdLog::GetInstance().Run(L"TestDLL", CExpr::GetInstance().GetVec());
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		//::MessageBoxW(NULL, L"Detah ...", L"", NULL);
		LOG_C_D(L"");
		libTools::CLog::GetInstance().Release();
		libTools::CCmdLog::GetInstance().Stop();
		CExpr::GetInstance().Release();
	}
	return TRUE;
}