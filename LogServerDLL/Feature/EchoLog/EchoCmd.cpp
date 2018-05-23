#include "EchoCmd.h"
#include <algorithm>

CEchoCmd& CEchoCmd::GetInstance()
{
	static CEchoCmd Instance;
	return Instance;
}

VOID CEchoCmd::Add(_In_ CONST std::wstring& wsClientName, _In_ CONST std::wstring& wsCmdText)
{
	DoActionInLock([=] 
	{
		_VecCmdContent.emplace_back(wsClientName, wsCmdText);
	});
}

BOOL CEchoCmd::Find(_In_ CONST std::wstring& wsClientName, _Out_ CmdContent& Content)
{
	return DoActionReturnInLock<BOOL>([&]
	{
		auto itr = std::find_if(_VecCmdContent.begin(), _VecCmdContent.end(), [wsClientName](_In_ CONST CmdContent& itm)
		{
			return itm.wsClientName == wsClientName;
		});


		if (itr != _VecCmdContent.end())
		{
			Content = *itr;
			_VecCmdContent.erase(itr);
			return TRUE;
		}

		return FALSE;
	});
}
