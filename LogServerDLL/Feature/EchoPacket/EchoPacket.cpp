#include "EchoPacket.h"
#include <Feature/EchoLog/EchoLog.h>
#include <Feature/EchoFile/EchoFile.h>
#include <Common/Common.h>

#pragma comment(lib,"SocketServerLib.lib")

VOID CEchoPacket::KeepALive(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	pSocketBuffer->clear();
	pRemoteClient->SetKeepALive();
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
		*pSocketBuffer << 0;
	}
}

VOID CEchoPacket::SendLog(_In_ CRemoteClient* pRemoteClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	std::wstring wsLogText;
	*pSocketBuffer >> wsLogText;

	pRemoteClient->SetKeepALive();
	CEchoLog::GetInstance().Add(pRemoteClient->GetClientName(), wsLogText);
}
