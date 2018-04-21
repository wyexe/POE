#ifndef __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_BUFF_BUFFATTRIBUTE_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_BUFF_BUFFATTRIBUTE_H__

#include <GameStruct.h>
#include <string>
#include <vector>
#include <functional>

class CBuffAttribute
{
public:
	struct BuffObject
	{
		std::wstring wsBuffName;
		std::wstring wsBuffText;
	};

	enum em_Buff_Type
	{
		ManaAura,    // ÇåÎú¹â»·
	};

public:
	CBuffAttribute() = default;
	~CBuffAttribute() = default;

	static UINT GetVecBuff(_Out_ std::vector<BuffObject>& Vec);

	static BOOL IsExistBuff(_In_ em_Buff_Type emBuffType);
private:
	static UINT GetVecBuff(_Out_ std::vector<BuffObject>& Vec, _In_ std::function<BOOL(CONST std::wstring&)> FilterPtr);
};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ATTRIBUTE_BUFF_BUFFATTRIBUTE_H__
