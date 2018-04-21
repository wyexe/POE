#ifndef __LFZL_COMMON_COMMONTEMPLATE_H__
#define __LFZL_COMMON_COMMONTEMPLATE_H__

#include <vector>

class CCommonTemplate
{
public:
	CCommonTemplate() = default;
	~CCommonTemplate() = default;


	template<typename T>
	static BOOL AssignNotEmptyToPtrAndReturn(_Out_opt_ T* Ptr, _In_ CONST std::vector<T>& Vec)
	{
		if (!Vec.empty())
		{
			if (Ptr != nullptr)
			{
				*Ptr = Vec.at(0);
			}
			return TRUE;
		}
		return FALSE;
	}
private:

};



#endif // !__LFZL_COMMON_COMMONTEMPLATE_H__
