#pragma once
#include "Player.h"
#include "Utils.h"
#include <iostream>
#include <vector>

int playerNum = 0;
char playerSymbol = 'X';
Grid* grid;


void Player::SetCurrentGrid(Grid* currentGrid)
{
	grid = currentGrid;
}

void Player::ChangePlayerNum(int playerNumber)
{
	playerNum = playerNumber;

}

void Player::ChangePlayerSymbol(char symbol)
{
	playerSymbol = symbol;
}


void Player::ChangePlayerSymbol()
{

	std::cin >> playerSymbol;

}


//Returns choosen cell position for convience sake
Vector2Int Player::PlayerTurn()
{
	bool correctPos = false;
	Vector2Int choosenCellPos = { -1,-1 };

	while (correctPos == false)
	{
		std::cout << "Player " << playerNum << std::endl;


		std::cout << "Choose position X: " << std::endl;
		std::cin >> choosenCellPos.x;
		choosenCellPos.x - 1;
		std::cout << "Choose position Y: " << std::endl;
		std::cin >> choosenCellPos.y;
		choosenCellPos.y - 1;
		if (choosenCellPos.x >= 0 && choosenCellPos.y >= 0 && grid->CheckCellState(choosenCellPos, available) && std::cin)
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
	GridCellState curPlayer;
	if (playerNum == 1)
	{
		curPlayer = playerOne;
	}
	else
	{
		curPlayer = playerTwo;
	}

	grid->OccupySpace(choosenCellPos, curPlayer, available);

	Utils::ClearScreen();
	grid->ShowGrid();
	return choosenCellPos;
}

char Player::GetplayerSymbol()
{
	return playerSymbol;
}

int Player::GetplayerNum()
{
	return playerNum;
}


Vector2Int Player::ChoosePosition()
{

	bool choosenPosition = false;
	while (choosenPosition == false)
	{
		Vector2Int pos = {};

		std::cout << "Pos X: " << std::endl;
		std::cin >> pos.x;

		std::cout << "Pos Y: " << std::endl;
		std::cin >> pos.y;

		for (int i = 0; i < grid->GetCellNum(); i++)
		{
			if (grid->CheckCellState(pos, available))
			{
				choosenPosition = true;
				return pos;
			}
		}

		std::cout << "Wrong position" << std::endl;
	}
}

