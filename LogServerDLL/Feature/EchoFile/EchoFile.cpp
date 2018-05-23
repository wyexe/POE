#include "EchoFile.h"
#include <CharacterLib/Character.h>
#include <FileLib/File.h>
#include <AlgroithmLib/Encrypt/CRC32.h>



BOOL CEchoFile::ReadFileContent(_In_ CONST std::wstring& wsFileName, _Out_ libTools::CSocketBuffer& SocketBuffer)
{
	std::wstring wsPath = libTools::CCharacter::MakeCurrentPath(L"\\File\\" + wsFileName);
	if (!libTools::CFile::FileExist(wsPath))
	{
		return FALSE;
	}


	LPVOID	pvFileContent = nullptr;
	SIZE_T	uFileSize = 0;
	if (!libTools::CFile::ReadFileContent(wsPath, pvFileContent, uFileSize))
	{
		return FALSE;
	}


	SocketBuffer << uFileSize << libTools::CCRC32::GetCRC32(reinterpret_cast<LPCSTR>(pvFileContent), uFileSize);
	SocketBuffer.SetDataPtr(reinterpret_cast<CONST CHAR*>(pvFileContent), uFileSize);
	return TRUE;
}
