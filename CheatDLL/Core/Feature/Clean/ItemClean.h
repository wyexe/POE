#ifndef __LFZL_CHEATDLL_CORE_FEATURE_CLEAN_ITEMCLEAN_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_CLEAN_ITEMCLEAN_H__

#include <GameStruct.h>
#include <Core/Object/Item.h>
#include <vector>

#define WAREHOUSE_MAX_ITEMPAGE_COUNT 3

class CItemClean
{
public:
	// 占一个格子的通货 或者 地图 命运卡之类的
	struct ItemCleanContent
	{
		std::wstring		wsItemName;
		em_Object_Type		emObjectType;
		Point				Loc;
		DWORD				dwCount;
		DWORD				dwMaxCount;

		ItemCleanContent(_In_ CONST std::wstring& ItemName, _In_ em_Object_Type emType, _In_ CONST Point& Pos, _In_ DWORD Count, _In_ DWORD MaxCount)
		{
			wsItemName = ItemName;
			emObjectType = emType;
			Loc = Pos;
			dwCount = Count;
			dwMaxCount = MaxCount;
		}
	};

	// 单个仓库页(物品)
	struct WarehousePageItemContent
	{
		std::vector<ItemCleanContent>	Vec;
		DWORD							dwItemCount;
		DWORD							dwItemMaxCount;
	};

	// 装备
	struct EquiCleanContent
	{
		std::wstring		wsItemName;
		em_Object_Type		emObjectType;
		CItem::ItemPoint	Loc;
		em_Equi_Color		emColor;
		DWORD				dwLevel;
		BOOL				IsBindAccount;
		BOOL				IsNotAppraisal;

		EquiCleanContent(_In_ CONST std::wstring& wsItemName_, _In_ em_Object_Type emObjectType_, _In_ CONST CItem::ItemPoint& Loc_, _In_ em_Equi_Color emColor_, _In_ DWORD dwLevel_, _In_ BOOL IsBindAccount_, _In_ BOOL IsNotAppraisal_)
		{
			wsItemName = wsItemName_;
			emObjectType = emObjectType_;
			Loc = Loc_;
			emColor = emColor_;
			dwLevel = dwLevel_;
			IsBindAccount = IsBindAccount_;
			IsNotAppraisal = IsNotAppraisal_;
		}
	};

	// 单个仓库页的装备
	struct WarehousePageEquiContent
	{
		std::vector<EquiCleanContent>	Vec;
		DWORD							dwItemCount;
		DWORD							dwItemMaxCount;
	};


	// 整个仓库
	struct WarehouseContent
	{
		std::vector<WarehousePageItemContent>   VecItem;
		std::vector<WarehousePageEquiContent>	VecEqui;

		void Release()
		{
			VecItem.clear();
			VecEqui.clear();
		}

	};
public:
	CItemClean();
	~CItemClean();

	static CItemClean& GetInstance();

	// 初始化的时候读取仓库的内容
	BOOL InitializeWarehouse();

	// 将背包的物品整理到仓库
	BOOL BagItemCleanToWarehouse();

private:
	// 丢弃物品
	VOID DropBagItem() CONST;

	// 移动到仓库
	BOOL MoveToWarehouse() CONST;

	// 打开仓库
	BOOL OpenWarehouse() CONST;

	// 遍历仓库的所有物品
	BOOL TraverseWarehouse();

	//
	VOID FillItemToWarehouseContent(_In_ CONST std::vector<CItem>& Vec, _Out_ WarehousePageItemContent& PageItem) CONST;

	//
	VOID FillEquiToWarehouseContent(_In_ CONST std::vector<CItem>& Vec, _Out_ WarehousePageEquiContent& PageEqui) CONST;

	//
	BOOL ClickWarehousePage(_In_ DWORD Index) CONST;

	//
	BOOL SaveItemToWarehouse(_In_ CONST CItem& itm);

	//
	BOOL SaveEquiToWarehouse(_In_ CONST CItem& equi);

	//
	VOID ChoiceDestory() CONST;

	//
	BOOL IsShowDestoryConform() CONST;

	// 根据条件掏出要刷的图
	BOOL TakeTheMap_For_Warehouse() CONST;

	// 在仓库里拿出物品
	BOOL TakeItem_For_Warehouse(_In_ CONST std::wstring& wsItemName) CONST;

	// 在仓库里点击物品
	BOOL RightClickItem_In_Warehouse(_In_ CONST std::wstring& wsItemName) CONST;

	// 在仓库搜索物品
	BOOL FindItem_In_Warehouse_By_ItemName(_In_ CONST std::wstring& wsItemName, _Out_ CItem& Item) CONST;
private:
	WarehouseContent _WarehouseContent;
	UINT			 _uMaxPageCount = 0;
};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_CLEAN_ITEMCLEAN_H__
