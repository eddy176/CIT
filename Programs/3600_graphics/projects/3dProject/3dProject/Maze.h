#pragma once
#include <vector>

const int HEIGHT = 4;
const int WIDTH = 4;
const double MARGIN = 5;


struct Cell {
	Cell();
	void Draw(int i, int j);
	bool leftW, rightW, bottomW, topW;
	bool visited;
	void Draw3d(int i, int j);
};


class Maze {

public:
	Maze();

	void Draw();

	void WipeWall(double x, double y, int wall);

	void RemoveWalls();
	void RemoveWallsR(int i, int j);
	bool isSafe(double x, double y, double move);

private:
	Cell mCells[WIDTH][HEIGHT];
	double r;
	double ratStart;
};