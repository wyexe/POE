#include "AttributeObject.h"
#include <set>
#include <algorithm>
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

em_Object_Type CAttributeObject::GetObjectType(_In_ DWORD dwNodeBase)
{
	DWORD dwNodeResPtr = ReadDWORD(dwNodeBase + 0x0);
	if (ReadDWORD(dwNodeResPtr + 0x10 + 0x10) == 0)
	{
		return em_Object_Type::Other;
	}


	struct ObjectTypeContent
	{
		em_Object_Type emObjectType;
		std::wstring   wsText;
	};


	CONST static std::vector<ObjectTypeContent> Vec =
	{
		{ em_Object_Type::Helmets , L"Metadata/Items/Armours/Helmets" },
		{ em_Object_Type::Ring , L"Metadata/Items/Rings" },
		{ em_Object_Type::BodyArmours , L"Metadata/Items/Armours/BodyArmours" },
		{ em_Object_Type::Weapons , L"Metadata/Items/Weapons" },
		{ em_Object_Type::Gems , L"Metadata/Items/Gems" },
		{ em_Object_Type::Amulets , L"Metadata/Items/Amulets" },
		{ em_Object_Type::Shields , L"Metadata/Items/Armours/Shields" },
		{ em_Object_Type::Gloves , L"Metadata/Items/Armours/Gloves" },
		{ em_Object_Type::Belts , L"Metadata/Items/Belts" },
		{ em_Object_Type::Boots , L"Metadata/Items/Armours/Boots" },
		{ em_Object_Type::Flasks , L"Metadata/Items/Flasks" },
		{ em_Object_Type::DivinationCards , L"Metadata/Items/DivinationCards" },
		{ em_Object_Type::Currency , L"Metadata/Items/Currency" },
		{ em_Object_Type::Player , L"Metadata/Characters" },
		{ em_Object_Type::Npc , L"Metadata/NPC" },
		{ em_Object_Type::QuestObjects , L"Metadata/QuestObjects" },
		{ em_Object_Type::Monster , L"Metadata/Monsters" },
		{ em_Object_Type::WorldItem , L"MiscellaneousObjects/WorldItem" },
		{ em_Object_Type::Chests , L"Metadata/Chests" },
		{ em_Object_Type::Waypoint , L"MiscellaneousObjects/Waypoint" },
		{ em_Object_Type::AreaTransition , L"MiscellaneousObjects/AreaTransition" },
		{ em_Object_Type::MiscellaneousObjects , L"Metadata/MiscellaneousObjects" },
	};

	CONST WCHAR* pwszResName = reinterpret_cast<CONST WCHAR*>(ReadDWORD(dwNodeResPtr + 0x10 + 0x10 + 0x4) > 0x7 ? ReadDWORD(dwNodeResPtr + 0x10) : (dwNodeResPtr + 0x10));

	auto itr = std::find_if(Vec.begin(), Vec.end(), [pwszResName](CONST ObjectTypeContent& itm) { return wcsstr(pwszResName, itm.wsText.c_str()) != nullptr; });
	return itr != Vec.end() ? itr->emObjectType : em_Object_Type::Other;
}