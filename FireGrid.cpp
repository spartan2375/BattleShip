#include "FireGrid.h"

void FireGrid::SetupFireGrid(std::vector<std::vector<char>> _grid)
{
	fireGridVect = gridVect;
}

void FireGrid::DisplayFireGrid()
{
	{
		//std::cout << "\033[2J\033[1;1H";
		std::cout << "\033[1;34m";
		std::cout << "  ";
		for (int i = 0; i < fireGridVect.size(); i++)
		{
			std::cout << "|" << char('A' + i);
		}
		std::cout << "|\n";

		for (int i = 0; i < fireGridVect.size(); i++)
		{
			(i != 9) ? std::cout << i + 1 << " " : std::cout << i + 1;
			for (int j = 0; j < fireGridVect[i].size(); j++)
			{
				std::cout << "|" << fireGridVect[i][j];
			}
			std::cout << "|\n";
		}
		std::cout << "\033[0m";
	}
}

int FireGrid::FireTorpedoAtFireGrid(int xShot, int yShot, Grid& _grid)
{
	if (_grid.GetGrid()[xShot][yShot] != '~')
	{
		if (_grid.GetGrid()[xShot][yShot] == '0' || _grid.GetGrid()[xShot][yShot] == 'X')
		{
			return -3;
		}
		_grid.SetGridValue(xShot, yShot, '0');
		fireGridVect[xShot][yShot] = '0';
		for (int i = 0; i < _grid.GetShipVector().size(); i++)
			for (int j = 0; j < _grid.GetShipVector()[i].GetSize(); j++)
				if (_grid.GetShipVector()[i].positions[j].GetX() == yShot && _grid.GetShipVector()[i].positions[j].GetY() == xShot)
					return i;//return the index of the ship that was hit
	}
	else
	{
		fireGridVect[xShot][yShot] = 'X';
		_grid.SetGridValue(xShot, yShot, 'X');
		return -1;
	}
}