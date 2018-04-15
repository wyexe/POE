#include "BagAttribute.h"
#include <Core/Object/Item.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>
#include <Core/Feature/GameMemory/GameMemory.h>

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
	DWORD dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3) + 物品遍历偏移1);
	dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 物品遍历偏移2 + 物品遍历偏移3) + 1 * 4) + 0x4) - 4 + 物品遍历偏移4 + 物品遍历偏移5) + 0x4) + 物品遍历偏移6);
	dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 0 * 4) + 物品遍历偏移7) + 物品遍历偏移8 + 物品遍历偏移9) + 0 * 0x10 + 4) + 物品遍历偏移10;
	
	return CObjectSearcher::GetVecItem(dwAddr, Vec);
}
