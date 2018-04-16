#include "WarehouseAttribute.h"
#include <Core/Object/Item.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <LogLib/Log.h>

#define _SELF L"WarehouseAttribute.cpp"
BOOL CWarehouseAttribute::IsOpenedWarehouse()
{
	DWORD dwNodeBase = GetWarehouseNodeBase();
	if (((ReadDWORD(ReadDWORD(dwNodeBase + 仓库偏移1 + 0xC) + 仓库偏移2 + 0x4) & 0x0000FF00) >> 0x8) != 0x1)
	{
		return FALSE;
	}


	return GetWarehouseObject() != NULL;
}

DWORD CWarehouseAttribute::GetWarehousePageCount()
{
	DWORD dwWarehouseObject = GetWarehouseObject();
	return (ReadDWORD(dwWarehouseObject + 仓库页偏移1 + 0x8) - ReadDWORD(dwWarehouseObject + 仓库页偏移1 + 0x4)) / 0xC;
}

DWORD CWarehouseAttribute::GetCurrentPageIndex()
{
	return ReadDWORD(ReadDWORD(GetWarehouseObject() + 仓库页偏移1) + 当前仓库页偏移) & 0xFF;
}

DWORD CWarehouseAttribute::GetCurrentPageObject()
{
	return ReadDWORD(ReadDWORD(ReadDWORD(GetWarehouseObject() + 仓库页偏移1) + 仓库页偏移2) + GetCurrentPageIndex() * 0x20);
}

UINT CWarehouseAttribute::GetCurrentPageItem(_Out_ std::vector<CItem>& Vec)
{
	DWORD dwWarehousePageObject = GetWarehouseObject();
	if (ReadDWORD(dwWarehousePageObject + 仓库页索引偏移1) == NULL)
	{
		LOG_C_E(L"ReadDWORD(dwWarehousePageObject + 仓库页索引偏移1) = NULL");
		return 0;
	}

	DWORD dwAttributeIndex = ReadDWORD(ReadDWORD(ReadDWORD(GetCurrentPageObject() + 仓库页索引偏移1) + 0x0) + 仓库页索引偏移2);


	DWORD dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3);
	dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 物品遍历偏移1) + 物品遍历偏移2 + 物品遍历偏移3) + (dwAttributeIndex - 0x1) * 0x10 + 0x4) + 物品遍历偏移4;
	return CObjectSearcher::GetVecItem(dwAddr, Vec);
}

DWORD CWarehouseAttribute::GetWarehouseNodeBase()
{
	return ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3) + 物品遍历偏移1);
}

DWORD CWarehouseAttribute::GetWarehouseObject()
{
	return ReadDWORD(ReadDWORD(GetWarehouseNodeBase() + 仓库偏移1 + 0xC) + 仓库偏移2 - 0x4);
}
