#pragma once
#include <vector>

const int HEIGHT = 4;
const int WIDTH = 4;
const double MARGIN = 5;

struct Cell {
	Cell();
	void Draw(int i, int j);
	bool l, r, b, t;
	bool visited;
};


class Maze{

public:
	Maze();

	void Draw();

	void RemoveWalls();
	void RemoveWallsR(int i, int j);
	bool isSafe(double x, double y, double move);

private:
	Cell mCells[WIDTH][HEIGHT];
	double r;
	double ratStart;
};