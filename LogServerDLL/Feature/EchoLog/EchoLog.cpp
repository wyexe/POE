#include "EchoLog.h"

CEchoLog::CEchoLog()
{
	::InitializeCriticalSection(&_LockVecLogContent);
}

CEchoLog::~CEchoLog()
{
	::DeleteCriticalSection(&_LockVecLogContent);
}

CEchoLog& CEchoLog::GetInstance()
{
	static CEchoLog Instance;
	return Instance;
}

VOID CEchoLog::Add(_In_ CONST std::wstring& wsClientName, _In_ CONST std::wstring& wsLogText)
{
	::EnterCriticalSection(&_LockVecLogContent);
	_VecLogContent.emplace(wsClientName, wsLogText);
	::LeaveCriticalSection(&_LockVecLogContent);
}

BOOL CEchoLog::Front(_Out_ LogContent& Content)
{
	BOOL bExist = FALSE;


	::EnterCriticalSection(&_LockVecLogContent);
	if (!_VecLogContent.empty())
	{
		bExist = TRUE;
		Content = _VecLogContent.front();
		_VecLogContent.pop();
	}

	::LeaveCriticalSection(&_LockVecLogContent);
	return bExist;
}
