#ifndef __LFZL_LOGCLIENTINTERFACE_FEATURE_FILEEXECUTOR_FILEEXECUTOR_H__
#define __LFZL_LOGCLIENTINTERFACE_FEATURE_FILEEXECUTOR_FILEEXECUTOR_H__

#include <Windows.h>
#include <string>

class CFileExecutor
{
private:
	enum class em_Proc_Status
	{
		Live,
		Dead
	};
public:
	CFileExecutor() = default;
	~CFileExecutor() = default;

	static CFileExecutor& GetInstance();

	// 
	BOOL RunProc(_In_ CONST std::wstring& wsProcName);


	// Kill Proc
	void Kill(_In_ CONST std::wstring& wsProcName);
private:
	em_Proc_Status _emProcStatus = em_Proc_Status::Dead;
};


#endif // !__LFZL_LOGCLIENTINTERFACE_FEATURE_FILEEXECUTOR_FILEEXECUTOR_H__
