#include "FileExecutor.h"
#include <ProcessLib/Process/Process.h>
#include <FileLib/File.h>
#include <CharacterLib/Character.h>
#include <LogLib/Log.h>

#ifdef _DEBUG
#pragma comment(lib,"ProcessLib_Debug.lib")
#else
#pragma comment(lib,"ProcessLib.lib")
#endif // !_DEBUG


#define _SELF L"FileExecutor.cpp"
CFileExecutor& CFileExecutor::GetInstance()
{
	static CFileExecutor Instance;
	return Instance;
}

BOOL CFileExecutor::RunProc(_In_ CONST std::wstring& wsProcName)
{
	if (!libTools::CProcess::IsExistProcName(wsProcName))
	{
		std::wstring wsPath = libTools::CCharacter::MakeCurrentPath(L"\\" + wsProcName);
		if (!libTools::CFile::FileExist(wsPath))
		{
			LOG_MSG_CF(L"UnExist File:[%s]", wsPath.c_str());
			return FALSE;
		}


		_emProcStatus = libTools::CProcess::CreateProc(wsPath, FALSE) ? em_Proc_Status::Live : em_Proc_Status::Dead;
	}
	return TRUE;
}

void CFileExecutor::Kill(_In_ CONST std::wstring& wsProcName)
{
	_emProcStatus = em_Proc_Status::Dead;
	libTools::CProcess::TerminateProcByProcName(wsProcName);
}
