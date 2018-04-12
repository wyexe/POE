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
	CAttributeObject::FillObject_By_AttributeName(this, "Positioned", _dwPositionedObject);
	CAttributeObject::FillObjectAttribute_Render(this);
}
