#include "ObjectSearcher.h"
#include <set>
#include <Core/Object/AttributeObject.h>

CObjectSearcher::CObjectSearcher()
{
}

CObjectSearcher::~CObjectSearcher()
{
}

std::wstring CObjectSearcher::GetCurrentStateText()
{
	DWORD dwGameEnv = CObjectSearcher::GetGameEnv();
	return dwGameEnv == 0 ? L"" : CGameMemory::GetInstance().ReadProcTextWithLength(dwGameEnv + 0x8);
}

DWORD CObjectSearcher::GetGameEnv()
{
	return ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 1 * 人物基址偏移3);
}


DWORD CObjectSearcher::GetUiEnv()
{
	return ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 2 * 人物基址偏移3);
}

UINT CObjectSearcher::GetVecItem(_In_ DWORD dwAddr, _Out_ std::vector<CItem>& Vec)
{
	DWORD dwCount = (ReadDWORD(dwAddr + 0x4) - ReadDWORD(dwAddr)) / 4;
	DWORD dwArrayHead = ReadDWORD(dwAddr);


	struct ItemObjectContent
	{
		DWORD dwItemObject;
		DWORD dwTopLeftX;
		DWORD dwTopRightY;
	};

	std::set<DWORD> VecItemObject;
	for (DWORD i = 0; i < dwCount; ++i)
	{
		DWORD dwItemObject = ReadDWORD(dwArrayHead + i * 4);
		if (dwItemObject == NULL)
			continue;

		DWORD dwItemId = ReadDWORD(dwItemObject + 物品ID偏移);
		if (dwItemId == NULL)
			continue;

		DWORD dwTopLeftX = ReadDWORD(dwItemObject + 物品左上角坐标);
		DWORD dwTopRightY = ReadDWORD(dwItemObject + 物品右上角坐标);
		DWORD dwRepeatFlag = (dwTopLeftX << 0x8) | (dwTopRightY << 0xF);
		if (VecItemObject.find(dwRepeatFlag) != VecItemObject.end())
			continue;


		VecItemObject.insert(dwRepeatFlag);
		Vec.emplace_back(dwItemObject);
	}
	return Vec.size();
}

UINT CObjectSearcher::GetVecChest(_Out_ std::vector<CChest>& Vec)
{
	return GetVecObject<CChest>(Vec, [](DWORD dwNodeBase)
	{
		return CAttributeObject::GetObjectType(ReadDWORD(dwNodeBase)) == em_Object_Type::Chests;
	});
}

UINT CObjectSearcher::GetVecNpc(_Out_ std::vector<CNpc>& Vec)
{
	return GetVecObject<CNpc>(Vec, [](DWORD dwNodeBase)
	{
		return CAttributeObject::GetObjectType(ReadDWORD(dwNodeBase)) == em_Object_Type::Npc;
	});
}

UINT CObjectSearcher::GetVecMonster(_Out_ std::vector<CMonster>& Vec)
{
	return GetVecObject<CMonster>(Vec, [](DWORD dwNodeBase)
	{
		return CAttributeObject::GetObjectType(ReadDWORD(dwNodeBase)) == em_Object_Type::Monster;
	});
}

UINT CObjectSearcher::GetVecPlayer(_Out_ std::vector<CPlayer>& Vec)
{
	return GetVecObject<CPlayer>(Vec, [](DWORD dwNodeBase)
	{
		return CAttributeObject::GetObjectType(ReadDWORD(dwNodeBase)) == em_Object_Type::Player;
	});
}

UINT CObjectSearcher::GetVecWorlditem(_Out_ std::vector<CWorldItem>& Vec)
{
	return GetVecObject<CWorldItem>(Vec, [](DWORD dwNodeBase)
	{
		return CAttributeObject::GetObjectType(ReadDWORD(dwNodeBase)) == em_Object_Type::WorldItem;
	});
}
