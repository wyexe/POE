#include "BuffAttribute.h"
#include <Core/Object/Person.h>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <LogLib/Log.h>
#include <map>

#define _SELF L"BuffAttribute.cpp"
UINT CBuffAttribute::GetVecBuff(_Out_ std::vector<BuffObject>& Vec)
{
	return GetVecBuff(Vec, [](CONST std::wstring&) { return TRUE; });
}

UINT CBuffAttribute::GetVecBuff(_Out_ std::vector<BuffObject>& Vec, _In_ std::function<BOOL(CONST std::wstring&)> FilterPtr)
{
	DWORD dwLifeAddr = CPerson::GetInstance().GetLifeAttributeAddr();
	DWORD dwCount = (ReadDWORD(dwLifeAddr + Buff±éÀúÆ«ÒÆ + 0x4) - ReadDWORD(dwLifeAddr + Buff±éÀúÆ«ÒÆ)) / 4;
	if (dwCount >= 100)
	{
		LOG_C_E(L"dwCount=%d", dwCount);
		return 0;
	}


	for (DWORD i = 0; i < dwCount; ++i)
	{
		DWORD dwBuffObject = ReadDWORD(ReadDWORD(dwLifeAddr + Buff±éÀúÆ«ÒÆ) + i * 4);
		if (dwBuffObject == NULL)
			continue;


		DWORD dwBuffAttributeAddr = ReadDWORD(ReadDWORD(dwBuffObject + 0x4) + 0x4);

		BuffObject tmpInstance;
		if (ReadBYTE(ReadDWORD(dwBuffAttributeAddr + 0x0) + 0x0) != NULL)
			tmpInstance.wsBuffName = CGameMemory::GetInstance().ReadProcTextWithoutLength(ReadDWORD(dwBuffAttributeAddr + 0x0));
		if (ReadBYTE(ReadDWORD(dwBuffAttributeAddr + 0x4) + 0x0) != NULL)
			tmpInstance.wsBuffText = CGameMemory::GetInstance().ReadProcTextWithoutLength(ReadDWORD(dwBuffAttributeAddr + 0x4));


		if (FilterPtr(tmpInstance.wsBuffName))
		{
			Vec.push_back(std::move(tmpInstance));
		}
	}
	return Vec.size();
}

BOOL CBuffAttribute::IsExistBuff(_In_ em_Buff_Type emBuffType)
{
	struct BuffTypeContent
	{
		em_Buff_Type emType;
		std::wstring wsName;
	};


	CONST static std::map<em_Buff_Type, std::wstring> VecBuffType = 
	{
		{ em_Buff_Type::ManaAura, L"player_aura_mana_regen" },
	};


	auto itr = VecBuffType.find(emBuffType);
	if (itr == VecBuffType.end())
	{
		LOG_MSG_CF(L"UnExist emBuffType[%d]!", emBuffType);
		return FALSE;
	}


	std::vector<BuffObject> Vec;
	return GetVecBuff(Vec, [itr](CONST std::wstring& wsBuffName) { return itr->second == wsBuffName; }) != 0;
}
