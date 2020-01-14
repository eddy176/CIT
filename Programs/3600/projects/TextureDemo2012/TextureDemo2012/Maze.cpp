#include "Maze.h"
#include "graphics.h"
#include <iostream>


Cell::Cell() {
	leftW = topW = rightW = bottomW = true;
}

void Cell::Draw3d(int i, int j, int index) {
	if (leftW) {
		DrawQuad(i, j, i, j + 1, index);
	}
	if (bottomW) {
		DrawQuad(i + 1, j, i, j, index);
	}
	if (topW && j == HEIGHT - 1) {
		DrawQuad(i, j + 1, i + 1, j + 1, index);
	}
	if (rightW && i == WIDTH - 1) {
		DrawQuad(i + 1, j + 1, i + 1, j, index);
	}
}


Maze::Maze() {
}

bool Maze::isSafe(double x, double y, double r) {
	int i = (int)x;
	int j = (int)y;
	x = x - i;
	y = y - j;
	if (mCells[i][j].rightW && x + r > 1.0) { // these make sure the walls stop the mouse
		return false;
	}
	if (mCells[i][j].leftW && x - r < 0.0) {
		return false;
	}
	if (mCells[i][j].topW && y + r > 1.0) {
		return false;
	}
	if (mCells[i][j].bottomW && y - r < 0.0) {
		return false;
	}
	if (x + r > 1.0 && y - r < 0.0) {
		return false;
	}
	if (x + r > 1.0 && y + r > 1.0) {
		return false;
	}
	if (x - r < 0.0 && y - r < 0.0) {
		return false;
	}
	if (x - r < 0.0 && y + r > 1.0) {
		return false;
	}
	return true;
}


void Maze::Draw() {
	int index = 0;
	for (int i = 0; i < WIDTH; i++) {
		index++;
		for (int j = 0; j < HEIGHT; j++) {
			mCells[i][j].Draw3d(i, j, index);
		}
	}
}



void Maze::RemoveWalls() {
	int tR = rand() % WIDTH;
	int bR = rand() % WIDTH;
	mCells[tR][HEIGHT - 1].topW = false;
	mCells[bR][0].bottomW = false;
	ratStart = bR;
	RemoveWallsR(0, 0);
}

enum DIRECTIONS { NORTH, SOUTH, EAST, WEST };

void Maze::RemoveWallsR(int i, int j) {
	mCells[i][j].visited = true;
	while (true) {
		std::vector<DIRECTIONS> dirs;
		if (j + 1 < HEIGHT && !mCells[i][j + 1].visited) {
			dirs.push_back(NORTH);
		}
		if (j - 1 >= 0 && !mCells[i][j - 1].visited) {
			dirs.push_back(SOUTH);
		}
		if (i + 1 < WIDTH && !mCells[i + 1][j].visited) {
			dirs.push_back(EAST);
		}
		if (i - 1 >= 0 && !mCells[i - 1][j].visited) {
			dirs.push_back(WEST);
		}
		if (dirs.size() == 0) {
			//std::cout << "should run at beginning. " << std::endl;
			return;
		}
		int r = rand() % dirs.size();
		if (dirs[r] == NORTH) {
			mCells[i][j].topW = false;
			mCells[i][j + 1].bottomW = false;
			RemoveWallsR(i, j + 1);
		}
		if (dirs[r] == SOUTH) {
			mCells[i][j].bottomW = false;
			mCells[i][j - 1].topW = false;
			RemoveWallsR(i, j - 1);
		}
		if (dirs[r] == EAST) {
			mCells[i][j].rightW = false;
			mCells[i + 1][j].leftW = false;
			RemoveWallsR(i + 1, j);
		}
		if (dirs[r] == WEST) {
			mCells[i][j].leftW = false;
			mCells[i - 1][j].rightW = false;
			RemoveWallsR(i - 1, j);
		}
	}
}