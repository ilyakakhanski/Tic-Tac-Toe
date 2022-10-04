#include "Grid.h"
#include <iostream>
#include <vector>
#include <algorithm>



Vector2Int size;
std::vector<GridCell> cells;

//GenerateNewGrid
void Grid::GenNewGrid(Vector2Int size)
{
	cells.clear();

	if (size.x == 0 || size.y == 0)
	{
		std::cout << "Size can't equal to 0!" << std::endl;
		return;
	}

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			Vector2Int currentPos = { x,y };

			cells.push_back(GridCell());

			cells.back().SetPos(currentPos);
			cells.back().SetCellState(available);

		}
	}
	this->size = size;
}

void Grid::ShowGrid()
{
	std::string curLine = {};

	int gridCellIndex = 0;

	for (int y = 0; y < size.y; y++)
	{
		curLine = {};
		for (int x = 0; x < size.x; x++)
		{
			char cellChar = ' ';

			if (cells[gridCellIndex].GetCellState() == available)
			{
				cellChar = '.';
			}
			else if (cells[gridCellIndex].GetCellState() == playerOne)
			{
				cellChar = playerOneSymbol;

			}
			else if (cells[gridCellIndex].GetCellState() == playerTwo)
			{
				cellChar = playerTwoSymbol;
			}
			else if (cells[gridCellIndex].GetCellState() == blocked)
			{
				cellChar = '+';
			}
			else
			{
				std::cout << "Unknown State" << std::endl;
			}
			curLine.push_back(cellChar);
			gridCellIndex++;
		}
		std::cout << curLine << std::endl;
	}
	std::cout << std::endl;
}


//Changes cell state independent of current state
void Grid::OccupySpace(Vector2Int pos, GridCellState state)
{
	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetPos() == pos)
		{
			cells[i].SetCellState(state);
			return;
		}
	}


	std::cout << "Niema takiej pozycji" << std::endl;

}


//Changes cell state dependend on current state
void Grid::OccupySpace(Vector2Int pos, GridCellState state, GridCellState condition)
{
	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetPos() == pos && cells[i].GetCellState() == condition)
		{
			cells[i].SetCellState(state);

			return;
		}
		else if (cells[i].GetPos() == pos)
		{
			return;
		}

	}
	std::cout << "Niema takiej pozycji" << std::endl;
}

void Grid::SetPlayerOneSymbol(char symbol)
{
	playerOneSymbol = symbol;
}
void Grid::SetPlayerTwoSymbol(char symbol)
{
	playerTwoSymbol = symbol;

}

bool Grid::CheckCellState(Vector2Int pos, GridCellState state)
{

	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetPos() == pos)
		{
			if (cells[i].GetCellState() == state)
				return true;
			else
				return false;
		}
	}

	std::cout << "There is no such position" << std::endl;
	return false;
}

int Grid::GetCellNum()
{
	return cells.size();

}

GridCell& Grid::FindCell(Vector2Int pos)
{
	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetPos() == pos)
		{
			return cells[i];


		}
	}

	GridCell nullCell;
	Vector2Int invalidPos = { -1, -1 };
	nullCell.SetPos(invalidPos);

	return nullCell;
}

int Grid::ReturnBiggestConnectionsNum(Vector2Int pos, GridCellState state)
{

	int connectionsTotal = 1;
	Vector2Int newPos = pos;

	int connectionNumX = 1;
	int connectionNumY = 1;

	int connectionNumDiagnoalLeft = 1;  // "/"
	int connectionNumDiagnoalRight = 1; // "\"

	GridCell curCell = FindCell(pos);

	if (curCell.GetPos().x < 0)
	{
		return 0;
	}


	//Checking X
	{

		bool checking = true;

		//Checking left
		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x - 1, newPos.y };
			curCell = FindCell(newPos);
			if (curCell.GetPos().x < 0) break; //Checking if right position
			if (curCell.GetCellState() == state) connectionNumX++;
			else break;
		}

		//Checking Right side
		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x + 1, newPos.y };
			curCell = FindCell(newPos);

			if (curCell.GetPos().x < 0) break; //Checking if right position
			if (curCell.GetCellState() == state) connectionNumX++;
			else break;
		}
		if (connectionNumX >= connectionsTotal) { connectionsTotal = connectionNumX; }
	}

	//Checking Y
	{

		bool checking = true;

		//Checking down
		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x, newPos.y - 1 };
			curCell = FindCell(newPos);

			if (curCell.GetPos().x < 0) break; //Checking if right position 
			if (curCell.GetCellState() == state) connectionNumY++;
			else break;
		}

		//Checking up
		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x, newPos.y + 1 };
			curCell = FindCell(newPos);

			if (curCell.GetPos().x < 0) break; //Checking if right position
			if (curCell.GetCellState() == state) connectionNumY++;
			else break;
		}
		if (connectionNumY >= connectionsTotal) { connectionsTotal = connectionNumY; }

	}

	//Checking diagnal "/"
	{

		bool checking = true;

		//Checking left down
		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x - 1, newPos.y - 1 };
			curCell = FindCell(newPos);

			if (curCell.GetPos().x < 0) break; //Checking if right position
			if (curCell.GetCellState() == state) connectionNumDiagnoalLeft++;
			else break;
		}

		//Checking right up 
		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x + 1, newPos.y + 1 };
			curCell = FindCell(newPos);

			if (curCell.GetPos().x < 0) break; //Checking if right position
			if (curCell.GetCellState() == state) connectionNumDiagnoalLeft++;
			else break;
		}
		if (connectionNumDiagnoalLeft >= connectionsTotal) { connectionsTotal = connectionNumDiagnoalLeft; }
	}

	//Checking diagnal "\"
	{

		bool checking = true;

		//Checking left up
		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x - 1, newPos.y + 1 };
			curCell = FindCell(newPos);

			if (curCell.GetPos().x < 0) break; //Checking if right position
			if (curCell.GetCellState() == state) connectionNumDiagnoalRight++;
			else break;
		}

		//Checking right down

		newPos = pos;
		while (checking)
		{
			newPos = { newPos.x + 1, newPos.y - 1 };
			curCell = FindCell(newPos);

			if (curCell.GetPos().x < 0) break; //Checking if right position
			if (curCell.GetCellState() == state) connectionNumDiagnoalRight++;
			else break;
		}
		if (connectionNumDiagnoalRight >= connectionsTotal) { connectionsTotal = connectionNumDiagnoalRight; }
	}

	return connectionsTotal;
}

std::vector<GridCell> Grid::GetAvailableCells()
{
	std::vector<GridCell> availableCells = {};

	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetCellState() == available)
		{
			availableCells.push_back(cells[i]);
		}
	}

	return availableCells;
}

//Return vector of non-null cell neighbours
std::vector <GridCell> Grid::FindNeightbours(Vector2Int pos, Grid* grid)
{
	std::vector<GridCell> neightbours;
	GridCell mainCell = grid->FindCell(pos);
	if (mainCell.GetPos().x < 0)
	{
		return neightbours;
	}

	{
		Vector2Int newPos;

		newPos = { pos.x - 1, pos.y };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}

		newPos = { pos.x - 1, pos.y + 1 };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}

		newPos = { pos.x, pos.y + 1 };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}

		newPos = { pos.x + 1, pos.y + 1 };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}

		newPos = { pos.x + 1, pos.y };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}

		newPos = { pos.x + 1, pos.y - 1 };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}

		newPos = { pos.x , pos.y - 1 };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}

		newPos = { pos.x - 1, pos.y - 1 };
		mainCell = grid->FindCell(newPos);
		if (mainCell.GetPos().x >= 0)
		{
			neightbours.push_back(mainCell);
		}
	}

	return neightbours;
}

std::vector<GridCell> Grid::GetPlayer1Cells()
{
	std::vector<GridCell> playerOneCells = {};

	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetCellState() == playerOne)
		{
			playerOneCells.push_back(cells[i]);
		}
	}

	return playerOneCells;
}


std::vector<GridCell> Grid::GetPlayer2Cells()
{
	std::vector<GridCell> playerTwoCells = {};

	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetCellState() == playerTwo)
		{
			playerTwoCells.push_back(cells[i]);
		}
	}

	return playerTwoCells;
}

std::vector<GridCell> Grid::GetBlockedCells()
{
	std::vector<GridCell> blockedCells = {};

	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetCellState() == blocked)
		{
			blockedCells.push_back(cells[i]);
		}
	}

	return blockedCells;
}

