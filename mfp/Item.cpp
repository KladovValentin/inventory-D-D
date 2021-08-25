#include "Item.h"

Item Item::operator = (const Item& rItem) {
	type = rItem.type;
	name = rItem.name;
	description = rItem.description;
	sprite = rItem.sprite;
	cell = rItem.cell;
	amount = rItem.amount;
	mass = rItem.mass;
	value = rItem.value;
	return *this;
}