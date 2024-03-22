#include "Attribute.h"
#include "CharacterStats.h"

Attribute::Attribute(Attributes type, int baseValue, CharacterStats* parent) :
	parent(parent),
	type(type),
	value([parent]()
		{
			parent->AttributeModified();
		})
{
	value.SetBaseValue(baseValue);
}
