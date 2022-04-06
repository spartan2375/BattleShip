#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
class Ship
{
public:
	void ShowShip()//Displays the ship, used for testing purposes
	{
		std::cout << shipType << ", " << size << ", " << allignment << ", " << x << ", " << y << std::endl;
	}

	Ship()
	{
		shipType = "";
		x = 0;
		y = 0;
		size = 0;
		health = 0;
		allignment = 'N';
	}

	Ship(std::string _type, int _x, int _y, int _size, char _allign)
	{
		shipType = _type;
		x = _x;
		y = _y;
		size = _size;
		health = _size;
		allignment = _allign;
	}

	//Returns true if ships inhabit same cell
	bool CheckForCollision(Ship s2)
	{
		//check if its the same ship
		if (this->shipType == s2.GetType() && this->allignment == s2.GetAllignment()
			&& this->x == s2.GetX() && this->y == s2.GetY())
			return false;

		//we have to use the smaller size to avoid accessing an index that is out of bounds
		int smallerSize = (positions.size() < s2.positions.size()) ? positions.size() : s2.positions.size();

		//For each position, for each position of the other ship, check if its the same spot
		for (int i = 0; i < smallerSize; i++)
		{
			for (int j = 0; j < smallerSize; j++)
			{
				if (positions[i] == s2.positions[j])
					return true;//if it is the same spot, the position is invalid
			}
		}
		return false;//If we reach this far, the position is valid
	}

	std::string GetType() { return shipType; }
	int GetX() { return x; }
	int GetY() { return y; }
	int GetSize() { return size; }
	char GetAllignment() { return allignment; }
	void SetShipHealth(int _health) { health = _health; }
	int GetShipHealth() { return health; }

	std::vector<Point>positions;


private:
	int size;
	int x, y;
	char allignment;
	int health;
	std::string shipType;
};