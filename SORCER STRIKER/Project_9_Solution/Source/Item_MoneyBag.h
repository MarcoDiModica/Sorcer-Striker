#ifndef __ITEM_MONEYBAG_H__
#define __ITEM_MONEYBAG_H__

#include "Item.h"
#include "Path.h"

class Item_MoneyBag : public Item 
{
public:

	Item_MoneyBag(int x, int y);

	void Update() override;

	

private:
	Path path;

	Animation hoveranim;

};

#endif 