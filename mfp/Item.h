#pragma once
#include "mainHeader.h"

class Item
{
public:
	string type;
	string name;
	string description;
	Sprite sprite;
	size_t cell;
	size_t amount;
	double mass;
	double value;

	Item(string iname, string itype) :name(iname), type(itype), amount(1), cell(0),mass(0),value(0),sprite() {};

	void setTexture(Texture t) { sprite.setTexture(t); }
	void setCell(size_t cellN) { cell = cellN; }
	void setInCell() { sprite.setPosition(Vector2f(float(100 * (cell - 8 * (cell / 8))), float(100 * (cell / 8))+50)); }

	Item operator = (const Item& rItem);
};

