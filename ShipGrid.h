#pragma once
#include "Grid.h"
class ShipGrid : public Grid
{
public:
	void FillShipGridWithShips();
	void FireTorpedoAtShipGrid(int xShot, int yShot);
	int ShipHit(Point p);
};