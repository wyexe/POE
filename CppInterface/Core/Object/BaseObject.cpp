#include "BaseObject.h"
#include "AttributeObject.h"
#include <vector>

DWORD CBaseObject::GetNodeBase() CONST
{
	return _dwNodeBase;
}

VOID CBaseObject::SetNodeBase(_In_ DWORD dwNodeBase)
{
	_dwNodeBase = dwNodeBase;
	if (_dwNodeBase != NULL)
	{
		CAttributeObject::FillObjectAttribute_ResName(this);
	}
}

CONST std::wstring& CBaseObject::GetName() CONST
{
	return _wsName;
}

VOID CBaseObject::SetName(_In_ LPCWSTR pwszName)
{
	_wsName = pwszName;
}

CONST std::wstring& CBaseObject::GetResName() CONST
{
	return _wsResName;
}

VOID CBaseObject::SetResName(_In_ LPCWSTR pwszResName)
{
	_wsResName = pwszResName;
}

Point CBaseObject::GetPoint() CONST
{
	return _Pos;
}

VOID CBaseObject::SetPoint(_In_ DWORD dwX, _In_ DWORD dwY)
{
	_Pos.X = dwX;
	_Pos.Y = dwY;
}

em_Object_Type CBaseObject::GetType()
{
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


	if (_emObjectType != em_Object_Type::Other)
	{
		return _emObjectType;
	}


	for (CONST auto& itm : Vec)
	{
		if (_wsResName.find(itm.wsText) != std::wstring::npos)
		{
			return itm.emObjectType;
		}
	}

	return em_Object_Type::Other;
}
