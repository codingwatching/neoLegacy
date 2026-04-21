#pragma once

#include "Enchantment.h"

class DepthStriderEnchantment : public Enchantment
{
public:
	DepthStriderEnchantment(int id, int freq);

	virtual int getMinCost(int level);
	virtual int getMaxCost(int level);
	virtual int getMaxLevel();
};