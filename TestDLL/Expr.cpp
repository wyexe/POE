#include "Expr.h"
#include <set>
#include <queue>
#include <LogLib/Log.h>
#include <ExceptionLib/Exception.h>
#include <CharacterLib/Character.h>
#include <ProcessLib/Memory/SearchBinary.h>
#include <ProcessLib/Memory/Memory.h>
#include <ProcessLib/Memory/SearchBinary.h>
#include <GameStruct.h>
#define _SELF L"Expr.cpp"

#pragma comment(lib,"ProcessLib.lib")
#undef ReadDWORD
#undef ReadBYTE
#define ReadDWORD(x) libTools::CMemory::ReadDWORD(x)
#define ReadBYTE(x)  libTools::CMemory::ReadBYTE(x)

std::function<VOID(CONST std::wstring&)> g_EchoExceptionMsgPtr = [] (CONST std::wstring& wsText)
{
	::MessageBoxW(NULL, wsText.c_str(), L"ExceptionError", NULL);
};
CExpr::CExpr()
{
	
}

CExpr::~CExpr()
{
}

std::vector<libTools::ExpressionFunPtr>& CExpr::GetVec()
{
	static std::vector<libTools::ExpressionFunPtr> Vec = 
	{
		{ std::bind(&CExpr::PrintPlayerAttribute, this, std::placeholders::_1), L"PrintPlayerAttribute" },
		{ std::bind(&CExpr::Help, this, std::placeholders::_1), L"Help" },
		{ std::bind(&CExpr::PrintItem, this, std::placeholders::_1), L"PrintItem" },
		{ std::bind(&CExpr::SwapAlloc, this, std::placeholders::_1), L"SwapAlloc" },
		{ std::bind(&CExpr::PrintWarehouse, this, std::placeholders::_1), L"PrintWarehouse" },
		{ std::bind(&CExpr::PrintAroundObject, this, std::placeholders::_1), L"PrintAroundObject" },
		{ std::bind(&CExpr::ScanBase, this, std::placeholders::_1), L"ScanBase" },
	};
	return Vec;
}

VOID CExpr::Release()
{

}

CExpr& CExpr::GetInstance()
{
	static CExpr Instance;
	return Instance;
}

VOID CExpr::Help(CONST std::vector<std::wstring>&)
{
	auto& Vec = GetVec();
	for (auto& itm : Vec)
	{
		LOG_C_D(L"MethodName=%s", itm.wsFunName.c_str());
	}
}

VOID CExpr::PrintPlayerAttribute(CONST std::vector<std::wstring>&)
{
	libTools::CException::InvokeAction(__FUNCTIONW__, []
	{
		DWORD dwArrayHead = ReadDWORD(人物基址 + 人物基址偏移1);
		DWORD dwObjectPtr = ReadDWORD(dwArrayHead + 1 * 4);
		DWORD dwCount = (ReadDWORD(人物基址 + 人物基址偏移1 + 0x4) - dwArrayHead) >> 2;
		LOG_C_D(L"dwCount=%d", dwCount);

		LOG_C_D(L"dwObjectPtr=%X", dwObjectPtr);
		DWORD dwNode = ReadDWORD(dwObjectPtr + 人物基址偏移2);
		LOG_C_D(L"[dwObjectPtr + %X] = %X", 人物基址偏移2, dwNode);
		if (dwNode == ReadDWORD(dwObjectPtr + 人物基址偏移2 - 4))
		{
			LOG_C_D(L"dwNode == ReadDWORD(dwObjectPtr + 人物基址偏移2 - 4)");
			return;
		}

		dwNode = ReadDWORD(ReadDWORD(ReadDWORD(dwNode - 人物基址偏移3) + 人物基址偏移4) + 人物基址偏移5);
		DWORD dwArrayNode = ReadDWORD(ReadDWORD(dwNode + 0) + 人物基址偏移6) + 人物基址偏移7 + 人物基址偏移8;
		LOG_C_D(L"dwNode=%X,dwArrayNodeAddr=%X, dwArrayNodeAddr=%X", dwNode, dwArrayNode, ReadDWORD(dwArrayNode));


		DWORD dwArrayCount = (ReadDWORD(dwArrayNode + 0x4) - ReadDWORD(dwArrayNode)) / 4;
		LOG_C_D(L"dwArrayCount=%d", dwArrayCount);

		std::set<DWORD> VecArray;
		for (DWORD j = 0; j < dwArrayCount; ++j)
		{
			DWORD dwObject = ReadDWORD(ReadDWORD(dwArrayNode) + j * 4);
			//LOG_C_D(L"dwObject=%X", dwObject);
			if (dwObject == NULL || ReadDWORD(dwObject + 0x8) == NULL)
				continue;

			VecArray.insert(dwObject);
		}

		LOG_C_D(L"VecArray.size=%d", VecArray.size());
		for (auto& itm : VecArray)
		{
			std::string wsName = reinterpret_cast<CONST CHAR*>(ReadDWORD(itm + 0x8));
			LOG_C_D(L"Addr=%X, Name=%s", itm, libTools::CCharacter::ASCIIToUnicode(wsName).c_str());
			if (wsName == "Life")
			{
				DWORD dwObject = ReadDWORD(ReadDWORD(dwNode + 0x4) + 4 * (ReadDWORD(itm + 0xC)));
				LOG_C_D(L"HP=%d,MaxHP=%d,MP=%d,MAXMP=%d,Shield=%d,MaxShiled=%d",
					ReadDWORD(dwObject + 人物HP偏移),
					ReadDWORD(dwObject + 人物MAXHP偏移),
					ReadDWORD(dwObject + 人物MP偏移),
					ReadDWORD(dwObject + 人物MAXMP偏移),
					ReadDWORD(dwObject + 人物护盾偏移),
					ReadDWORD(dwObject + 人物MAX护盾偏移));

				LOG_C_D(L"Player.Name=%s", 人物名字基址 + 人物名字偏移);
			}
			else if (wsName == "Player")
			{
				DWORD dwObject = ReadDWORD(ReadDWORD(dwNode + 0x4) + 4 * (ReadDWORD(itm + 0xC)));
				LOG_C_D(L"Level=%d", ReadDWORD(dwObject + 人物等级偏移));
			}
		}
	});
}

enum
{
	em_ItemObjectIndex_RenderItem = 0x3, // 渲染
	em_ItemObjectIndex_Stack      = 0x2, // 数量
	em_ItemObjectIndex_Base		  = 0x0, // 物品对象
	em_ItemObjectIndex_Usable	  = 0x1, // 是否可以使用
	em_ItemObjectIndex_Charges    = 0x3, // 药剂的充能
};
/*
[物品资源对象+10].Contain 
"Metadata/Items/Helmets" = 头盔
"Metadata/Items/Ring"=戒指,
"Metadata/Items/BodyArmours"=衣服,
"Metadata/Items/Weapons/OneHandWeapon"=单手武器 ,
"Metadata/Items/Weapons/TwoHandWeapon"=双手武器 ,
"Metadata/Items/Gems"=宝石,
"Metadata/Items/Amulets"=护身符,
"Metadata/Items/Shields"=护盾,
"Metadata/Items/Gloves"=手套,
"Metadata/Items/Belts"=腰带,
"Metadata/Items/Boots"=鞋子
"Metadata/Items/Flasks"=药剂
"Metadata/Items/DivinationCards"=命运卡
*/

struct ItemAttributeTableContent
{
	DWORD dwIndex = 0xFF;
	std::string wsIndexName;

	ItemAttributeTableContent() {};
	ItemAttributeTableContent(_In_ DWORD Index, _In_ LPCSTR pszIndexName) : dwIndex(Index), wsIndexName(pszIndexName) {}
};

VOID GetItemAttributeTable(_In_ DWORD dwItemAttributePtr, _Out_ std::vector<ItemAttributeTableContent>& Vec)
{
	DWORD dwItemAttributeTableArray = ReadDWORD(ReadDWORD(dwItemAttributePtr + 0x0) + 人物基址偏移6) + 人物基址偏移7 + 人物基址偏移8;

	std::set<DWORD> VecIndex;
	for (DWORD dwItemObjectAttributeTableNode = ReadDWORD(dwItemAttributeTableArray); dwItemObjectAttributeTableNode < ReadDWORD(dwItemAttributeTableArray + 0x4); dwItemObjectAttributeTableNode += 4)
	{
		DWORD dwItemAttributeTableObject = ReadDWORD(dwItemObjectAttributeTableNode);
		DWORD dwIndex = ReadDWORD(dwItemAttributeTableObject + 0xC);
		if (dwIndex >= 0x10)
			continue;
		else if (ReadDWORD(dwItemAttributeTableObject + 0x8) == 0)
			continue;
		else if(VecIndex.find(dwIndex) != VecIndex.end())
			continue;

		CHAR* pszItemAttributeTableObjectName = reinterpret_cast<CHAR*>(ReadDWORD(dwItemAttributeTableObject + 0x8));
		if (strlen(pszItemAttributeTableObjectName) >= 16)
			continue;


		VecIndex.insert(dwIndex);
		if (strcmp(pszItemAttributeTableObjectName, "Base") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Stack") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Charges") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Mods") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Positioned") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Life") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Player") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Render") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Chest") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "ObjectMagicProperties") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "Actor") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
		else if (strcmp(pszItemAttributeTableObjectName, "WorldItem") == 0x0)
		{
			Vec.emplace_back(dwIndex, pszItemAttributeTableObjectName);
		}
	}
}

VOID PrintItem_By_Object(_In_ DWORD dwArrayHead)
{
	LOG_C_D(L"dwArrayHead=%X", dwArrayHead);
	DWORD dwCount = (ReadDWORD(dwArrayHead + 0x4) - ReadDWORD(dwArrayHead)) / 4;
	dwArrayHead = ReadDWORD(dwArrayHead);

	struct ItemObjectContent
	{
		DWORD dwItemObject;
		DWORD dwTopLeftX;
		DWORD dwTopRightY;
	};

	LOG_C_D(L"dwCount=%d", dwCount);
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
		DWORD dwBottomLeftX = ReadDWORD(dwItemObject + 物品左下角坐标);
		DWORD dwBottomRightY = ReadDWORD(dwItemObject + 物品右下角坐标);
		DWORD dwItemAttributePtr = ReadDWORD(dwItemObject + 物品属性表偏移);

		LOG_C_D(L"dwItemObject=%X,ID=%X, Point=[%d,%d,%d,%d]", dwItemObject, dwItemId, dwTopLeftX, dwTopRightY, dwBottomLeftX, dwBottomRightY);


		std::vector<ItemAttributeTableContent> VecItemAttributeTable;
		GetItemAttributeTable(dwItemAttributePtr, VecItemAttributeTable);
		for (auto& itm : VecItemAttributeTable)
		{
			if (itm.wsIndexName == "Base")
			{
				DWORD dwItemObjectBasePtr = ReadDWORD(ReadDWORD(dwItemAttributePtr + 0x4) + itm.dwIndex * 4);
				DWORD dwNamePtr = ReadDWORD(dwItemObjectBasePtr + 0x8);
				if (dwNamePtr == NULL)
					continue;

				WCHAR* wszItemNamePtr = reinterpret_cast<WCHAR*>(ReadDWORD(dwNamePtr + 0x10 + 0x14) >= 0xF ? ReadDWORD(dwNamePtr + 0x10) : (dwNamePtr + 0x10));
				LOG_C_D(L"ItemName=%s,是否绑定=%d", wszItemNamePtr, ReadDWORD(dwItemObjectBasePtr + 物品绑定偏移) & 0xFF);
			}
			else if (itm.wsIndexName == "Stack")
			{
				DWORD dwItemObjectStackPtr = ReadDWORD(ReadDWORD(dwItemAttributePtr + 0x4) + itm.dwIndex * 4);
				LOG_C_D(L"当前物品数量=%d/%d", ReadDWORD(dwItemObjectStackPtr + 0xC) & 0xFF, ReadDWORD(ReadDWORD(dwItemObjectStackPtr + 0x8) + 0x18) & 0xFF);
			}
			else if (itm.wsIndexName == "Charges")
			{
				DWORD dwItemObjectChargesPtr = ReadDWORD(ReadDWORD(dwItemAttributePtr + 0x4) + itm.dwIndex * 4);
				LOG_C_D(L"当前药剂充能次数=%d, 上限=%d", ReadDWORD(dwItemObjectChargesPtr + 0xC), ReadDWORD(ReadDWORD(dwItemObjectChargesPtr + 0x8) + 0xC));
			}
			else if (itm.wsIndexName == "Quality")
			{
				DWORD dwItemObjectQualityPtr = ReadDWORD(ReadDWORD(dwItemAttributePtr + 0x4) + itm.dwIndex * 4);
				LOG_C_D(L"当前品质=%d", ReadDWORD(dwItemObjectQualityPtr + 0xC) & 0xFF);
			}
			else if (itm.wsIndexName == "Mods")
			{
				DWORD dwItemObjectModsPtr = ReadDWORD(ReadDWORD(dwItemAttributePtr + 0x4) + itm.dwIndex * 4);

				if ((ReadDWORD(dwItemObjectModsPtr + 物品鉴定偏移) & 0xFF) == 0)
				{
					LOG_C_D(L"未鉴定的物品,dwItemObjectModsPtr=%X", dwItemObjectModsPtr);
				}

				switch (ReadBYTE(dwItemObjectModsPtr + 0x18 + 物品颜色偏移))
				{
				case 0:
					LOG_C_D(L"物品颜色=白板");
					break;
				case 1:
					LOG_C_D(L"物品颜色=魔法");
					break;
				case 2:
					LOG_C_D(L"物品颜色=稀有");
					break;
				case 3:
					LOG_C_D(L"物品颜色=传奇");
					break;
				default:
					LOG_C_D(L"未知的物品颜色=%d", ReadBYTE(dwItemObjectModsPtr + 0x18 + 物品颜色偏移));
					break;
				}

				LOG_C_D(L"装备的等级=%d, 需要装备上的等级=%d", ReadDWORD(dwItemObjectModsPtr + 物品需求等级偏移 - 0x4), ReadDWORD(dwItemObjectModsPtr + 物品需求等级偏移));
			}
		}
	}
}

VOID CExpr::PrintItem(CONST std::vector<std::wstring>&)
{
	/*if (Vec.size() == 0)
	{
		LOG_C_D(L"EmptyParam");
		return;
	}

	DWORD dwOffset = std::stoi(Vec.at(0), nullptr, 16);
	LOG_C_D(L"dwOffset=%X", dwOffset);

	using GetArrayLenPtr = DWORD(WINAPI*)();
	struct tagItemObjectVt
	{
		GetArrayLenPtr	GetLenPtr;
	};
	struct tagItemObject
	{
		tagItemObjectVt* pVt;
		DWORD			dwObject;
	};

	DWORD dwArrayHead = ReadDWORD(ReadDWORD(0x156C49C) + 0x100 + 0x4);

	tagItemObject* pNode = reinterpret_cast<tagItemObject *>(dwArrayHead);
	DWORD dwLen = pNode->pVt->GetLenPtr();
	LOG_C_D(L"dwArrayHead=%X, dwLen=%d", dwArrayHead, dwLen);

	for (DWORD dwNode = dwArrayHead + dwLen; ReadDWORD(dwNode) != NULL; dwNode += dwLen)
	{
		DWORD dwObject = reinterpret_cast<tagItemObject *>(dwNode)->dwObject;
		if (ReadDWORD(dwNode) == 0x0121B584 && ReadDWORD(dwObject + 0x82C) < 8)
		{
			if (ReadDWORD(dwObject + 0x8F8) != NULL && ReadDWORD(dwObject + 0x8F4) != NULL/ *人物Object* /)
			{
				//DWORD dwItemResObject = ReadDWORD(ReadDWORD(dwObject + 0x8F8) + 0x0);
				DWORD dwItemAttributeObject = ReadDWORD(ReadDWORD(dwObject + 0x8F8) + 0x4);
				DWORD dwNamePtr = ReadDWORD(ReadDWORD(dwItemAttributeObject + 4 * 0/ *Base* /) + 0x8);
				if (dwNamePtr != NULL && ReadDWORD(dwNamePtr) != NULL && ReadDWORD(dwNamePtr + 0x10) != NULL && ReadDWORD(dwNamePtr + 0x10 + 0x10) < 32)
				{
					std::wstring wsItemName = ReadDWORD(dwNamePtr + 0x10 + 0x14) >= 0xF ? reinterpret_cast<WCHAR*>(ReadDWORD(dwNamePtr + 0x10)) : reinterpret_cast<WCHAR*>(dwNamePtr + 0x10);
					DWORD dwItemCount = wsItemName.length() >= 2 && *wsItemName.rbegin() == L'剂' && (*(wsItemName.rbegin() + 1)) == L'药' ? ReadDWORD(ReadDWORD(dwItemAttributeObject + em_ItemObjectIndex_Charges * 4) + 0xC) : ReadDWORD(ReadDWORD(dwItemAttributeObject + em_ItemObjectIndex_Stack * 4) + 0xC);
					dwItemCount = dwItemCount > 40 ? 0 : dwItemCount;
					LOG_C_D(L"Addr=%X, Name=%s, Count=%d, +%X=%X", dwObject, wsItemName.c_str(), dwItemCount, dwOffset, ReadDWORD(dwObject + dwOffset));
				}
			}
		}


		dwLen = reinterpret_cast<tagItemObject *>(dwNode)->pVt->GetLenPtr();
	}*/

	enum class em_Item_Type
	{
		em_Item_Type_Other,
		em_Item_Type_Currency, // 普通物品
		em_Item_Type_Weapons,  // 武器
		em_Item_Type_Armours,  // 防具
		em_Item_Type_Belts,    // 腰带
		em_Item_Type_Rings,    // 戒指
		em_Item_Type_Amulets,  // 护身符
		em_Item_Type_Boots,	   // 鞋子
		em_Item_Type_Gloves,   // 手套
		em_Item_Type_Shields,  // 盾牌
		em_Item_Type_Gems,     // 技能宝石
		em_Item_Type_Flaks,    // 药剂
		em_Item_Type_DivinationCards, // 命运卡

	};
	/*
	[物品资源对象+10].Contain "/Helmets/" = 头盔,"/Ring/"=戒指,"/BodyArmours/"=衣服,"/Weapons/OneHandWeapon/"=单手武器 ,"/Weapons/TwoHandWeapon/"=双手武器 ,?
	"/Gems/"=宝石,"/Amulets/"=护身符,"/Shields/"=护盾,"/Gloves/"=手套,"/Belts/"=腰带,"/Boots/"=鞋子
	"/Flasks/"=药剂
	*/

	libTools::CException::InvokeAction(__FUNCTIONW__, [] 
	{
		// dd [[[[[[[[[[[[[[[[0x013F24F0+38]+1*4]+14]-8]+1C4]+4AAC+0C]+1*4]+4]-4+4CE8+88]+4]+44]+0*4]+84]+4CE8+88]+0*10+4]+30] = 背包数组
		// dd [[[[[[[[[[[[[[[[0x013F24F0+38]+1*4]+14]-8]+1C4]+4AAC+0C]+1*4]+4]-4+4CE8+88]+4]+44]+0*4]+84]+4CE8+88]+0*10+4]+30] = 背包数组
		DWORD dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3);
		LOG_C_D(L"dwAddr=%X", dwAddr);
		dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 物品遍历偏移1) + 物品遍历偏移2 + 物品遍历偏移3) + 0 * 0x10 + 0x4) + 物品遍历偏移4;
		LOG_C_D(L"dwAddr=%X", dwAddr);
		PrintItem_By_Object(dwAddr);
	});
	
}

using RtlAllocateHeapPtr =
PVOID(WINAPI*)(_In_ PVOID  HeapHandle, _In_opt_ ULONG  Flags, _In_  SIZE_T Size);

RtlAllocateHeapPtr OldRtlAllocateHeapPtr = nullptr;
PVOID WINAPI NewRtlAllocateHeap(_In_ PVOID  HeapHandle, _In_opt_ ULONG  Flags, _In_  SIZE_T Size)
{
	PVOID pAddr = OldRtlAllocateHeapPtr(HeapHandle, Flags, Size);
	if (pAddr != nullptr)
	{
		memset(pAddr, 0, Size);
	}
	return pAddr;
}

VOID CExpr::SwapAlloc(CONST std::vector<std::wstring>&)
{
	DWORD dwAddr = 0x10F719C;
	OldRtlAllocateHeapPtr = (RtlAllocateHeapPtr)ReadDWORD(dwAddr);
	LOG_C_D(L"NewRtlAllocateHeap=%X", NewRtlAllocateHeap);
	//::MessageBoxW(NULL, L"", L"", NULL);
	libTools::CMemory::WriteDWORD(dwAddr, (DWORD)NewRtlAllocateHeap);
}

VOID CExpr::PrintWarehouse(CONST std::vector<std::wstring>&)
{
	libTools::CException::InvokeAction(__FUNCTIONW__, [] 
	{
		DWORD dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3) + 物品遍历偏移1);
		DWORD dwIsShow = ReadDWORD(ReadDWORD(dwAddr + 仓库偏移1 + 0xC) + 仓库偏移2 + 0x4);
		LOG_C_D(L"dwAddr=%X, dwIsShow=%X", dwAddr, dwIsShow);
		/*
			dd [[[[[[0x013F24F0+38]+1*4]+14]-8]+1C4]+894+0C]+0A78+4 = dwValue
			dwValue & 0xFFFF = 0x01?? ? 打开购买窗口
			dwValue & 0xFF = 01 ? 打开仓库 | 打开传送点
		*/
		if (((dwIsShow & 0x0000FF00) >> 0x8) != 0x1)
		{
			LOG_C_D(L"还没打开仓库");
			return;
		}

		DWORD dwWarehouseObject = ReadDWORD(ReadDWORD(dwAddr + 仓库偏移1 + 0xC) + 仓库偏移2 - 0x4);
		if (dwWarehouseObject == NULL)
		{
			LOG_C_D(L"还没打开仓库");
			return;
		}


		DWORD dwPageCount = (ReadDWORD(dwWarehouseObject + 仓库页偏移1 + 0x8) - ReadDWORD(dwWarehouseObject + 仓库页偏移1 + 0x4)) / 0xC;
		LOG_C_D(L"dwPageCount=%d", dwPageCount);


		DWORD dwCurrentPageIndex = ReadDWORD(ReadDWORD(dwWarehouseObject + 仓库页偏移1) + 当前仓库页偏移) & 0xFF;
		LOG_C_D(L"当前页=%d", dwCurrentPageIndex);

		DWORD dwWarehousePageObject = ReadDWORD(ReadDWORD(ReadDWORD(dwWarehouseObject + 仓库页偏移1) + 仓库页偏移2) + dwCurrentPageIndex * 0x20);
		if (ReadDWORD(dwWarehousePageObject + 仓库页索引偏移1) == NULL)
		{
			LOG_C_D(L"仓库页[%d]还没打开!!!", dwCurrentPageIndex);
			return;
		}

		DWORD dwAttributeIndex = ReadDWORD(ReadDWORD(ReadDWORD(dwWarehousePageObject + 仓库页索引偏移1) + 0x0) + 仓库页索引偏移2);
		LOG_C_D(L"dwAttributeIndex=%X", dwAttributeIndex);
		dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3);
		LOG_C_D(L"dwAddr=%X", dwAddr);
		dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 物品遍历偏移1) + 物品遍历偏移2 + 物品遍历偏移3) + (dwAttributeIndex - 0x1) * 0x10 + 0x4) + 物品遍历偏移4;
		LOG_C_D(L"dwAddr=%X", dwAddr);
		PrintItem_By_Object(dwAddr);
	});
}

VOID CExpr::PrintAroundObject(CONST std::vector<std::wstring>&)
{
	libTools::CException::InvokeAction(__FUNCTIONW__, [] 
	{
		DWORD dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3) + 物品遍历偏移1);
		LOG_C_D(L"dwAddr=%X", dwAddr);
		dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 物品遍历偏移2 + 物品遍历偏移3) + 0 * 4) + 0x8 + 周围对象遍历偏移1);
		dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 4 * 4) - 周围对象遍历偏移2) + 周围对象遍历偏移3) + 周围对象遍历偏移4) + 周围对象遍历偏移5 + 0xC) + 0x4/*RootNode*/);
		LOG_C_D(L"Root=%X", dwAddr);

		std::queue<DWORD> VecStack;
		VecStack.push(dwAddr);
		while (!VecStack.empty())
		{
			DWORD dwNode = VecStack.front();
			VecStack.pop();

			DWORD dwLeftNode = ReadDWORD(dwNode + 0x0);
			DWORD dwRightNode = ReadDWORD(dwNode + 0x8);
			if (ReadBYTE(dwLeftNode + 0xD) == 0)
			{
				VecStack.push(dwLeftNode);
			}
			if (ReadBYTE(dwRightNode + 0xD) == 0x0)
			{
				VecStack.push(dwRightNode);
			}

			// BYTE(dwNode + 0xC) == 1 ? 可打开的宝箱
			// dwNode + 0x10 = ID


			DWORD dwNodeAttributePtr = ReadDWORD(dwNode + 0x14);
			// NpcWindowPtr = ReadDWORD(dwNodeAttributePtr + 0x10)
			DWORD dwNodeResPtr = ReadDWORD(dwNodeAttributePtr + 0x0);

			if (ReadDWORD(dwNodeResPtr + 0x10 + 0x10) != 0)
			{
				CONST WCHAR* pwszResName = reinterpret_cast<CONST WCHAR*>(ReadDWORD(dwNodeResPtr + 0x10 + 0x10 + 0x4) > 0x7 ? ReadDWORD(dwNodeResPtr + 0x10) : (dwNodeResPtr + 0x10));
				LOG_C_D(L"pwszResName=%s", pwszResName);
			}


			std::vector<ItemAttributeTableContent> VecItemAttributeTable;
			GetItemAttributeTable(dwNodeAttributePtr, VecItemAttributeTable);
			for (auto& itm : VecItemAttributeTable)
			{
				DWORD dwIndexObject = ReadDWORD(ReadDWORD(dwNodeAttributePtr + 0x4) + itm.dwIndex * 4);
				LOG_C_D(L"dwIndexObject=%X", dwIndexObject);
				if (itm.wsIndexName == "Positioned")
				{
					DWORD dwClientPointX = ReadDWORD(dwIndexObject + 0x10);
					DWORD dwClientPointY = ReadDWORD(dwIndexObject + 0x14);

					std::wstring wsObjectLife;
					DWORD dwLifeValue = ReadDWORD(dwIndexObject + 0x18);
					if (dwLifeValue == 0x7FFFFFFF)
						wsObjectLife = L"死亡";
					else if (dwLifeValue == 0x27)
						wsObjectLife = L"触发类怪物";
					else
						wsObjectLife = L"存活";

					LOG_C_D(L"Point[%d,%d], dwLifeValue=[%08X,%s]", dwClientPointX, dwClientPointY, dwLifeValue, wsObjectLife.c_str());
				}
				else if (itm.wsIndexName == "Life")
				{
					LOG_C_D(L"HP=%d/%d MP=%d/%d", ReadDWORD(dwIndexObject + 0x2C), ReadDWORD(dwIndexObject + 0x30), ReadDWORD(dwIndexObject + 0x50), ReadDWORD(dwIndexObject + 0x54));
				}
				else if (itm.wsIndexName == "Player")
				{
					CONST WCHAR* pwszPlayerName = reinterpret_cast<CONST WCHAR*>(ReadDWORD(dwIndexObject + 0x10 + 0x10 + 0x4) > 0x7 ? ReadDWORD(dwIndexObject + 0x10) : (dwIndexObject + 0x10));
					DWORD dwLevel = ReadDWORD(dwIndexObject + 0x40);
					LOG_C_D(L"pwszPlayerName=%s, Level=%d", pwszPlayerName, dwLevel);
				}
				else if (itm.wsIndexName == "Render")
				{
					if (ReadDWORD(dwIndexObject + 怪物名字偏移 + 0x10) != 0)
					{
						CONST WCHAR* pwszNpcName = reinterpret_cast<CONST WCHAR*>(ReadDWORD(dwIndexObject + 怪物名字偏移 + 0x10 + 0x4) > 0x7 ? ReadDWORD(dwIndexObject + 怪物名字偏移) : (dwIndexObject + 怪物名字偏移));
						LOG_C_D(L"pwszNpcName=%s", pwszNpcName);
					}
				}
				else if (itm.wsIndexName == "Chest")
				{
					LOG_C_D(L"dwNode=%X,AttributeAddr=%X, 箱子打开状态=%d", dwNode, dwNodeAttributePtr, ReadBYTE(dwIndexObject + 0x20));
				}
				/*else if (itm.wsIndexName == "ObjectMagicProperties")
				{
					enum em_MonsterColor
					{
						White = 0x0,
						Blue = 0x1,
						Gold = 0x2,
						DarkGold = 0x3
					};

					em_MonsterColor emColor = (em_MonsterColor)ReadDWORD(dwIndexObject + 0x50);

					
					DWORD dwNameCount = (ReadDWORD(dwIndexObject + 0x14) - ReadDWORD(dwIndexObject + 0x10)) / 0x8;
					if (dwNameCount > 3 || dwNameCount == 0)
					{
						LOG_C_D(L"Invalid dwNameCount=%d", dwNameCount);
						continue;
					}

					std::wstring wsMonsterName;
					for (DWORD i = 0;i < dwNameCount; ++i)
					{
						DWORD dwMonsterNamePtr = ReadDWORD(dwIndexObject + 0x10) + i * 0x8 + 0x4;
						wsMonsterName += reinterpret_cast<WCHAR*>(dwMonsterNamePtr);
						wsMonsterName += L" ";
					}

					LOG_C_D(L"怪物[%s] 颜色=%d", wsMonsterName.c_str(), emColor);
				}*/
				else if (itm.wsIndexName == "Actor")
				{
					LOG_C_D(L"可攻击状态=%d", ReadBYTE(dwIndexObject + 0x80));
				}
				else if (itm.wsIndexName == "WorldItem")
				{
					DWORD dwWorldItemObjectPtr = ReadDWORD(dwIndexObject + 0x14);
					if(dwWorldItemObjectPtr == 0)
						continue;

					LOG_C_D(L"dwWorldItemObjectPtr=%X", dwWorldItemObjectPtr);
					std::vector<ItemAttributeTableContent> VecWorldItemAttributeTable;
					GetItemAttributeTable(dwWorldItemObjectPtr, VecWorldItemAttributeTable);
					for (auto& WorldItem : VecWorldItemAttributeTable)
					{
						DWORD dwWorldItemIndexObject = ReadDWORD(ReadDWORD(dwWorldItemObjectPtr + 0x4) + WorldItem.dwIndex * 4);
						if (WorldItem.wsIndexName == "Base" || WorldItem.wsIndexName == "Render")
						{
							LOG_C_D(L"dwWorldItemIndexObject=%X", dwWorldItemIndexObject);
							DWORD dwNamePtr = ReadDWORD(dwWorldItemIndexObject + 0x8);
							if (ReadDWORD(dwNamePtr + 0x10 + 0x10) == 0)
								continue;

							WCHAR* wszItemNamePtr = reinterpret_cast<WCHAR*>(ReadDWORD(dwNamePtr + 0x10 + 0x14) > 7 ? ReadDWORD(dwNamePtr + 0x10) : (dwNamePtr + 0x10));
							LOG_C_D(L"WorldItemName=%s", wszItemNamePtr);
						}
						else if (WorldItem.wsIndexName == "Mods") // 强制装备类的地上物品或者物品栏都 默认设置Mods = 2?
						{
							switch (ReadBYTE(dwWorldItemIndexObject + 0x18 + 物品颜色偏移))
							{
							case 0:
								LOG_C_D(L"物品颜色=白板");
								break;
							case 1:
								LOG_C_D(L"物品颜色=魔法");
								break;
							case 2:
								LOG_C_D(L"物品颜色=稀有");
								break;
							case 3:
								LOG_C_D(L"物品颜色=传奇");
								break;
							default:
								LOG_C_D(L"未知的物品颜色=%d", ReadBYTE(dwWorldItemIndexObject + 0x18 + 物品颜色偏移));
								break;
							}
						}
					}
				}
			}

		}
	});
}

VOID CExpr::ScanBase(CONST std::vector<std::wstring>&)
{
	DWORD dwBase = NULL;
	libTools::CSearchBinary ScanBinary;


	dwBase = ScanBinary.FindBase("B9????????FF??83??????????00", 0x826C4C - 0x826C4C, 1, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 人物基址 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("E8????????8B??????C6????008B", 0x7BAC08 - 0x7BAC1A, 0x2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 人物基址偏移1 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("83????000F??????????8B??8B????8D", 0x7BC164 - 0x7BC185, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 人物基址偏移2 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("83????000F??????????8B??8B????8D", 0x7BC164 - 0x7BC193, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 人物基址偏移3 0x%X", 0xFF - dwBase + 1);

	dwBase = ScanBinary.FindBase("85C0????8B??????00008B??????0000F3", 0x7DA8A1 - 0x7DA8CB, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 人物基址偏移4 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("85C0????8B??????00008B??????0000F3", 0x7DA8A1 - 0x7DA8D1, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 人物基址偏移5 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("EB0233??83????E8????????8B", 0x677800 - 0x6777D7, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 人物基址偏移6 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("EB0233??83????E8????????8B", 0x677800 - 0x6777E2, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 人物基址偏移7 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("E8????????6A006A006A0033", 0x5DC244 - 0x5DC258, 1, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 人物名字基址 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("83??14E8????????39??24??74??8B????E8", 0x66C1E8 - 0x66C1FE, 3, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 人物等级偏移 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("80????0075??80??????00000075??6A", 0x7E798E - 0x7E797F, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 物品遍历偏移1 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("80????0075??80??????00000075??6A", 0x7E798E - 0x7E79A3, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 物品遍历偏移2 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("C70000000000C7400400000000C208008B", 0x09447BA - 0x944793, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 物品遍历偏移3 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("C7????000000008B????3B??7C", 0x865953 - 0x86594A, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 物品遍历偏移4 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("83??????????000F??????????8B??????????E8????????8B", 0x67BAB8 - 0x67BAD6, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 物品绑定偏移 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("80??????????0075078B??E8????????80????000F", 0x8A1162 - 0x8A1172, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 物品鉴定偏移 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("80??????????0075078B??E8????????80????000F", 0x8A1162 - 0x8A1156, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 物品需求等级偏移 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("81????????????7507C6", 0x83C2C5 - 0x83C2DF, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 物品颜色偏移 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("80??????0000020F??????????8B", 0xA36181 - 0xA36169, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 仓库偏移1 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("8B??????00003B??0F??????????8B??????????83", 0x77FA20 - 0x77FA20, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 仓库偏移2 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("F30F5805????????8B??F3??????????8B????FF??D8", 0x6E0ABD - 0x6E0AA9, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 仓库页偏移1 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("3B??????????0F84????????83??FF", 0xBC18BD - 0xBC18D8, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 仓库页偏移2 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("8B3C078B87????????3B87????????0F84????????8B308D4D??8B86????????8945??8D45", 0x627D26 - 0x627D29, 2, 2, L"PathOfExile.exe");
	LOG_C_D(L"#define 仓库页索引偏移1 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("8B3C078B87????????3B87????????0F84????????8B308D4D??8B86????????8945??8D45", 0x627D26 - 0x627D40, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 仓库页索引偏移2 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("E8????????8B??????000083??FF7408", 0xBC1C42 - 0xBC1C47, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 当前仓库页偏移 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("E8????????83????8D??????????3B??????6A", 0x658849 - 0x65884E, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 怪物名字偏移 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("E8????????83C4??83????FCE9????????8B????33", 0x92717B - 0x9271A0, 2, 0x0, L"PathOfExile.exe", 0xFF);
	LOG_C_D(L"#define 周围对象遍历偏移1 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("8D????C7????????????89????89????????8D", 0x68A9D1 - 0x68A9E3, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 周围对象遍历偏移2 0x%X", static_cast<DWORD>(abs(static_cast<int>(dwBase))));

	dwBase = ScanBinary.FindBase("FF????8B??8D????????8D????????8D", 0x68ACD1 - 0x68ACB5, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 周围对象遍历偏移3 0x%X", dwBase);

	dwBase = ScanBinary.FindBase("FF????8B??8D????????8D????????8D", 0x68ACD1 - 0x68ACBB, 2, 0x0, L"PathOfExile.exe");
	LOG_C_D(L"#define 周围对象遍历偏移4 0x%X", dwBase);
}
