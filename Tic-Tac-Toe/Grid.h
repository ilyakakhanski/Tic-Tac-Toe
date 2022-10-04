#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

struct Vector2Int
{
	int x;
	int y;


	bool operator==(const Vector2Int& a) const
	{
		if (a.x == x && a.y == y) return true;
		else return false;
	}

};


enum GridCellState { available, playerOne, playerTwo, blocked, unknown };

class GridCell
{
private:
	Vector2Int pos;
	GridCellState cellState;



public:

	void SetPos(Vector2Int _pos)
	{
		pos = _pos;
	}

	Vector2Int GetPos()
	{
		return pos;
	}

	void SetCellState(GridCellState _cellState)
	{
		cellState = _cellState;
	}

	GridCellState GetCellState()
	{
		return cellState;
	}

	bool operator==(const GridCell& a) const
	{
		if (a.pos.x == pos.x && a.pos.y == pos.y && a.cellState == cellState) return true;
		else return false;
	}

	bool IsPosEquals(Vector2Int pos, Vector2Int pos2)
	{
		return(pos.x == pos2.x && pos.y && pos2.y);
	};
};




class Grid
{
private:
	std::vector<GridCell> cells;
	Vector2Int size;
	char playerOneSymbol;
	char playerTwoSymbol;

public:
	void GenNewGrid(Vector2Int);
	void ShowGrid();
	void OccupySpace(Vector2Int, GridCellState);
	void OccupySpace(Vector2Int, GridCellState, GridCellState);
	void SetPlayerOneSymbol(char symbol);
	void SetPlayerTwoSymbol(char symbol);
	bool CheckCellState(Vector2Int, GridCellState);
	int  GetCellNum();
	std::vector<GridCell> GetAvailableCells();
	GridCell& FindCell(Vector2Int pos);
	int ReturnBiggestConnectionsNum(Vector2Int pos, GridCellState state);
	std::vector <GridCell> FindNeightbours(Vector2Int pos, Grid* grid);
	std::vector<GridCell> GetPlayer1Cells();
	std::vector<GridCell> GetPlayer2Cells();
	std::vector<GridCell> GetBlockedCells();

};
