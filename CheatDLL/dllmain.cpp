#include <Windows.h>
#include <ProcessLib\Process\Process.h>
#include <ProcessLib\KeyboardMsg\KeyboardMsg.h>
#include <CharacterLib\Character.h>
#include <LogLib\CmdLog.h>
#include <LogLib\Log.h>
#include <Expr\CmdExpr.h>
#include <Core\Feature\GameMemory\GameMemory.h>
#include <Core\Feature\Config\FileConfig.h>

#pragma comment(lib,"ProcessLib.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"CharacterLib.lib")
#pragma comment(lib,"LogLib.lib")

#define _SELF L"dllmain.cpp"
BOOL WINAPI DllMain(_In_ HINSTANCE, _In_ DWORD dwReason, _In_ LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Set Capacity = 100
		libTools::CCmdLog::GetInstance().Run(L"CheatDLL", CCmdExpr::GetInstance().GetVec());
		libTools::CLog::GetInstance().SetClientName(L"CheatDLL", L"C:\\Share\\DLL\\");
		libTools::CLog::GetInstance().SetSyncSendLog();
		if (!CGameMemory::GetInstance().InitializeReadMemory())
		{
			LOG_MSG_CF(L"InitializeReadMemory Faild!");
			return FALSE;
		}

		libTools::CCmdLog::GetInstance().PrintHelp();
		/*if (!CFileConfig::GetInstance().Initialize())
		{
			LOG_MSG_CF(L"CFileConfig.Initialize = FALSE");
			return FALSE;
		}*/
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		LOG_C_D(L"Free Cheat.DLL");
	}
	return TRUE;
}


