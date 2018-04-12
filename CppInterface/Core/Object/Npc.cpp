#include "Npc.h"
#include "AttributeObject.h"

CNpc::CNpc()
{
	
}

CNpc::CNpc(_In_ DWORD dwNodeBase)
{
	SetNodeBase(dwNodeBase);
}

CNpc::~CNpc()
{
}

VOID CNpc::RefreshObjectAttribute()
{
	CAttributeObject::FillObjectAttribute_Positioned(this);
	CAttributeObject::FillObjectAttribute_Render(this);
}
