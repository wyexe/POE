#ifndef __LFZL_CPPINTERFACE_CORE_OBJECT_MONSTER_H__
#define __LFZL_CPPINTERFACE_CORE_OBJECT_MONSTER_H__

#include "BaseObject.h"

class CMonster : public CBaseObject
{
public:
	enum class em_Monster_LiveType
	{
		None,
		Dead,
		Live,
		Trigger,
	};
public:
	CMonster();
	CMonster(_In_ DWORD dwNodeBase);
	~CMonster();

	// !
	virtual VOID RefreshObjectAttribute() override;

	// 挂了?
	BOOL IsDead() CONST;


	// 血量百分比
	DWORD GetPercentHp() CONST;


	// 是否允许被攻击
	BOOL IsAllowAttack() CONST;
private:
	DWORD _dwLifeObject = NULL;
	DWORD _dwActorObject = NULL;
};



#endif // !__LFZL_CPPINTERFACE_CORE_OBJECT_MONSTER_H__
