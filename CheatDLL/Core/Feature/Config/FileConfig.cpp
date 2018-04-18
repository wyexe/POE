#include "FileConfig.h"
#include <FileLib/File.h>
#include <LogLib/Log.h>
#include <CharacterLib/Character.h>

#pragma comment(lib,"FileLib.lib")

#define _SELF L"FileConfig.cpp"
CFileConfig& CFileConfig::GetInstance()
{
	static CFileConfig Instance;
	return Instance;
}

BOOL CFileConfig::Initialize()
{
	std::wstring wsPath = L"C:\\LFZLConfig\\Config.ini";
	if (!libTools::CFile::FileExist(wsPath))
	{
		LOG_MSG_CF(L"Config.ini UnExist!");
		return FALSE;
	}

	_wsConfigPath = wsPath;
	if (!ReadFarmConfig())
	{
		LOG_MSG_CF(L"ReadFarmMap = FALSE!");
		return FALSE;
	}

	if (!ReadLoginConfig())
	{
		LOG_MSG_CF(L"ReadPlayerName = FALSE!");
		return FALSE;
	}


	return TRUE;
}

CONST CFileConfig::AccountConfig& CFileConfig::GetAccountConfig() CONST
{
	return _ConfigContent;
}

BOOL CFileConfig::ReadFarmConfig()
{
	std::wstring wsFarmMap;
	if (!ReadTextConfig(L"Farm",L"Map", wsFarmMap))
	{
		return FALSE;
	}

	std::vector<std::wstring> VecText;
	libTools::CCharacter::Split(wsFarmMap, L",", VecText, libTools::CCharacter::em_Split_Option::em_Split_Option_KeepOnly_RemoveEmptyEntries);
	_ConfigContent.FarmInfo.FarmMapInfo.VecFarmMap.clear();
	_ConfigContent.FarmInfo.FarmMapInfo.VecFarmMap = VecText;


	return ReadBoolConfig(L"Farm", L"IsUseDianJinStone", _ConfigContent.FarmInfo.FarmMapInfo.IsUseDianJinStone) &&
		ReadBoolConfig(L"Farm", L"IsUseOpportunityStone", _ConfigContent.FarmInfo.FarmMapInfo.IsUseOpportunityStone) &&
		ReadBoolConfig(L"Farm", L"IsUseTransformationStone", _ConfigContent.FarmInfo.FarmMapInfo.IsUseTransformationStone);
}

BOOL CFileConfig::ReadLoginConfig()
{
	return ReadTextConfig(L"Login", L"PlayerNaMe", _ConfigContent.Login.wsPlayerName);
}

BOOL CFileConfig::ReadTextConfig(_In_ LPCWSTR pwszConfigName, _In_ LPCWSTR pwszKeyName, _Out_ std::wstring& wsText) CONST
{
	WCHAR wszText[1024] = { 0 };
	::GetPrivateProfileStringW(pwszConfigName, pwszKeyName, L"", wszText, _countof(wszText), _wsConfigPath.c_str());
	if (wszText[0] == L'\0')
	{
		LOG_MSG_CF(L"[%s.%s] = NULL", pwszConfigName, pwszKeyName);
		return FALSE;
	}


	wsText = wszText;
	return TRUE;
}

BOOL CFileConfig::ReadBoolConfig(_In_ LPCWSTR pwszConfigName, _In_ LPCWSTR pwszKeyName, _Out_ BOOL& bValue) CONST
{
	WCHAR wszText[1024] = { 0 };
	::GetPrivateProfileStringW(pwszConfigName, pwszKeyName, L"", wszText, _countof(wszText), _wsConfigPath.c_str());
	if (wszText[0] == L'\0')
	{
		LOG_MSG_CF(L"[%s.%s] = NULL", pwszConfigName, pwszKeyName);
		return FALSE;
	}

	bValue = _wtoi(wszText) != 0 ? TRUE : FALSE;
	return TRUE;
}
