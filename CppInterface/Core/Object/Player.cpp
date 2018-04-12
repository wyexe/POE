#include "Player.h"
#include "AttributeObject.h"

CPlayer::CPlayer()
{
	
}

CPlayer::CPlayer(_In_ DWORD dwNodeBase)
{
	SetNodeBase(dwNodeBase);
}

CPlayer::~CPlayer()
{

}

VOID CPlayer::RefreshObjectAttribute()
{
	CAttributeObject::FillObjectAttribute_Player(this);
	CAttributeObject::FillObjectAttribute_Positioned(this);
}
