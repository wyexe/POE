#include "FilterConfig.h"

CFilterConfig& CFilterConfig::GetInstance()
{
	static CFilterConfig Instance;
	return Instance;
}

BOOL CFilterConfig::Initialize()
{
	return FALSE;
}

BOOL CFilterConfig::IsTakeWorldItem(_In_ CONST CWorldItem& WorldItem) CONST
{
	return FALSE;
}

BOOL CFilterConfig::IsKeepItem(_In_ CONST CItem& Item) CONST
{
	return FALSE;
}

BOOL CFilterConfig::IsAttackMonster(_In_ CONST CMonster& Monster) CONST
{
	return FALSE;
}
