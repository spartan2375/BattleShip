#pragma once
#include "Grid.h"
class FireGrid : public Grid
{
public:
	void SetupFireGrid(std::vector<std::vector<char>> _grid);
	void DisplayFireGrid();
	int FireTorpedoAtFireGrid(int xShot, int yShot, Grid& _grid);

private:
	std::vector<std::vector<char>> fireGridVect;
};