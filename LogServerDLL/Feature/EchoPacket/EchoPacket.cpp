#include "EchoPacket.h"
#include <Feature/EchoLog/EchoLog.h>
#include <Feature/EchoFile/EchoFile.h>
#include <Feature/EchoLog/EchoCmd.h>
#include <Common/Common.h>


VOID CEchoPacket::KeepALive(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	pRemoteClient->SetKeepALive();

	pSocketBuffer->clear();
	pSocketBuffer->InitializeHead(em_Sock_Msg_KeepLive);
}

VOID CEchoPacket::DownloadFile(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	std::wstring wsFileName;
	*pSocketBuffer >> wsFileName;


	pSocketBuffer->clear();
	pRemoteClient->SetKeepALive();
	pSocketBuffer->InitializeHead(em_Sock_Msg_DownLoad_File);


	if (!CEchoFile::ReadFileContent(wsFileName, *pSocketBuffer))
	{
		pSocketBuffer->clear();
		*pSocketBuffer << 0/*FileSize*/;
		return;
	}
}

VOID CEchoPacket::SendLog(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	std::wstring wsLogText;
	*pSocketBuffer >> wsLogText;

	pRemoteClient->SetKeepALive();
	CEchoLog::GetInstance().Add(pRemoteClient->GetClientName(), wsLogText);

	pSocketBuffer->clear();
	pSocketBuffer->InitializeHead(em_Sock_Msg_Log);
}

VOID CEchoPacket::IsExistCmd(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	pSocketBuffer->clear();
	pSocketBuffer->InitializeHead(em_Sock_Msg_IsExistCmd);

	CEchoCmd::CmdContent Content;
	if (!CEchoCmd::GetInstance().Find(pRemoteClient->GetClientName(), Content))
	{
		*pSocketBuffer << FALSE;
		return;
	}


	*pSocketBuffer << TRUE << Content.wsLogText;
	pRemoteClient->SetKeepALive();
}

VOID CEchoPacket::ClientInitialize(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	std::wstring wsClientName;
	*pSocketBuffer >> wsClientName;
	pRemoteClient->SetClientName(wsClientName);


	pSocketBuffer->clear();
	pSocketBuffer->InitializeHead(em_Sock_Msg_Initialize);
}
