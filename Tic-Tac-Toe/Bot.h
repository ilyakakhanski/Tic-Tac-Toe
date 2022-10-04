#pragma once
#include "Player.h"
#include <iostream>
#include <stdlib.h> 
#include "Utils.h"

class Bot : public Player
{
private:

public:
	virtual Vector2Int PlayerTurn() = 0;

protected:
	std::vector<GridCell> availableCells;
	std::vector<GridCell> occupiedCells;

	virtual ~Bot() {};
};

//Always tries to put cells next to owned cells
class AgressiveBot : public Bot
{

private:
	std::vector<GridCell> neigbouringCells;

public:

	Vector2Int PlayerTurn()
	{

		availableCells = grid->GetAvailableCells();

		if (playerNum == 1) occupiedCells = grid->GetPlayer1Cells();
		else if (playerNum == 2) occupiedCells = grid->GetPlayer2Cells();

		GridCellState curPlayer;
		if (playerNum == 1)
		{
			curPlayer = playerOne;
		}
		else
		{
			curPlayer = playerTwo;
		}

		//Getting neigbours 
		for (int i = 0; i < occupiedCells.size(); i++)
		{
			std::vector<GridCell> _neigbouringCells = grid->FindNeightbours(occupiedCells[i].GetPos(), grid);

			for (int k = 0; k < _neigbouringCells.size(); k++)
			{
				if (_neigbouringCells[k].GetCellState() == available)
				{
					neigbouringCells.push_back(_neigbouringCells[k]);
				}
			}
		}

		//Occuping space on grid
		if (neigbouringCells.size() > 0)
		{
			int randomIndex = rand() % neigbouringCells.size();
			grid->OccupySpace(neigbouringCells[randomIndex].GetPos(), curPlayer, available);

			Utils::ClearScreen();
			grid->ShowGrid();
			return neigbouringCells[randomIndex].GetPos();
		}
		else
		{
			int randomIndex = rand() % availableCells.size();
			grid->OccupySpace(availableCells[randomIndex].GetPos(), curPlayer, available);

			Utils::ClearScreen();
			grid->ShowGrid();
			return availableCells[randomIndex].GetPos();

		}
	}


};


//Always tries to lose by trying not putting cells next to owned cells
class LosingBot : public Bot
{

private:

	std::vector<GridCell> neigbouringCells;

public:

	Vector2Int PlayerTurn()
	{

		availableCells = grid->GetAvailableCells();

		if (playerNum == 1) occupiedCells = grid->GetPlayer1Cells();
		else if (playerNum == 2) occupiedCells = grid->GetPlayer2Cells();

		GridCellState curPlayer;
		if (playerNum == 1)
		{
			curPlayer = playerOne;
		}
		else
		{
			curPlayer = playerTwo;
		}

		//Getting neighbours
		for (int i = 0; i < occupiedCells.size(); i++)
		{
			std::vector<GridCell> _neigbouringCells = grid->FindNeightbours(occupiedCells[i].GetPos(), grid);

			for (int k = 0; k < _neigbouringCells.size(); k++)
			{
				if (_neigbouringCells[k].GetCellState() == available)
				{
					neigbouringCells.push_back(_neigbouringCells[k]);
				}
			}
		}

		//Removing from available cell all cells that are neibours to owned cells 
		std::vector<GridCell> _availableCells = availableCells;
		for (int i = 0; i < neigbouringCells.size(); i++)
		{
			for (int k = 0; k < _availableCells.size(); k++)
			{
				if (neigbouringCells[i].GetCellState() == available && neigbouringCells[i].GetPos() == _availableCells[k].GetPos())
				{
					_availableCells.erase(_availableCells.begin() + k);
				}
			}
		}

		//Occuping space on grid
		if (_availableCells.size() > 0)
		{
			int randomIndex = rand() % _availableCells.size();
			grid->OccupySpace(_availableCells[randomIndex].GetPos(), curPlayer, available);

			Utils::ClearScreen();
			grid->ShowGrid();
			return _availableCells[randomIndex].GetPos();
		}
		else
		{
			int randomIndex = rand() % availableCells.size();
			grid->OccupySpace(availableCells[randomIndex].GetPos(), curPlayer, available);

			Utils::ClearScreen();
			grid->ShowGrid();
			return availableCells[randomIndex].GetPos();
		}


		Vector2Int pos = { 1,1 };
		return pos;
	}
};


//Always does random moves
class RandomBot : public Bot
{

public:

	Vector2Int PlayerTurn()
	{

		availableCells = grid->GetAvailableCells();

		int randomIndex = rand() % availableCells.size();

		GridCellState curPlayer;
		if (playerNum == 1)
		{
			curPlayer = playerOne;
		}
		else
		{
			curPlayer = playerTwo;
		}

		//Occuping space on grid
		grid->OccupySpace(availableCells[randomIndex].GetPos(), curPlayer, available);
		Utils::ClearScreen();
		grid->ShowGrid();
		return availableCells[randomIndex].GetPos();


	}


};