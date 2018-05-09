#ifndef __LFZL_LOGSERVERDLL_FEATURE_ECHOLOG_ECHOLOG_H__
#define __LFZL_LOGSERVERDLL_FEATURE_ECHOLOG_ECHOLOG_H__

#include <Windows.h>
#include <string>
#include <queue>

class CEchoLog
{
public:
	struct LogContent
	{
		std::wstring wsClientName;
		std::wstring wsLogText;
		SYSTEMTIME   Tick;

		LogContent() = default;
		LogContent(_In_ CONST std::wstring& wsText1, _In_ CONST std::wstring& wsText2)
		{
			wsClientName = wsText1;
			wsLogText = wsText2;
			::GetLocalTime(&Tick);
		}
	};
public:
	CEchoLog();
	~CEchoLog();

	static CEchoLog&	GetInstance();
public:
	VOID				Add(_In_ CONST std::wstring& wsClientName, _In_ CONST std::wstring& wsLogText);

	BOOL				Front(_Out_ LogContent& Content);
private:
	CRITICAL_SECTION       _LockVecLogContent;
	std::queue<LogContent> _VecLogContent;
};



#endif // !__LFZL_LOGSERVERDLL_FEATURE_ECHOLOG_ECHOLOG_H__
