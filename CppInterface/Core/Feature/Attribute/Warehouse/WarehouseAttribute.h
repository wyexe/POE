#ifndef __LFZL_CPPINTERFACE_CORE_FEATURE_ATTRIBUTE_WAREHOUSE_WAREHOUSEATTRIBUTE_H__
#define __LFZL_CPPINTERFACE_CORE_FEATURE_ATTRIBUTE_WAREHOUSE_WAREHOUSEATTRIBUTE_H__

#include <GameStruct.h>
#include <vector>

class CItem;
class CWarehouseAttribute
{
public:
	CWarehouseAttribute() = default;
	~CWarehouseAttribute() = default;

	static BOOL IsOpenedWarehouse();

	// 总共几页的仓库
	static DWORD GetWarehousePageCount();

	// 当前打开的是第几页仓库
	static DWORD GetCurrentPageIndex();

	// 当前索引页的仓库页对象
	static DWORD GetCurrentPageObject();

	// 获取当前仓库页的物品
	static UINT GetCurrentPageItem(_Out_ std::vector<CItem>& Vec);
private:
	static DWORD GetWarehouseNodeBase();

	static DWORD GetWarehouseObject();
};


#endif // !__LFZL_CPPINTERFACE_CORE_FEATURE_ATTRIBUTE_WAREHOUSE_WAREHOUSEATTRIBUTE_H__
