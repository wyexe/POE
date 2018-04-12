#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_ATTRIBUTEOBJECT_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_ATTRIBUTEOBJECT_H__

#include <GameStruct.h>
#include <functional>
#include <vector>

class CAttributeObject
{
public:
	CAttributeObject() = default;
	~CAttributeObject() = default;

	static BOOL FillAttributeTable(_In_ DWORD dwAttributeNodeBase, _In_ LPCSTR pwszAttributeName, _In_ std::function<VOID(DWORD)> Ptr);

	template<typename T>
	static BOOL FillObjectAttribute_ResName(_In_ T* pObject)
	{
		DWORD dwNodeResPtr = ReadDWORD(pObject->GetNodeBase() + 0x0);
		if (ReadDWORD(dwNodeResPtr + 0x10 + 0x10) != 0)
		{
			pObject->SetResName(reinterpret_cast<CONST WCHAR*>(ReadDWORD(dwNodeResPtr + 0x10 + 0x10 + 0x4) > 0x7 ? ReadDWORD(dwNodeResPtr + 0x10) : (dwNodeResPtr + 0x10)));
			return TRUE;
		}


		return FALSE;
	}

	template<typename T>
	static BOOL FillObjectAttribute_Render(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Render", [&](DWORD dwIndex)
		{
			DWORD dwRenderObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			if (ReadDWORD(dwRenderObject + ¹ÖÎïÃû×ÖÆ«ÒÆ + 0x10) != 0)
			{
				pObject->SetName(reinterpret_cast<CONST WCHAR*>(ReadDWORD(dwRenderObject + ¹ÖÎïÃû×ÖÆ«ÒÆ + 0x10 + 0x4) > 0x7 ? ReadDWORD(dwRenderObject + ¹ÖÎïÃû×ÖÆ«ÒÆ) : (dwRenderObject + ¹ÖÎïÃû×ÖÆ«ÒÆ)));
			}
		});
	}

	template<typename T>
	static BOOL FillObjectAttribute_Base(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Base", [&](DWORD dwIndex)
		{
			DWORD dwBaseObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			DWORD dwNamePtr = ReadDWORD(dwBaseObject + 0x8);
			if (ReadDWORD(dwNamePtr + 0x10 + 0x10) != 0)
			{
				pObject->SetName(reinterpret_cast<WCHAR*>(ReadDWORD(dwNamePtr + 0x10 + 0x14) > 7 ? ReadDWORD(dwNamePtr + 0x10) : (dwNamePtr + 0x10)));
			}
		});
	}


	template<typename T>
	static BOOL FillObjectAttribute_Player(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Player", [&](DWORD dwIndex)
		{
			DWORD dwPlayerObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetName(reinterpret_cast<WCHAR*>(ReadDWORD(dwPlayerObject + 0x10 + 0x14) > 7 ? ReadDWORD(dwPlayerObject + 0x10) : (dwPlayerObject + 0x10)));
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
