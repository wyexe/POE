#ifndef __LFZL_LOGSERVER_FEATURE_ECHOLOG_ECHOCMD_H__
#define __LFZL_LOGSERVER_FEATURE_ECHOLOG_ECHOCMD_H__

#include <Windows.h>
#include <string>
#include <vector>
#include <ProcessLib/Lock/Lock.h>

class CEchoCmd : public libTools::CThreadLock
{
public:
	struct CmdContent
	{
		std::wstring wsClientName;
		std::wstring wsLogText;

		CmdContent() = default;
		CmdContent(_In_ CONST std::wstring& wsText1, _In_ CONST std::wstring& wsText2)
		{
			wsClientName = wsText1;
			wsLogText = wsText2;
		}
	};
public:
	CEchoCmd() = default;
	~CEchoCmd() = default;

	static CEchoCmd&	GetInstance();
public:
	VOID				Add(_In_ CONST std::wstring& wsClientName, _In_ CONST std::wstring& wsCmdText);

	BOOL				Find(_In_ CONST std::wstring& wsClientName, _Out_ CmdContent& Content);
private:
	std::vector<CmdContent> _VecCmdContent;
};

#endif // !__LFZL_LOGSERVER_FEATURE_ECHOLOG_ECHOCMD_H__
