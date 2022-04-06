#include "GameLogic.h"
//This file contains most of the general logic specific to the game
//sorry it ended up being relatively long

//Main Menu function displays the main menu text to the user
char DisplayMainMenu()
{
	bool quitGame = false;
	while (!quitGame)
	{
		std::cout << "\033[2J\033[1;1H";//this clears the screen
		std::cout << "\033[1;32m";//this changes the color of the text
		std::cout << "BattleShip: The Computer Game\n\n~~~~~~~Main Menu~~~~~~~\n";
		std::cout << "Please select an option (a, b, q)\n"
			<< "a. Play The Game!\n" << "b. Read the tutorial\n" << "q. Quit\n";
		char userInput = std::getchar();
		if (userInput == 'a' || userInput == 'A')
		{
			return 'a';//This calls DriverFunction() in main
		}

		else if (userInput == 'b' || userInput == 'B')
		{
			DisplayTutorial();
			return 'b';
		}

		else if (userInput == 'q' || userInput == 'Q')
		{
			return 'q';
		}

		else
		{
			std::cout << "\nYou did not enter a valid option!\nPlease enter a, b, c, or q to select an option.\n";
		}
		std::cout << "\033[0m";
	}
	return false;
}

//We have a tutorial just in case the user wants it
void DisplayTutorial()
{
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Page 1, General Info\n\nWelcome to a rendition of the classic board game popularly know as Battleship!!!\n"
		<< "\nThe objective of the game is to sink the enemy's ships before they sink yours.\n"
		<< "Today we are playing agaisnt just the computer, who will only give random guesses.\n"
		<< "However, I had enough time to make it so that each ship has hp (healthpoints)\n"
		<< "so you have to hit all the ships' locations or positions to win the game.\n"
		<< "But don't worry, it takes quite some time for the computer to hit all the shots.\n"
		<< "\nNext: 'n'\nQuit: 'q'(or anything other than n)\n";
	char selected;
	std::cin >> selected;
	if (selected == 'n')
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "Page 2, How To Play\n\nThe game revolves around making educated guesses where the ships are.\n"
			<< "You will enter your guess each round in the form of coordinates.\n"
			<< "For example, if you think the enemy has a ship at A1, you will enter either\n"
			<< "A1 or a1, the program recognizes both upper and lowercase guesses.\n"
			<< "A hit will show up on the upper grid as a 0 and a miss will show up as a X.\n"
			<< "All of the guesses must be in this form: a character followed by a number.\n"
			<< "If you make a typo, the program will just let you know if it is an invalid guess.\n"
			<< "\nNext: 'n'\nQuit: 'q'(or anything other than n)\n";;
		std::cin >> selected;
		if (selected == 'n')
		{
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Last Page\n\nTired of guessing?\nOr are you just interested in testing the program?\n"
				<< "Type 'sv_cheats1' to show the computer's ships instead of your normal firing grid.\n"
				<< "Dont worry, you can always type sv_cheats1 again to toggle it on and off.\n"
				<< "\nQuit: 'q'(or anything)\n";;
			std::cin >> selected;
		}
	}
}

//Function to display the end of the game message 
void DisplayGameOverMessage(bool getThatDub)
{
	if (getThatDub)
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "Congratulations!!!\nYou won the game!\n\n";
		std::cout << "Enter anything to return to the main menu.\n";
		std::string somethingUseful;
		std::cin >> somethingUseful;
	}

	else
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "That's too bad\nYou lost the game!\n\n";
		std::cout << "Enter anything to return to the main menu.\n";
	}
} //Make it show the grids one last time

//This alerts the user of invalid guesses
//We don't need proper exception handling here because we can just reset that round of the game
void AlertUserOfException(int ex)
{
	std::string userIn;
	bool isAck = false;
	switch (ex)
	{
	case -1:

	case -2:
		while (!isAck)
		{
			std::cout << "\n\nYou entered an invalid selection for firing a torpedo!\n"
				<< "You MUST enter a guess in the format a1.\n"
				<< "   The letter MUST be from a to j inclusive.\n"
				<< "   The number MUST be from 1 to 10 inclusive.\n"
				<< "Enter 'ok' to continue: ";
			std::cin >> userIn;
			if (userIn == "ok")
				isAck = !isAck;
		}
		break;

	case -3:
		while (!isAck)
		{
			std::cout << "\n\nYou entered an invalid selection for firing a torpedo!\n"
				<< "   You can not enter a duplicate guess.\n"
				<< "   You already fired a torpedo in this location.\n"
				<< "   Let's not waste our tax dollars by firing in a spot we know the enemy isn't.\n"
				<< "Enter 'ok' to continue: ";
			std::cin >> userIn;
			if (userIn == "ok")
				isAck = !isAck;
		}
		break;

	default:
		break;
	}
}

//Checks if the ship was destroyed, returns false if other ships are alive
bool ShipDestroyed(ShipGrid& _shipGrid, int shipNum, bool b)
{
	if (_shipGrid.GetShipVector()[shipNum].GetShipHealth() == 0)
	{
		//Here is where we alert the user if they sunk the computer's ship or vice versa
		b ? std::cout << "You sunk the computer's " : std::cout << "The computer sunk your ";
		std::cout << _shipGrid.GetShipVector()[shipNum].GetType() << "!\n";
	}
	bool shipsAlive = true;
	for (int i = 0; i < 5; i++)
	{
		if (!(_shipGrid.GetShipVector()[i].GetShipHealth() <= 0))
			shipsAlive = false;
	}
	return shipsAlive;//shipsAlive is true if any ships have hp > 0, so, if shipsAlive is false, we end the game
}

//We do a couple checks to make sure input is a valid guess
bool TestUserInput(std::string in, int& x, int& y)
{
	if (in.length() == 1)
	{
		AlertUserOfException(-2);
		return true;
	}

	x = CharToInt(in.front());
	if (x == -2)
	{
		AlertUserOfException(x);
		return true;
	}

	//since we are using chars, we need to check the 3rd index to see if it is a 0
	//if it is, we assume the user entered x10 where x is any valid char
	y = (in[2] != '0') ? int(in[1]) - 49 : int(in[1]) - 40;

	if (y < 0 || y > 9)
	{
		AlertUserOfException(-2);
		return true;
	}
	return false;
}

//Sets up the computer's ships every game
void SetComputerShipGrid(ShipGrid& compShipGrid, std::string shipNames[])
{
	int tempSize, tempX, tempY;
	char tempAllign;
	std::vector<Ship> shipVect;
	//For each of the 5 ships, we get a random position for its location
	for (int i = 0; i < 5; i++)
	{
		tempSize = GetShipSize(shipNames[i]);
		tempX = -1;
		tempY = -1;
		tempAllign = NULL;
		while (tempAllign == NULL)//we continue until we have a valid spot
		{
			tempX = rand() % 10;
			tempY = rand() % 10;
			if ((tempX + tempSize) <= 9) //If it fits in the horizontal allignment, it will be horizontal
			{
				tempAllign = 'H';
			}

			else if ((tempY + tempSize) <= 9)//Same as above exept vertical
			{
				tempAllign = 'V';
			}
		}
		Ship Car(shipNames[i], tempX, tempY, tempSize, tempAllign);
		shipVect.push_back(Car);
		compShipGrid.SetShipVector(shipVect);
		compShipGrid.FillShipGridWithShips();
	}

	//If the position is invalid for some reason, we try again
	if (TestShipGridPlacement(compShipGrid))
	{
		shipVect.clear();
		ShipGrid newCompShipGrid;
		compShipGrid = newCompShipGrid;
		SetComputerShipGrid(compShipGrid, shipNames);
	}
}

//Here we test for two more issues with computer ship placement
bool TestShipGridPlacement(ShipGrid csg)
{
	std::vector<Ship> testingExceptions = csg.GetShipVector();
	//1. The computer is missing ships
	if (testingExceptions.size() != 5)
	{
		std::cout << "\n\nThere was a fatal error when generating the computer's ships.\nExiting now...";
		exit(-2);
	}

	//2. The computer's ships overlap
	bool shipBuildingFailed = false;
	for (int i = 0; i < testingExceptions.size(); i++)
	{
		for (int j = 0; j < testingExceptions.size(); j++)
		{
			if (testingExceptions[i].CheckForCollision(testingExceptions[j]))//CheckForCollision tests for overlap
				return true;
		}
	}
	return false;
}

//Generate a random shot for the computer
Point GenerateComputerShot(ShipGrid& ourShipGrid, std::vector<Point>& shots)
{
	int x, y;
	while (true)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (ourShipGrid.GetGrid()[y][x] != 'X' && ourShipGrid.GetGrid()[y][x] != '0')//checks if this is a new guess
		{
			Point p(x, y);
			shots.push_back(p);
			ourShipGrid.FireTorpedoAtShipGrid(y, x);
			break;
		}
	}
	Point p(x, y);
	return p;
}

//Updates the grid and gets the index of the ship that was hit if it was a hit
int TakeShot(FireGrid& fireGrid, ShipGrid& shipGrid, int _x, int _y)
{
	int shipNum = fireGrid.FireTorpedoAtFireGrid(_y, _x, shipGrid);
	return shipNum;
}

//Logic for if someone gets a hit, val == true means it is the user, false = computer
bool LogicOnHit(ShipGrid& sg, int hitMarker, bool val)
{
	std::vector<Ship> temp = sg.GetShipVector();
	int hp = temp[hitMarker].GetShipHealth();
	temp[hitMarker].SetShipHealth(hp - 1);//Subtract 1 hp from the target
	sg.SetShipVector(temp);
	if (ShipDestroyed(sg, hitMarker, val))//ShipDestroyed checks if we destroyed a ship, then if the game is over
	{
		DisplayGameOverMessage(val);//Displays to the user the game is over
		return true;
	}
	else return false;
}

//This is the main game loop
bool DriverFunction(ShipGrid& ourShipGrid, FireGrid& ourFireGrid)
{
	//gameOver tracks if the game is still going
	//easyMode toggles whether or not to show the computer's shipgrid, or your firegrid
	bool gameOver, easyMode;
	gameOver = easyMode = false;
	std::vector<Point> computerShots;

	ShipGrid CompShipGrid;
	std::string ShipNames[5]{ "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" };
	
	//These two calls prepare the user's grids
	SetComputerShipGrid(CompShipGrid, ShipNames);
	ourFireGrid.SetupFireGrid(ourShipGrid.GetGrid());

	std::string userIn = "";
	//The game loops until gameOver becomes true
	while (!gameOver)
	{
		//Please see page 3 of the DisplayTutorial, this is for testing purposes
		easyMode ? CompShipGrid.DisplayGrid() : ourFireGrid.DisplayFireGrid();
		ourShipGrid.DisplayGrid();
		std::cout << "Please enter your selection (ex: A1, or B2, or q to quit):\n";
		std::cin >> userIn;
		if (userIn == "sv_cheats1")//see DisplayTutorial() page 3
		{
			easyMode = !easyMode;
			continue;
		}

		userIn = userIn.substr(0, 3);//We only need the first 3 characters of the guess
		if (userIn.front() == 'q' || userIn.front() == 'Q')
			gameOver = !gameOver;
		else
		{
			int guessX = -1;
			int guessY = -1;
			if (TestUserInput(userIn, guessX, guessY))//If there is an issue, continue to reset the round
				continue;

			std::cout << "\033[2J\033[1;1H";//clears the screen
			int hitMarker = TakeShot(ourFireGrid, CompShipGrid, guessX, guessY);
			if (hitMarker == -3)//-3 == duplicate shot
			{
				AlertUserOfException(hitMarker); //uncomment testing if gameover works
				continue;
			}
			else if (hitMarker != -1)//-1 is a miss, so if its not -1, we must have hit something
				gameOver = LogicOnHit(CompShipGrid, hitMarker, true);//LogicOnHit takes it away from here
		}
		//This marks the computer's turn
		Point computerShot = GenerateComputerShot(ourShipGrid, computerShots);//we generate a random shot
		int compHitMarker = ourShipGrid.ShipHit(computerShot);//We find out what that shot does
		if (compHitMarker != -1)//Not a miss?
		{
			gameOver = LogicOnHit(ourShipGrid, compHitMarker, false);//Logic on hit handles the logic
			if (gameOver)
			{
				CompShipGrid.DisplayGrid();
				std::string somethingUseful;
				std::cin >> somethingUseful;
			}
		}
	}
	CompShipGrid.DisplayGrid();
	std::cout << "Here is the computer's ship grid, enter anything to continue\n";
	std::string sometext;
	std::cin >> sometext;
	return gameOver;
}

//A quick function to get the size of a ship based on the name
int GetShipSize(std::string _type)
{
	if (_type == "Carrier")
		return 5;
	else if (_type == "Battleship")
		return 4;
	else if (_type == "Cruiser" || _type == "Submarine")
		return 3;
	else if (_type == "Destroyer")
		return 2;
	else
	{
		std::cout << "Error: Ship Type could not be extrapolated from the csv file.\n"
			<< "Please ensure that the ship types in the csv file are spelled correctly and are a valid type.";
		return -1;
	}
}

//Takes the x coordinate and converts it to an int
//-2 is returned on invalid character
int CharToInt(char c)
{
	switch (c)
	{
	case 'A':
	case 'a':
		return 0;
		break;
	case 'B':
	case 'b':
		return 1;
		break;
	case 'C':
	case 'c':
		return 2;
		break;
	case 'D':
	case 'd':
		return 3;
		break;
	case 'E':
	case 'e':
		return 4;
		break;
	case 'F':
	case 'f':
		return 5;
		break;
	case 'G':
	case 'g':
		return 6;
		break;
	case 'H':
	case 'h':
		return 7;
		break;
	case 'I':
	case 'i':
		return 8;
		break;
	case 'J':
	case 'j':
		return 9;
		break;
	default:
		return -2;
		break;
	}
}