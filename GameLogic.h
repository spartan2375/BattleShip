#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "Grid.h"
#include "ShipGrid.h"
#include "FireGrid.h"
#include "Ship.h"

char DisplayMainMenu();
void DisplayTutorial();
bool ShipDestroyed(ShipGrid& _shipGrid, int shipNum, bool b);
void SetComputerShipGrid(ShipGrid& compShipGrid, std::string shipNames[]);
bool TestShipGridPlacement(ShipGrid csg);
Point GenerateComputerShot(ShipGrid& ourShipGrid, std::vector<Point> &shots);
int TakeShot(FireGrid& fireGrid, ShipGrid& shipGrid, int _x, int _y);
bool DriverFunction(ShipGrid& ourShipGrid, FireGrid& ourFireGrid);
int GetShipSize(std::string _type);
int CharToInt(char c);