#include "Grid.h"

Grid::Grid()
{
	int M, N;
	M = 10;
	N = 10;
	std::vector<char> v(N, '~');
	std::vector<std::vector<char>> tempVector(10, v);
	gridVect = tempVector;
}

//Displays the grid to the console
void Grid::DisplayGrid()
{
	std::cout << "\033[1;34m";
	std::cout << "  ";
	for (int i = 0; i < gridVect.size(); i++)//prints the top row of the grid
	{
		std::cout << "|" << char('A' + i);
	}
	std::cout << "|\n";
	for (int i = 0; i < gridVect.size(); i++)
	{
		(i != 9) ? std::cout << i + 1 << " " : std::cout << i + 1;//10 does not need an extra whitespace to make everything fit
		for (int j = 0; j < gridVect[i].size(); j++)
		{
			std::cout << "|" << gridVect[i][j];
		}
		std::cout << "|\n";
	}
	std::cout << "\033[0m";
}

//Used for testing purposes, this displays the ships on the grid
void Grid::DisplayShipVector()
{
	std::cout << "Type, Size, Allignment, X, Y: \n";
	for (int i = 0; i < ships.size(); i++)
	{
		ships[i].ShowShip();
		for (int j = 0; j < ships[i].positions.size(); j++)
		{
			std::cout << "X, Y: " << ships[i].positions[j].GetX() << ", " << ships[i].positions[j].GetY() << "\n";
		}
	}
}

void Grid::FillShipVector(Ship _ship)
{
	ships.push_back(_ship);
}

void Grid::SetShipVector(std::vector<Ship> _shipVect)
{
	ships = _shipVect;
}

char Grid::GetGridValue(int x, int y)
{
	return gridVect[x][y];
}

void Grid::SetGridValue(int x, int y, char v)
{
	gridVect[x][y] = v;
}
