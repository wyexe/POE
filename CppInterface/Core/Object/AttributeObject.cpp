#include "AttributeObject.h"
#include <set>
#include <CharacterLib/Character.h>
#pragma comment(lib,"CharacterLib.lib")

BOOL CAttributeObject::FillAttributeTable(_In_ DWORD dwAttributeNodeBase, _In_ LPCSTR pwszAttributeName, _In_ std::function<VOID(DWORD)> Ptr)
{
	DWORD dwItemAttributeTableArray = ReadDWORD(ReadDWORD(dwAttributeNodeBase + 0x0) + 人物基址偏移6) + 人物基址偏移7 + 人物基址偏移8;

	for (DWORD dwItemObjectAttributeTableNode = ReadDWORD(dwItemAttributeTableArray); dwItemObjectAttributeTableNode < ReadDWORD(dwItemAttributeTableArray + 0x4); dwItemObjectAttributeTableNode += 4)
	{
		DWORD dwItemAttributeTableObject = ReadDWORD(dwItemObjectAttributeTableNode);
		DWORD dwIndex = ReadDWORD(dwItemAttributeTableObject + 0xC);
		if (dwIndex >= 0x10)
			continue;
		else if (ReadDWORD(dwItemAttributeTableObject + 0x8) == 0)
			continue;


		CHAR* pszItemAttributeTableObjectName = reinterpret_cast<CHAR*>(ReadDWORD(dwItemAttributeTableObject + 0x8));
		if (strlen(pszItemAttributeTableObjectName) >= 16)
			continue;


		if (strcmp(pwszAttributeName, pszItemAttributeTableObjectName) == 0x0)
		{
			Ptr(dwIndex);
			return TRUE;
		}
	}

	return FALSE;
}
