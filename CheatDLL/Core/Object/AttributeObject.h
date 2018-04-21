#ifndef __LFZL_CHEATDLL_CORE_OBJECT_ATTRIBUTEOBJECT_H__
#define __LFZL_CHEATDLL_CORE_OBJECT_ATTRIBUTEOBJECT_H__

#include <GameStruct.h>
#include <functional>
#include <vector>
#include <Core/Feature/GameMemory/GameMemory.h>

class CAttributeObject
{
public:
	CAttributeObject() = default;
	~CAttributeObject() = default;

	static em_Object_Type GetObjectType(_In_ DWORD dwAttributeTablePtr);

	static std::wstring   GetObjectTypeText(_In_ em_Object_Type emObjectType);

	static BOOL FillAttributeTable(_In_ DWORD dwAttributeNodeBase, _In_ LPCSTR pwszAttributeName, _In_ std::function<VOID(DWORD)> Ptr);

	template<typename T>
	static VOID FillObjectAttribute_ResName(_In_ T* pObject)
	{
		pObject->SetResName(CGameMemory::GetInstance().ReadProcTextWithLength(ReadDWORD(pObject->GetNodeBase() + 0x0) + 0x10));
	}

	template<typename T>
	static BOOL FillObjectAttribute_Render(_In_ T* pObject, _In_ DWORD dwAttributeTablePtr = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwAttributeTablePtr != NULL ? dwAttributeTablePtr : pObject->GetAttributeTablePtr(), "Render", [&](DWORD dwIndex)
		{
			DWORD dwRenderObject = ReadDWORD(ReadDWORD(dwAttributeTablePtr != NULL ? dwAttributeTablePtr : pObject->GetAttributeTablePtr() + 0x4) + dwIndex * 4);
			pObject->SetName(CGameMemory::GetInstance().ReadProcTextWithLength(dwRenderObject + ¹ÖÎïÃû×ÖÆ«ÒÆ));
		});
	}

	template<typename T>
	static BOOL FillObjectAttribute_Base(_In_ T* pObject, _In_ DWORD dwAttributeTablePtr = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwAttributeTablePtr != NULL ? dwAttributeTablePtr : pObject->GetAttributeTablePtr(), "Base", [&](DWORD dwIndex)
		{
			DWORD dwBaseObject = ReadDWORD(ReadDWORD(dwAttributeTablePtr != NULL ? dwAttributeTablePtr : pObject->GetAttributeTablePtr() + 0x4) + dwIndex * 4);
			pObject->SetName(CGameMemory::GetInstance().ReadProcTextWithLength(ReadDWORD(dwBaseObject + 0x8) + 0x10));
		});
	}


	template<typename T>
	static BOOL FillObjectAttribute_Player(_In_ T* pObject, _In_ DWORD dwAttributeTablePtr = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwAttributeTablePtr != NULL ? dwAttributeTablePtr : pObject->GetAttributeTablePtr(), "Player", [&](DWORD dwIndex)
		{
			DWORD dwPlayerObject = ReadDWORD(ReadDWORD(dwAttributeTablePtr != NULL ? dwAttributeTablePtr : pObject->GetAttributeTablePtr() + 0x4) + dwIndex * 4);
			pObject->SetName(CGameMemory::GetInstance().ReadProcTextWithLength(dwPlayerObject + 0x10));
		});
	}


	template<typename T>
	static BOOL FillObject_By_AttributeName(_In_ T* pObject, _In_ LPCSTR pszAttributeName, _Out_ DWORD& dwObjectAddr)
	{
		return CAttributeObject::FillAttributeTable(pObject->GetAttributeTablePtr(), pszAttributeName, [&](DWORD dwIndex)
		{
			dwObjectAddr = ReadDWORD(ReadDWORD(pObject->GetAttributeTablePtr() + 0x4) + dwIndex * 4);
		});
	}


	static BOOL FillObject_By_AttributeName(_In_ DWORD dwAttributeTablePtr, _In_ LPCSTR pszAttributeName, _Out_ DWORD& dwObjectAddr)
	{
		return CAttributeObject::FillAttributeTable(dwAttributeTablePtr, pszAttributeName, [&](DWORD dwIndex)
		{
			dwObjectAddr = ReadDWORD(ReadDWORD(dwAttributeTablePtr + 0x4) + dwIndex * 4);
		});
	}
};

#endif // !__LFZL_CHEATDLL_CORE_OBJECT_ATTRIBUTEOBJECT_H__
