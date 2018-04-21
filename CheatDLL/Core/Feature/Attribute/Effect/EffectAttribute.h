#ifndef __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_EFFECT_EFFECTATTRIBUTE_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_EFFECT_EFFECTATTRIBUTE_H__

#include <GameStruct.h>
#include <vector>

class CEffectAttribute
{
public:
	struct EffectIconObject
	{
		DWORD Index;
		DWORD dwObject;
		DWORD dwId;

		DWORD GetCount() CONST;
	};
public:
	CEffectAttribute() = default;
	~CEffectAttribute() = default;

	static UINT GetVecEffect(_Out_ std::vector<EffectIconObject>& Vec);
private:

};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_EFFECT_EFFECTATTRIBUTE_H__
