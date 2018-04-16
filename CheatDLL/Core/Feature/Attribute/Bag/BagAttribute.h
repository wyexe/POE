#ifndef __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_BAG_BAGATTRIBUTE_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_BAG_BAGATTRIBUTE_H__

#include <vector>
#include <GameStruct.h>


class CItem;
class CBagAttribute
{
public:
	CBagAttribute();
	~CBagAttribute();

	static UINT GetVecBagItem(_Out_ std::vector<CItem>& Vec);
private:

};


#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_BAG_BAGATTRIBUTE_H__
