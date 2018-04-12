#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_WORLDITEM_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_WORLDITEM_H__

#include "BaseObject.h"

class CWorldItem : public CBaseObject
{
public:
	CWorldItem();
	CWorldItem(_In_ DWORD dwNodeBase);
	~CWorldItem();

	virtual VOID RefreshObjectAttribute() override;

	em_Equi_Color GetEquiColor() CONST;

	DWORD GetEquiLevel() CONST;

	VOID  SetEquiLevel(_In_ DWORD dwLevel);

	BOOL  IsEqui() CONST;
private:
	em_Equi_Color	_emEquiColor = em_Equi_Color::None;
	DWORD			_dwEquiLevel = NULL;
	BOOL			_IsEqui = FALSE;
};


#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_WORLDITEM_H__
