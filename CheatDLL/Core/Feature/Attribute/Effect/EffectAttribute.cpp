#include "EffectAttribute.h"
#include <LogLib/Log.h>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>

#define _SELF L"EffectAttribute.cpp"
DWORD CEffectAttribute::EffectIconObject::GetCount() CONST
{
	DWORD dwHead = dwObject + EffectID数组偏移;
	DWORD dwCount = (ReadDWORD(dwHead + 0x4) - ReadDWORD(dwHead)) / 4;
	if (dwCount >= 10)
	{
		LOG_C_E(L"CEffectAttribute::EffectIconObject::GetCount=[%d]", dwCount);
		return 0;
	}
	return dwCount;
}

UINT CEffectAttribute::GetVecEffect(_Out_ std::vector<EffectIconObject>& Vec)
{
	DWORD dwEffectUiObject =  ReadDWORD(ReadDWORD(CObjectSearcher::GetGameEnv() + 人物UI偏移) + EffectUI偏移);
	DWORD dwArrayHead = dwEffectUiObject + Effect数组偏移 + 0x4;


	DWORD dwCount = (ReadDWORD(dwArrayHead + 0x4) - ReadDWORD(dwArrayHead)) / 0xC;
	if (dwCount >= 10)
	{
		LOG_C_E(L"Effect.Count = [%d]", dwCount);
		return 0;
	}


	for (DWORD i = 0;i < dwCount; ++i)
	{
		DWORD dwEffectObjectAddr = ReadDWORD(dwArrayHead) + i * 0xC;


		EffectIconObject tmpInstance;
		tmpInstance.dwObject = ReadDWORD(dwEffectObjectAddr + 0x4);
		tmpInstance.dwId = ReadDWORD(dwEffectObjectAddr + 0x8);
		tmpInstance.Index = ReadDWORD(dwEffectObjectAddr + 0x0);
		Vec.push_back(std::move(tmpInstance));
	}
	return Vec.size();
}
