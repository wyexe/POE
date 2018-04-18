#include "WarehouseAttribute.h"
#include <Core/Object/Item.h>
#include <Core/Feature/Searcher/ObjectSearcher.h>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <LogLib/Log.h>

#define _SELF L"WarehouseAttribute.cpp"
BOOL CWarehouseAttribute::IsOpenedWarehouse()
{
	DWORD dwNodeBase = GetWarehouseNodeBase();
	if (((ReadDWORD(ReadDWORD(dwNodeBase + ²Ö¿âÆ«ÒÆ1 + 0xC) + ²Ö¿âÆ«ÒÆ2 + 0x4) & 0x0000FF00) >> 0x8) != 0x1)
	{
		return FALSE;
	}


	return GetWarehouseObject() != NULL;
}

DWORD CWarehouseAttribute::GetWarehousePageCount()
{
	DWORD dwWarehouseObject = GetWarehouseObject();
	return (ReadDWORD(dwWarehouseObject + ²Ö¿âÒ³Æ«ÒÆ1 + 0x8) - ReadDWORD(dwWarehouseObject + ²Ö¿âÒ³Æ«ÒÆ1 + 0x4)) / 0xC;
}

DWORD CWarehouseAttribute::GetCurrentPageIndex()
{
	return ReadDWORD(ReadDWORD(GetWarehouseObject() + ²Ö¿âÒ³Æ«ÒÆ1) + µ±Ç°²Ö¿âÒ³Æ«ÒÆ) & 0xFF;
}

DWORD CWarehouseAttribute::GetCurrentPageObject()
{
	return ReadDWORD(ReadDWORD(ReadDWORD(GetWarehouseObject() + ²Ö¿âÒ³Æ«ÒÆ1) + ²Ö¿âÒ³Æ«ÒÆ2) + GetCurrentPageIndex() * 0x20);
}

UINT CWarehouseAttribute::GetCurrentPageItem(_Out_ std::vector<CItem>& Vec)
{
	DWORD dwWarehousePageObject = GetWarehouseObject();
	if (ReadDWORD(dwWarehousePageObject + ²Ö¿âÒ³Ë÷ÒıÆ«ÒÆ1) == NULL)
	{
		LOG_C_E(L"ReadDWORD(dwWarehousePageObject + ²Ö¿âÒ³Ë÷ÒıÆ«ÒÆ1) = NULL");
		return 0;
	}

	DWORD dwAttributeIndex = ReadDWORD(ReadDWORD(ReadDWORD(GetCurrentPageObject() + ²Ö¿âÒ³Ë÷ÒıÆ«ÒÆ1) + 0x0) + ²Ö¿âÒ³Ë÷ÒıÆ«ÒÆ2);
	return CObjectSearcher::GetVecItem(ReadDWORD(ReadDWORD(GetWarehouseNodeBase() + ÎïÆ·±éÀúÆ«ÒÆ2 + ÎïÆ·±éÀúÆ«ÒÆ3) + (dwAttributeIndex - 0x1) * 0x10 + 0x4) + ÎïÆ·±éÀúÆ«ÒÆ4, Vec);
}


DWORD CWarehouseAttribute::GetCurrentWarehousePageMaxItemCount()
{
	return 12 * 12;
}

DWORD CWarehouseAttribute::GetWarehouseNodeBase()
{
	return ReadDWORD(CObjectSearcher::GetGameEnv() + ÎïÆ·±éÀúÆ«ÒÆ1);
}

DWORD CWarehouseAttribute::GetWarehouseObject()
{
	return ReadDWORD(ReadDWORD(GetWarehouseNodeBase() + ²Ö¿âÆ«ÒÆ1 + 0xC) + ²Ö¿âÆ«ÒÆ2 - 0x4);
}
