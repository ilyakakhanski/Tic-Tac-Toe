#pragma once
#include <iostream>
#include <vector>
#include "Grid.h"



class Player
{
protected:
	char playerSymbol;
	int playerNum;
	Grid* grid;


public:
	virtual Vector2Int PlayerTurn();
	void ChangePlayerSymbol(char);
	void ChangePlayerSymbol();
	void ChangePlayerNum(int);
	void SetCurrentGrid(Grid*);
	Vector2Int ChoosePosition();
	char GetplayerSymbol();
	int GetplayerNum();

	Player(int playerNumber, char symbol, Grid* gameGrid)
	{
		playerNum = playerNumber;
		playerSymbol = symbol;
		grid = gameGrid;
	}

	Player()
	{

	}

	virtual ~Player() {};

};