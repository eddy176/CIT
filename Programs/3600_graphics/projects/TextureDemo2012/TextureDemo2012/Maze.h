#pragma once
#include <vector>

const int HEIGHT = 4;
const int WIDTH = 4;
const double MARGIN = 5;


struct Cell {
	Cell();
	bool leftW, rightW, bottomW, topW;
	bool visited;
	void Draw3d(int i, int j, int index);
};


class Maze {

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