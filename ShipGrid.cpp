#include "ShipGrid.h"

void ShipGrid::FillShipGridWithShips()
{
	for (int i = 0; i < ships.size(); i++)
	{
		std::string _type = ships[i].GetType();
		int _size = ships[i].GetSize();
		int _x = ships[i].GetY();//This used to be getX, but the way the 2d grid vector is set up, it is this way
		int _y = ships[i].GetX();//This used to be getY
		char _allign = ships[i].GetAllignment();

		if (_allign == 'V')
			for (int j = 0; j < _size; j++)
			{
				if ((_x + j) < 0 || (_x + j) > 9)//checking for weird issues relating to out of bounds stuff
				{
					std::exception e;
					throw e;
				}
				gridVect[_x + j][_y] = _type.at(j);
				Point point(_y, _x + j);
				ships[i].positions.push_back(point);//We store each position in the ship's position vector
			}

		else if (_allign == 'H')
			for (int j = 0; j < _size; j++)
			{
				if ((_y + j) < 0 || (_y + j) > 9)//checking for weird issues...
				{
					std::exception e;
					throw e;
				}
				gridVect[_x][_y + j] = _type.at(j);
				Point point(_y + j, _x);
				ships[i].positions.push_back(point);//We store each position in the ship's position vector
			}
	}
}

void ShipGrid::FireTorpedoAtShipGrid(int xShot, int yShot)
{
	//if the shot was a hit
	if (gridVect[xShot][yShot] != '~')
	{
		gridVect[xShot][yShot] = '0';
	}
	else
	{
		gridVect[xShot][yShot] = 'X';
	}
}
//returns the index of the ship at the spot, -1 if miss
int ShipGrid::ShipHit(Point p)
{
	for (int i = 0; i < ships.size(); i++)
	{
		for (int j = 0; j < ships[i].GetSize(); j++)
		{
			if (p == ships[i].positions[j])
				return i;//returns the index of the ship that was hit
		}
	}
	return -1;//shot was a miss
}
