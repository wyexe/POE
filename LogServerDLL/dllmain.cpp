#include <Windows.h>
#include <Feature/Socket/SocketServer.h>
#include <CharacterLib/Character.h>
#include <Feature/EchoLog/EchoLog.h>
#include <TimeLib/TimeCharacter.h>
#include <SocketCommon/SocketBuffer.h>
#include <Common/Common.h>

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

extern "C" __declspec(dllexport) int WINAPIV SendCmdToClient(_In_ LPCWSTR pwszClientName, _In_ LPCWSTR pwszCmdText)
{
	return CSocketServer::GetInstance().DoAction_By_ClientName(pwszClientName, [pwszCmdText](CRemoteClient* pRemoteClient, libTools::CSocketBuffer& SocketBuffer)
	{
		SocketBuffer.InitializeHead(em_Sock_Msg_ServerCmd);
		SocketBuffer << std::wstring(pwszCmdText);
	});
}