#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions.h"
#include "GameLogic.h"
#include "Grid.h"
#include "ShipGrid.h"
#include "FireGrid.h"
#include "Ship.h"

//This function handles input from the csv.
std::vector<Ship> ReadInShipFromCSV(std::fstream &in) throw (InputFileError)
{
	std::string stringTemp;
	std::vector<Ship> ourShipVect;
	std::exception e;
	while (std::getline(in, stringTemp, ','))
	{
		try
		{
			if (stringTemp.empty())//if string.empty() we have a serious issue with the input file
				throw e;

			std::string sType;
			sType = stringTemp;
			std::string position;
			std::getline(in, position, ',');

			if (position.empty())//if string.empty() we have a serious issue with the input file
				throw e;

			int shipSize = GetShipSize(sType);

			char sAllignment = '!';
			std::getline(in, stringTemp);

			if (sType.empty() || stringTemp.empty())//if string.empty() we have a serious issue with the input file
				throw e;

			sAllignment = stringTemp.front();
			if ((sAllignment != 'H') && (sAllignment != 'V'))
			{
				if (sAllignment == 'h')
					sAllignment = 'H';

				else if (sAllignment == 'v')
					sAllignment = 'V';

				else//The ship allignment is invalid
					throw e;
			}
			int positionX = CharToInt(position.front());
			//CharToInt will return -2 if an invalid character is entered as the x position
			if (positionX == -2)
				throw e;

			int positionY;
			if (position[2] != '0')
				positionY = int(position[1]) - 49;
			else
				positionY = int(position[1]) - 40;//since we are dealing with chars, if the second digit is 0, we assume the user entered x10
			try
			{
				ShipDataInvalid sdi;
				if (positionY > 9 || positionY < 0)
				{
					throw sdi;//position is invalid
				}

				if (sAllignment == 'H')
				{
					if (positionX + shipSize > 9)
						throw sdi;//ship is out of bounds
				}

				else if (sAllignment == 'V')
				{
					if (positionY + shipSize > 9)
						throw sdi;//ship is out of bounds
				}

				else
					throw sdi;//The ship is missing its allignment char
			}
			catch (ShipDataInvalid s)
			{
				std::cout << s.error;
				exit(-2);//All of these are fatal errors
				//We don't want to try to guess at what the user intended, so we have the user fix the issue
			}

			Ship shipName(sType, positionX, positionY, GetShipSize(sType), sAllignment);
			ourShipVect.push_back(shipName);
		}
		catch (std::exception& e)
		{
			MissingObjects m;
			throw m;
		}
	}
	return ourShipVect;
}

//Function to set up the ships
void InputOurShipData(ShipGrid& sg)
{
	std::fstream in("ship_placement.csv");
	try
	{
		if (!in.is_open())
		{
			FileNotFound f;
			throw f;
		}
	}
	catch (FileNotFound f)
	{
		std::cout << f.error;
		exit(-1);
	}


	try
	{
		std::vector<Ship> shipVector;
		shipVector = ReadInShipFromCSV(in);
		sg.SetShipVector(shipVector);//get this from ReadInShip
		sg.FillShipGridWithShips();

		std::vector<Ship> testingExceptions = sg.GetShipVector();
		if (testingExceptions.size() != 5)
		{
			MissingObjects m;
			m.error.append("\n\nShips Missing From File!!!\nThere are ships missing from the input file!\n\n");
			throw m;
		}

		for (int i = 0; i < testingExceptions.size(); i++)//breakpoint was here
		{
			for (int j = 0; j < testingExceptions.size(); j++)
			{
				if (testingExceptions[i].CheckForCollision(testingExceptions[j]))
				{
					MissingObjects m;
					m.error.append("\n\nShip Collision Detected!!!\nTwo Ships inhabit the same position, please check the file!\n\n");
					throw m;
				}
			}
		}
	}
	catch (MissingObjects m)
	{
		std::cout << m.error;
		exit(-1);
	}
	in.close();
}

int main()
{
	char selectedMenuItem = '\0';
	while (selectedMenuItem != 'q')
	{
		ShipGrid OurShipGrid;
		FireGrid OurFireGrid;
		selectedMenuItem = DisplayMainMenu();//DisplayMainMenu will return 'a' if the user wants to play the game
		if (selectedMenuItem == 'a')
		{
			InputOurShipData(OurShipGrid);
			std::cout << "\033[2J\033[1;1H";//this has the same effect as clearing the console
			DriverFunction(OurShipGrid, OurFireGrid);
		}
	}
}