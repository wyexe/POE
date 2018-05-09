#ifndef __LFZL_LOGSERVERDLL_FEATURE_ECHOFILE_ECHOFILE_H__
#define __LFZL_LOGSERVERDLL_FEATURE_ECHOFILE_ECHOFILE_H__

#include <Windows.h>
#include <string>
#include <SocketCommon/SocketBuffer.h>

class CEchoFile
{
public:
	CEchoFile() = default;
	~CEchoFile() = default;

	static BOOL ReadFileContent(_In_ CONST std::wstring& wsFileName, _Out_ libTools::CSocketBuffer& SocketBuffer);
private:

};


#endif // !__LFZL_LOGSERVERDLL_FEATURE_ECHOFILE_ECHOFILE_H__
