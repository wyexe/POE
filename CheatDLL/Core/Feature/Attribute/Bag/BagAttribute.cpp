#include "BagAttribute.h"
#include <LogLib/Log.h>
#include <Core/Object/Item.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>
#include <Core/Feature/GameMemory/GameMemory.h>

#define _SELF L"BagAttribute.cpp"
CBagAttribute::CBagAttribute()
{
}

CBagAttribute::~CBagAttribute()
{
}

UINT CBagAttribute::GetVecBagItem(_Out_ std::vector<CItem>& Vec)
{
	// dd [[[[[[[[[[[[[[[[0x013F24F0+38]+1*4]+14]-8]+1C4]+4AAC+0C]+1*4]+4]-4+4CE8+88]+4]+44]+0*4]+84]+4CE8+88]+0*10+4]+30] = 背包数组
	// dd [[[[[[[[[[[[[[[[0x013F24F0+38]+1*4]+14]-8]+1C4]+4AAC+0C]+1*4]+4]-4+4CE8+88]+4]+44]+0*4]+84]+4CE8+88]+0*10+4]+30] = 背包数组
	DWORD dwAddr = CObjectSearcher::GetGameEnv();
	return CObjectSearcher::GetVecItem(ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 物品遍历偏移1) + 物品遍历偏移2 + 物品遍历偏移3) + 0 * 0x10 + 0x4) + 物品遍历偏移4, Vec);
}
