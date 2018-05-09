#include <Windows.h>
#include <Feature/Socket/SocketServer.h>
#include <CharacterLib/Character.h>
#include <Feature/EchoLog/EchoLog.h>
#include <TimeLib/TimeCharacter.h>

#pragma comment(lib,"TimeLib.lib")

BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	return TRUE;
}

extern "C" __declspec(dllexport) int WINAPIV Initialize()
{
	return CSocketServer::GetInstance().RunServer();
}

extern "C" __declspec(dllexport) void WINAPIV GetConnectedClient(_Out_ LPWSTR pwszClientArrayText)
{
	std::wstring wsText = CSocketServer::GetInstance().GetOnLineClientArrayText();
	libTools::CCharacter::strcpy_my(pwszClientArrayText, wsText.c_str(), wsText.length());
}

extern "C" __declspec(dllexport) int WINAPIV GetClientLog(_Out_ LPWSTR pwszClientName, _Out_ LPWSTR pwszLogText, _Out_ LPWSTR pwszTick)
{
	CEchoLog::LogContent Content;
	if (!CEchoLog::GetInstance().Front(Content))
	{
		return FALSE;
	}


	std::wstring wsTick = libTools::CCharacter::MakeFormatText(L"%d:%d:%d", Content.Tick.wHour, Content.Tick.wMinute, Content.Tick.wSecond);
	libTools::CCharacter::strcpy_my(pwszTick, wsTick.c_str(), wsTick.length());
	libTools::CCharacter::strcpy_my(pwszClientName, Content.wsClientName.c_str(), Content.wsClientName.length());
	libTools::CCharacter::strcpy_my(pwszLogText, Content.wsLogText.c_str(), Content.wsLogText.length());
	return TRUE;
}

extern "C" __declspec(dllexport) void WINAPIV SendCmdToClient(_In_ LPCWSTR pwszClientName, _In_ LPCWSTR pwszCmdText)
{

}