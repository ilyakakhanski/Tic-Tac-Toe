#pragma once
#include "GameManager.h"
#include "Grid.h"
#include "Utils.h"
#include <iostream>
#include "Bot.h"


void GameManager::InitializeGame()
{
	turnNum = 0;

	//Grid Creation

	Vector2Int size = AskForSize();
	grid->GenNewGrid(size);




	//Symbol Ammout To win
	bool correctNumberOfSymbols = false;

	while (correctNumberOfSymbols == false)
	{
		int biggerSize = 0;
		if (size.x >= size.y) biggerSize = size.x;
		else biggerSize = size.y;
		int symbolAmmout = 2;
		std::cout << "Insert ammount of symbols in order to win (2-" << biggerSize << ")" << std::endl;

		std::cout << "Symbol ammount: " << std::endl;
		std::cin >> symbolAmmout;


		if (symbolAmmout >= 2 && symbolAmmout <= 100 && (symbolAmmout <= size.x || symbolAmmout <= size.y))
		{
			correctNumberOfSymbols = true;
			winConnectionCondition = symbolAmmout;
			break;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Wrong number! " << std::endl;
		}

	}

	// Player Stuff
	SetUpPlayers();

	std::cout << "Player 1 symbol: ";
	std::cout << player1->GetplayerSymbol() << std::endl;

	std::cout << "Player 2 symbol : ";
	std::cout << player2->GetplayerSymbol() << std::endl;


	//Modify Grid
	{
		bool modifiyngGrid = true;


		while (modifiyngGrid)
		{
			Utils::ClearScreen();

			grid->ShowGrid();

			std::cout << "Do you want to modify grid? " << std::endl;
			std::cout << " " << std::endl;

			int choiceNum;

			std::cout << "1. Yes with Player1 Cell " << std::endl;
			std::cout << "2. Yes with Player2 Cell " << std::endl;
			std::cout << "3. Yes with Empty Cell " << std::endl;
			std::cout << "4. Yes with Blocked Cell " << std::endl;
			std::cout << "5. No let's start the game! " << std::endl;
			std::cout << " " << std::endl;

			std::cout << "Insert number: " << std::endl;

			bool choosenNum = false;
			GridCellState cellState;

			while (choosenNum == false)
			{
				std::cin;
				std::cin >> choiceNum;

				if (choiceNum == 5) { choosenNum = true; modifiyngGrid = false; break; }
				else
				{
					switch (choiceNum)
					{
					case 1:
						cellState = playerOne;
						choosenNum = true;
						break;
					case 2:
						cellState = playerTwo;
						choosenNum = true;
						break;
					case 3:
						cellState = available;
						choosenNum = true;
						break;
					case 4:
						cellState = blocked;
						choosenNum = true;
						break;
					default:
						std::cout << "choice Error";
					}
					
				}

			}

			if (modifiyngGrid)
			{
				bool correctPos = false;
				Vector2Int choosenCellPos = { -1,-1 };

				while (correctPos == false)
				{
					std::cout << "Choose position X: " << std::endl;
					std::cin >> choosenCellPos.x;
					choosenCellPos.x - 1;
					std::cout << "Choose position Y: " << std::endl;
					std::cin >> choosenCellPos.y;
					choosenCellPos.y - 1;
					GridCell choosenCell = grid->FindCell(choosenCellPos);

					if (choosenCell.GetPos().x >= 0)
					{
						correctPos = true;
					}
					else
					{
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
						std::cout << "Invalid position! Try again " << std::endl;
					}
				}



				grid->OccupySpace(choosenCellPos, cellState);

				Utils::ClearScreen();
				grid->ShowGrid();
			}



		}

	}


	//Start Game
	ManageTurns();
}

//Size for grid
Vector2Int GameManager::AskForSize()
{

	Vector2Int newSize = { 3,3 };
	bool correctSize = false;

	while (correctSize == false)
	{
		std::cout << "Enter grid size (2 - 100)" << std::endl;

		std::cout << "Size X:" << std::endl;
		std::cin >> newSize.x;

		std::cout << "Size Y:" << std::endl;
		std::cin >> newSize.y;

		if (newSize.x > 1 && newSize.y > 1 && std::cin && newSize.x <= 100 && newSize.y <= 100)
		{
			correctSize = true;
			return newSize;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Inserted wrong size! " << std::endl;
		}

	}
	return newSize;
}


void GameManager::SetUpPlayers()
{

	//Player1 Setup
	{
		std::cout << "Player nr 1: " << std::endl;

		//Setting Type
		{
			bool selectedType = false;
			int typeNum = 0;
			while (selectedType == false)
			{
				Utils::ClearScreen();

				std::cout << "Select player type: " << std::endl;
				std::cout << "" << std::endl;
				std::cout << "1. Human " << std::endl;
				std::cout << "2. Random bot (always do random moves) " << std::endl;
				std::cout << "3. Losing bot (always tries to lose)" << std::endl;
				std::cout << "4. Agressive bot (always tries to win)" << std::endl;
				std::cout << "" << std::endl;

				std::cin >> typeNum;
				switch (typeNum)
				{
				case 1:
					player1 = new Player;
					selectedType = true;
					break;
				case 2:
					player1 = new RandomBot;
					selectedType = true;
					break;
				case 3:
					player1 = new LosingBot;
					selectedType = true;
					break;
				case 4:
					player1 = new AgressiveBot;
					selectedType = true;
					break;
				}

			}
		}


		//Setting Player Symbol
		bool choosenChar = false;
		while (choosenChar == false)
		{
			char playerSymbol = 'X';

			std::cout << "Insert player symbol: ";

			std::getchar();
			playerSymbol = std::getchar();


			player1->ChangePlayerSymbol(playerSymbol);
			grid->SetPlayerOneSymbol(playerSymbol);
			choosenChar = true;
		}
		player1->ChangePlayerNum(1);
		player1->SetCurrentGrid(grid);


	}

	//Player2 Setup
	{

		std::cout << "Player nr 2: " << std::endl;

		//Setting Type
		{
			bool selectedType = false;
			int typeNum = 0;
			while (selectedType == false)
			{
				Utils::ClearScreen();
				std::cout << "Select player type: " << std::endl;
				std::cout << "" << std::endl;
				std::cout << "1. Human " << std::endl;
				std::cout << "2. Random bot (always do random moves) " << std::endl;
				std::cout << "3. Losing bot (always tries to lose)" << std::endl;
				std::cout << "4. Agressive bot (always tries to win)" << std::endl;
				std::cout << "" << std::endl;

				std::cin >> typeNum;
				switch (typeNum)
				{
				case 1:
					player2 = new Player;
					selectedType = true;
					break;
				case 2:
					player2 = new RandomBot;
					selectedType = true;
					break;
				case 3:
					player2 = new LosingBot;
					selectedType = true;
					break;
				case 4:
					player2 = new AgressiveBot;
					selectedType = true;
					break;
				}

			}
		}


		//Setting Player Symbol
		bool choosenChar = false;
		while (choosenChar == false)
		{
			char playerSymbol = 'X';

			std::cout << "Insert player symbol: ";

			std::getchar();
			playerSymbol = std::getchar();


			player2->ChangePlayerSymbol(playerSymbol);
			grid->SetPlayerTwoSymbol(playerSymbol);
			choosenChar = true;
		}

		player2->ChangePlayerNum(2);
		player2->SetCurrentGrid(grid);
	}

}

//Gameplay
void GameManager::ManageTurns()
{
	bool gameRunning = true;

	while (gameRunning)
	{
		cellsAvailable = grid->GetAvailableCells();
		Vector2Int lastMovePos;

		Utils::ClearScreen();
		grid->ShowGrid();
		turnNum++;

		//Player1 Turn
		{
			lastMovePos = player1->PlayerTurn();

		}

		//CheckIfPlayer1Won
		{
			if (winConnectionCondition <= grid->ReturnBiggestConnectionsNum(lastMovePos, playerOne))
			{
				EndGame(playerOneWon);
				return;
			}
		}

		//End game if there is no space
		if (grid->GetAvailableCells().size() <= 0)
		{
			gameRunning = false;
			EndGame(draw);
			return;
		}

		//Player2 Turn
		{
			lastMovePos = player2->PlayerTurn();
		}

		//CheckIfPlayer2Won
		{
			if (winConnectionCondition <= grid->ReturnBiggestConnectionsNum(lastMovePos, playerTwo))
			{
				EndGame(playerTwoWon);
				return;

			}
		}


		//End game if there is no space
		if (grid->GetAvailableCells().size() <= 0)
		{
			gameRunning = false;
			EndGame(draw);
			return;
		}

	}


}


void GameManager::EndGame(EndGameState endGameState)
{
	//Utils::ClearScreen();

	switch (endGameState)
	{
	case draw:
		std::cout << "Nobody won!" << std::endl;
		break;
	case playerOneWon:
		std::cout << "Player 1 won!" << std::endl;
		break;
	case playerTwoWon:
		std::cout << "Player 2 won!" << std::endl;
		break;
	default:
		std::cout << "Unknown State!" << std::endl;
	}

	std::cout << "Game ended after: " << turnNum << " rounds" << std::endl;
	std::cout << "" << std::endl;

	std::cin;

	//After End
	{
		bool choosenOption = false;
		while (choosenOption == false)
		{
			char choice = 'X';

			std::cout << "Start again? " << std::endl;
			std::cout << "" << std::endl;
			std::cout << "Y - Yes"<<std::endl;
			std::cout << "N - No"<<std::endl;

			std::getchar();
			choice = std::getchar();

			if(choice == 'Y')
			{
				choosenOption = true;
				InitializeGame();
				break;
			}
			else if (choice == 'N')
			{
				choosenOption = true;
				break;
			}
			else 
			{
				std::cout << "Wrong choice! " << std::endl;
			}

			
		}

	}

}
