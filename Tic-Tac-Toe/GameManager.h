#pragma once
#include <iostream>
#include "Player.h"
#include "Grid.h"

enum EndGameState { playerOneWon, playerTwoWon, draw, Unknown };
enum PlayerTypes { player1, player2, randomBot, losingBot, agressiveBot, Unknown2 };

class GameManager
{


private:
	int turnNum = 0;
	Player* player1;
	Player* player2;
	Grid* grid = new Grid;
	int winConnectionCondition = 3;
	Vector2Int AskForSize();
	void SetUpPlayers();

	std::vector<GridCell> cellsAvailable;
	std::vector<GridCell> cellsPlayer1;
	std::vector<GridCell> cellsPlayer2;
	std::vector<GridCell> cellsblocked;



public:
	void InitializeGame();
	void ManageTurns();
	void EndGame(EndGameState endGameState);
};

