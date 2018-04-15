#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_ATTRIBUTEOBJECT_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_ATTRIBUTEOBJECT_H__

#include <GameStruct.h>
#include <functional>
#include <vector>
#include <Core/Feature/GameMemory/GameMemory.h>

class CAttributeObject
{
public:
	CAttributeObject() = default;
	~CAttributeObject() = default;

	static em_Object_Type GetObjectType(_In_ DWORD dwNodeBase);

	static BOOL FillAttributeTable(_In_ DWORD dwAttributeNodeBase, _In_ LPCSTR pwszAttributeName, _In_ std::function<VOID(DWORD)> Ptr);

	template<typename T>
	static VOID FillObjectAttribute_ResName(_In_ T* pObject)
	{
		pObject->SetResName(ReadTextWithLength(ReadDWORD(pObject->GetNodeBase() + 0x0) + 0x10));
	}

	template<typename T>
	static BOOL FillObjectAttribute_Render(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Render", [&](DWORD dwIndex)
		{
			DWORD dwRenderObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetName(CGameMemory::GetInstance().ReadProcTextWithLength(dwRenderObject + ¹ÖÎïÃû×ÖÆ«ÒÆ));
		});
	}

	template<typename T>
	static BOOL FillObjectAttribute_Base(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Base", [&](DWORD dwIndex)
		{
			DWORD dwBaseObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetName(CGameMemory::GetInstance().ReadProcTextWithLength(ReadDWORD(dwBaseObject + 0x8) + 0x10));
		});
	}


	template<typename T>
	static BOOL FillObjectAttribute_Player(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Player", [&](DWORD dwIndex)
		{
			DWORD dwPlayerObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetName(CGameMemory::GetInstance().ReadProcTextWithLength(dwPlayerObject + 0x10));
		});
	}


	template<typename T>
	static BOOL FillObject_By_AttributeName(_In_ T* pObject, _In_ LPCSTR pszAttributeName, _Out_ DWORD& dwObjectAddr)
	{
		return CAttributeObject::FillAttributeTable(pObject->GetNodeBase(), pszAttributeName, [&](DWORD dwIndex)
		{
			dwObjectAddr = ReadDWORD(ReadDWORD(pObject->GetNodeBase() + 0x4) + dwIndex * 4);
		});
	}


	static BOOL FillObject_By_AttributeName(_In_ DWORD dwNodeBase, _In_ LPCSTR pszAttributeName, _Out_ DWORD& dwObjectAddr)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase, pszAttributeName, [&](DWORD dwIndex)
		{
			dwObjectAddr = ReadDWORD(ReadDWORD(dwNodeBase + 0x4) + dwIndex * 4);
		});
	}
};

#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_ATTRIBUTEOBJECT_H__
