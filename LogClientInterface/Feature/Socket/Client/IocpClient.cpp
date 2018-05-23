#include "IocpClient.h"
#include <LogLib/Log.h>

#ifdef _DEBUG
#pragma comment(lib,"SocketCommonLib_Debug.lib")
#pragma comment(lib,"SocketClientLib_Debug.lib")
#pragma comment(lib,"ProcessLib_Debug.lib")
#else
#pragma comment(lib,"SocketCommonLib.lib")
#pragma comment(lib,"SocketClientLib.lib")
#pragma comment(lib,"ProcessLib.lib")
#endif // _DEBUG


#define _SELF L"IocpClient.cpp"

CIocpClient& CIocpClient::GetInstance()
{
	static CIocpClient Instance;
	return Instance;
}

BOOL CIocpClient::AsyncSend(_In_ em_Sock_Msg Msg, _In_ std::function<VOID(libTools::CSocketBuffer&)> FillBufferPtr)
{
	libTools::CSocketBuffer SocketBuffer;
	SocketBuffer.InitializeHead(Msg);
	FillBufferPtr(SocketBuffer);
	return PostSend(SocketBuffer);
}

BOOL CIocpClient::AsyncSend(_In_ libTools::CSocketBuffer& SocketBuffer)
{
	return PostSend(SocketBuffer);
}

BOOL CIocpClient::SyncSend(_In_ libTools::CSocketBuffer& SocketBuffer, _In_ std::function<VOID(libTools::CSocketBuffer&)> EchoPtr)
{
	_dwMsgHead = SocketBuffer.GetMsgHead<DWORD>();
	_EchoPtr = EchoPtr;
	_hEvent = ::CreateEventW(NULL, FALSE, FALSE, NULL);
	if (_hEvent == NULL)
	{
		LOG_MSG_CF(L"_hEvent = NULL");
		return FALSE;
	}

	for (;;)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (!AsyncSend(SocketBuffer))
			{
				LOG_CF_E(L"AsyncSend = FALSE");
				return FALSE;
			}


			if (::WaitForSingleObject(_hEvent, 30 * 1000) == WAIT_TIMEOUT)
			{
				LOG_CF_E(L"SyncSend Timeout 30s! Msg=%X", _dwMsgHead);
				continue;
			}

			::CloseHandle(_hEvent);
			_hEvent = INVALID_HANDLE_VALUE;
			EchoPtr = nullptr;
			_dwMsgHead = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

VOID CIocpClient::SetDisConnectPtr(_In_ std::function<VOID(VOID)> DisConnectPtr)
{
	_DisConnectPtr = DisConnectPtr;
}

VOID CIocpClient::EchoPacket(_In_ libTools::CSocketBuffer& SocketBuffer)
{
	em_Sock_Msg emSockMsg;
	if (SocketBuffer.VerDataPtr(emSockMsg) != libTools::CSocketBuffer::em_SocketBuffer_Error_None)
	{
		LOG_C_E(L"Invalid Packet!, emSockMsg=%d", emSockMsg);
		return;
	}


	if (emSockMsg == em_Sock_Msg_Error)
	{
		std::wstring wsErrText;
		SocketBuffer >> wsErrText;
		LOG_MSG_CF(L"·þÎñÆ÷·µ»Ø´íÎó:[%s]", wsErrText.c_str());
		return;
	}


	if (_hEvent == INVALID_HANDLE_VALUE || SocketBuffer.GetMsgHead<DWORD>() != _dwMsgHead)
	{
		return;
	}


	if (_EchoPtr != nullptr)
	{
		_EchoPtr(SocketBuffer);
	}


	::SetEvent(_hEvent);
}

VOID CIocpClient::DisConnectServer()
{
	_DisConnectPtr();
}
