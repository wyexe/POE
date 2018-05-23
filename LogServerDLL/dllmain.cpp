#include <Windows.h>
#include <Feature/Socket/SocketServer.h>
#include <CharacterLib/Character.h>
#include <Feature/EchoLog/EchoLog.h>
#include <TimeLib/TimeCharacter.h>
#include <SocketCommon/SocketBuffer.h>
#include <Common/Common.h>
#include <Feature/EchoLog/EchoCmd.h>

#ifdef _DEBUG
#pragma comment(lib,"TimeLib_Debug.lib")
#pragma comment(lib,"CharacterLib_Debug.lib")
#pragma comment(lib,"FileLib_Debug.lib")
#pragma comment(lib,"AlgroithmLib_Debug.lib")
#pragma comment(lib,"SocketCommonLib_Debug.lib")
#pragma comment(lib, "SocketServerLib_Debug.lib")
#else
#pragma comment(lib,"TimeLib.lib")
#pragma comment(lib,"CharacterLib.lib")
#pragma comment(lib,"FileLib.lib")
#pragma comment(lib,"AlgroithmLib.lib")
#pragma comment(lib,"SocketCommonLib.lib")
#pragma comment(lib,"SocketServerLib.lib")
#endif // _DEBUG

BOOL WINAPI DllMain(_In_ HINSTANCE , _In_ DWORD fdwReason, _In_ LPVOID )
{
	if (fdwReason == DLL_PROCESS_DETACH)
	{
		CSocketServer::GetInstance().Stop();
	}
	return TRUE;
}

extern "C" __declspec(dllexport) int WINAPIV Initialize()
{
	return CSocketServer::GetInstance().Run(LFZL_LOG_SOCKET_PORT, 100);
}

extern "C" __declspec(dllexport) void WINAPIV GetConnectedClient(_Out_ LPWSTR pwszClientArrayText)
{
	std::wstring wsText = CSocketServer::GetInstance().GetOnLineClientArrayText();
	libTools::CCharacter::strcpy_my(pwszClientArrayText, wsText.c_str(), wsText.length());
}

extern "C" __declspec(dllexport) int WINAPIV GetClientLog(_Out_ LPWSTR pwszClientName, _Out_ LPWSTR pwszLogText)
{
	CEchoLog::LogContent Content;
	if (!CEchoLog::GetInstance().Front(Content))
	{
		return FALSE;
	}


	libTools::CCharacter::strcpy_my(pwszClientName, Content.wsClientName.c_str(), Content.wsClientName.length());
	libTools::CCharacter::strcpy_my(pwszLogText, Content.wsLogText.c_str(), Content.wsLogText.length());
	return TRUE;
}

extern "C" __declspec(dllexport) void WINAPIV SendCmdToClient(_In_ LPCWSTR pwszClientName, _In_ LPCWSTR pwszCmdText)
{
	CEchoCmd::GetInstance().Add(pwszClientName, pwszCmdText);
}