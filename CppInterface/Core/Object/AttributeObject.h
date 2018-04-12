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
	static BOOL FillObjectAttribute_Positioned(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Positioned", [&pObject](DWORD dwIndex)
		{
			DWORD dwPositionedObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetPoint(ReadDWORD(dwPositionedObject + 0x10), ReadDWORD(dwPositionedObject + 0x14));
		});
	}

	template<typename T>
	static BOOL FillObjectAttribute_Render(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Render", [&](DWORD dwIndex)
		{
			DWORD dwRenderObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			if (ReadDWORD(dwRenderObject + 怪物名字偏移 + 0x10) != 0)
			{
				pObject->SetName(reinterpret_cast<CONST WCHAR*>(ReadDWORD(dwRenderObject + 怪物名字偏移 + 0x10 + 0x4) > 0x7 ? ReadDWORD(dwRenderObject + 怪物名字偏移) : (dwRenderObject + 怪物名字偏移)));
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
	static BOOL FillObjectAttribute_IsBindAccount(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Base", [&](DWORD dwIndex)
		{
			DWORD dwBaseObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetIsBindAccount((ReadDWORD(dwBaseObject + 物品绑定偏移) & 0xFF) == 0 ? FALSE : TRUE);
		});
	}

	template<typename T>
	static BOOL FillObjectAttribute_Player(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Player", [&](DWORD dwIndex)
		{
			DWORD dwPlayerObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetName(reinterpret_cast<WCHAR*>(ReadDWORD(dwPlayerObject + 0x10 + 0x14) > 7 ? ReadDWORD(dwPlayerObject + 0x10) : (dwPlayerObject + 0x10)););
		});
	}

	template<typename T>
	static BOOL FillObjectAttribute_Color(_In_ T* pObject, _In_ DWORD dwModsObject = NULL)
	{
		switch (ReadBYTE(dwModsObject != NULL ? dwModsObject : pObject->GetNodeBase() + 0x18 + 物品颜色偏移))
		{
		case 0:
			pObject->_emEquiColor = em_Equi_Color::White;
			return TRUE;
		case 1:
			pObject->_emEquiColor = em_Equi_Color::Magic;
			return TRUE;
		case 2:
			pObject->_emEquiColor = em_Equi_Color::Rate;
			return TRUE;
		case 3:
			pObject->_emEquiColor = em_Equi_Color::Legend;
			return TRUE;
		default:
			pObject->_emEquiColor = em_Equi_Color::None;
			break;
		}

		return FALSE;
	}

	template<typename T>
	static void FillEquiObjectAttribute_Level(_In_ T* pObject, _In_ DWORD dwModObject = NULL)
	{
		pObject->SetEquiLevel(ReadDWORD(dwModsObject != NULL ? dwModsObject : pObject->GetNodeBase() + 物品需求等级偏移 - 0x4));
	}

	template<typename T>
	static BOOL FillEquiObjectAttribute_Appraisal(_In_ T* pObject, _In_ DWORD dwModObject = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwModObject != NULL ? dwModObject : pObject->GetNodeBase(), "Mods", [&](DWORD dwIndex)
		{
			DWORD dwModsObject = ReadDWORD(ReadDWORD(dwModObject != NULL ? dwModObject : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetIsNotAppraisal((ReadDWORD(dwModsObject + 物品鉴定偏移) & 0xFF) == 0 ? TRUE : FALSE);
		});
	}

	template<typename T>
	static BOOL FillEquiObjectAttribute_Quality(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Quality", [&](DWORD dwIndex)
		{
			DWORD dwQualityObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetQuality(ReadDWORD(dwQualityObject + 0xC) & 0xFF);
		});
	}


	template<typename T>
	static BOOL FillEquiObjectAttribute_Stack(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Stack", [&](DWORD dwIndex)
		{
			DWORD dwStackObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetStackAddr(dwStackObject);
		});
	}

	template<typename T>
	static BOOL FillFlasksObjectAttribute_Charges(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		return CAttributeObject::FillAttributeTable(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase(), "Charges", [&](DWORD dwIndex)
		{
			DWORD dwChargesObject = ReadDWORD(ReadDWORD(dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase() + 0x4) + dwIndex * 4);
			pObject->SetChargesAddr(dwChargesObject);
		});
	}

	template<typename T>
	static void FillItemObjectAttribute_Point(_In_ T* pObject, _In_ DWORD dwNodeBase = NULL)
	{
		DWORD dwItemObject = dwNodeBase != NULL ? dwNodeBase : pObject->GetNodeBase();
		pObject->SetItemLocation(ReadDWORD(dwItemObject + 物品左上角坐标), ReadDWORD(dwItemObject + 物品右上角坐标), ReadDWORD(dwItemObject + 物品左下角坐标), ReadDWORD(dwItemObject + 物品右下角坐标));
	}
};

#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_ATTRIBUTEOBJECT_H__
