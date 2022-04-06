#pragma once
#include <iostream>
#include <vector>
#include "Ship.h"
#include "Point.h"

class Grid
{
public:
	Grid();
	void DisplayGrid();
	void DisplayShipVector();
	void FillShipVector(Ship _ship);
	void SetShipVector(std::vector<Ship> _shipVect);
	std::vector<Ship> GetShipVector() { return ships; }
	std::vector<std::vector<char>> GetGrid() { return gridVect; }

	char GetGridValue(int x, int y);
	void SetGridValue(int x, int y, char v);

protected:
	std::vector<std::vector<char>> gridVect;
	std::vector<Ship> ships;
};