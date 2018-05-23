#include "SocketServer.h"
#include <SocketCommon/SocketBuffer.h>
#include <Feature/Socket/Client/RemoteClient.h>
#include <Common/Common.h>
#include <LogLib/Log.h>
#include <Feature/EchoPacket/EchoPacket.h>

#define _SELF L"SocketServer.cpp"

CSocketServer::CSocketServer()
{
	::InitializeCriticalSection(&_LockVecClient);
}

CSocketServer::~CSocketServer()
{
	Stop();
	if (_hWorkThread != NULL)
	{
		::WaitForSingleObject(_hWorkThread, INFINITE);
		_hWorkThread = NULL;
	}

	::DeleteCriticalSection(&_LockVecClient);
}

CSocketServer& CSocketServer::GetInstance()
{
	static CSocketServer Instance;
	return Instance;
}

libTools::CSocketRemoteClient* CSocketServer::CreateNewSocketClient(_In_ UINT_PTR ClientSock)
{
	return new CRemoteClient(ClientSock);
}

VOID CSocketServer::ReleaseSocketClient(_In_ libTools::CSocketRemoteClient* pSocketClient)
{
	pSocketClient->DisConnect();
	pSocketClient->Remove();
	delete dynamic_cast<CRemoteClient *>(pSocketClient);
	pSocketClient = nullptr;
}

BOOL CSocketServer::EchoRecive(_In_ libTools::CSocketRemoteClient* pSocketClient, _In_ libTools::CSocketBuffer* pSocketBuffer)
{
	em_Sock_Msg emSockMsg;
	// Test
	libTools::CSocketBuffer tmpSocketBuffer = *pSocketBuffer;
	auto Error = pSocketBuffer->VerDataPtr(emSockMsg);
	if (Error != libTools::CSocketBuffer::em_SocketBuffer_Error_None)
	{
		LOG_MSG_CF(L"数据包效验错误!. Err=%d", Error);

		DWORD dwSize, dwValue1, dwValue2, dwValue3 = 0;
		tmpSocketBuffer >> dwSize >> dwValue1 >> dwValue2 >> dwValue3;
		LOG_CF_E(L"dwSize=%d, dwValue1=%X, dwValue2=%X,dwValue3=%X, BufferSize=%d", dwSize, dwValue1, dwValue2, dwValue3, tmpSocketBuffer.size());
		return FALSE;
	}


	CRemoteClient* pRemoteClient = dynamic_cast<CRemoteClient*>(pSocketClient);
	switch (emSockMsg)
	{
	case em_Sock_Msg_KeepLive:
		CEchoPacket::KeepALive(pRemoteClient, pSocketBuffer);
		PostSend(pSocketClient, pSocketBuffer);
		break;
	case em_Sock_Msg_Log:
		CEchoPacket::SendLog(pRemoteClient, pSocketBuffer);
		PostSend(pSocketClient, pSocketBuffer);
		break;
	case em_Sock_Msg_DownLoad_File:
		CEchoPacket::DownloadFile(pRemoteClient, pSocketBuffer);
		PostSend(pSocketClient, pSocketBuffer);
		break;
	case em_Sock_Msg_IsExistCmd:
		CEchoPacket::IsExistCmd(pRemoteClient, pSocketBuffer);
		PostSend(pSocketClient, pSocketBuffer);
		break;
	case em_Sock_Msg_Initialize:
		CEchoPacket::ClientInitialize(pRemoteClient, pSocketBuffer);
		PostSend(pSocketClient, pSocketBuffer);
		break;
	default:
		break;
	}

	return TRUE;
}

BOOL CSocketServer::Run(_In_ SHORT shPort, _In_ UINT uMaxAccept)
{
	return RunServer(shPort, uMaxAccept);
}


void CSocketServer::Stop()
{
	StopServer();
}

std::wstring CSocketServer::GetOnLineClientArrayText()
{
	std::wstring wsText;
	::EnterCriticalSection(&_LockVecClient);
	for (auto& itm : _VecClient)
	{
		if (itm->IsOnLine())
		{
			wsText += itm->GetClientName();
			wsText += L"\r\n";
		}
	}
	::LeaveCriticalSection(&_LockVecClient);
	return wsText;
}


BOOL CSocketServer::DoAction_By_ClientName(_In_ CONST std::wstring& wsClientName, _In_ std::function<VOID(CRemoteClient *, libTools::CSocketBuffer & )> Ptr)
{
	BOOL bExist = FALSE;
	::EnterCriticalSection(&_LockVecClient);
	auto itr = std::find_if(_VecClient.begin(), _VecClient.end(), [wsClientName](CRemoteClient* pRemoteClient)
	{
		return pRemoteClient->GetClientName() == wsClientName;
	});


	if (itr != _VecClient.end())
	{
		libTools::CSocketBuffer SocketBuffer;
		Ptr(*itr, SocketBuffer);
		PostSend(*itr, &SocketBuffer);
		bExist = TRUE;
	}

	::LeaveCriticalSection(&_LockVecClient);
	return bExist;
}