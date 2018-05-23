#include "Watcher.h"
#include <Feature/Socket/Client/IocpClient.h>
#include <LogLib/Log.h>
#include <CharacterLib/Character.h>
#include <Feature/FileExecutor/FileExecutor.h>

#define _SELF L"Watcher.cpp"
CCmdWatcher::~CCmdWatcher()
{
	Release();
}

CCmdWatcher CCmdWatcher::GetInstance()
{
	static CCmdWatcher Instance;
	return Instance;
}

BOOL CCmdWatcher::Run()
{
	if (!CIocpClient::GetInstance().Run(L"192.168.0.104", LFZL_LOG_SOCKET_PORT, 10 * 1000))
	{
		return FALSE;
	}


	_IsRun = TRUE;
	_hThread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)_WatchThread, this, NULL, NULL);
	return TRUE;
}

VOID CCmdWatcher::Stop()
{
	Release();
}

VOID CCmdWatcher::InitializeClientToServer(_In_ CONST std::wstring& wsClientName)
{
	CIocpClient::GetInstance().AsyncSend(em_Sock_Msg_Initialize, [wsClientName](libTools::CSocketBuffer& SocketBuffer)
	{
		SocketBuffer << wsClientName;
	});
}

VOID CCmdWatcher::Release()
{
	_IsRun = FALSE;
	if (_hThread != NULL)
	{
		::WaitForSingleObject(_hThread, INFINITE);
		::CloseHandle(_hThread);
		_hThread = NULL;
	}
}

BOOL CCmdWatcher::SendKeepALive()
{
	return CIocpClient::GetInstance().AsyncSend(em_Sock_Msg_IsExistCmd, [&](libTools::CSocketBuffer& SocketBuffer)
	{
		BOOL bExist = FALSE;
		SocketBuffer >> reinterpret_cast<DWORD&>(bExist);
		if (bExist)
		{
			std::wstring wsCmd;
			SocketBuffer >> wsCmd;
			this->DoActionInLock([&] { _VecCmd.push(wsCmd); });
		}
	});
}

VOID CCmdWatcher::CheckExcuteCmd()
{
	if (!_VecCmd.empty())
		return;


	std::wstring wsText;
	DoActionInLock([this, &wsText] 
	{
		wsText = _VecCmd.front();
		_VecCmd.pop(); 
	});


	ExcuteCmd(libTools::CCharacter::MakeTextToLower(wsText));
}

VOID CCmdWatcher::ExcuteCmd(_In_ CONST std::wstring& wsCmd)
{
	if (wsCmd == L"runcheatproc")
	{
		// 创建测试进程
		CFileExecutor::GetInstance().RunProc(L"LoadDLL.exe");
	}
	else if (wsCmd == L"kill")
	{
		// 关闭作弊进程
		CFileExecutor::GetInstance().Kill(L"LoadDLL.exe");
	}
	else
	{
		LOG_MSG_CF(L"Invalid Command: [%s]", wsCmd.c_str());
	}
}

DWORD WINAPI CCmdWatcher::_WatchThread(LPVOID lpParam)
{
	CCmdWatcher* pWatcher = reinterpret_cast<CCmdWatcher *>(lpParam);
	while (pWatcher->_IsRun)
	{
		if (!pWatcher->SendKeepALive())
		{
			LOG_MSG_CF(L"发送心跳失败!");
			break;
		}

		pWatcher->CheckExcuteCmd();
		::Sleep(1000);
	}
	return 0;
}
