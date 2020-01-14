#include "Maze.h"
#include "graphics.h"

Cell::Cell() {
	l = t = r = b = true;
}

void Cell::Draw(int i, int j) {
	if (l) {
		DrawLine(i, j, i, j + 1);
	}
	if (t) {
		DrawLine(i, j + 1, i + 1, j + 1);
	}
	if (r) {
		DrawLine(i + 1, j + 1, i + 1, j);
	}
	if (b) {
		DrawLine(i + 1, j, i, j);
	}
}


Maze::Maze() {
}

bool Maze::isSafe(double x, double y, double r) {
	int i = (int)x;
	int j = (int)y;
	x = x - i;
	y = y - j;
	if (mCells[i][j].r && x + r > 1.0) { // these make sure the walls stop the mouse
		return false;
	}
	if (mCells[i][j].l && x - r < 0.0) {
		return false;
	}
	if (mCells[i][j].t && y + r > 1.0) {
		return false;
	}
	if (mCells[i][j].b && y - r < 0.0) {
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
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			mCells[i][j].Draw(i, j);
		}
	}
}


void Maze::RemoveWalls() {
	int tR = rand() % WIDTH;
	int bR = rand() % WIDTH;
	mCells[tR][HEIGHT - 1].t = false;
	mCells[bR][0].b = false;
	ratStart  = bR;
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
			return;
		}
		int r = rand() % dirs.size();
		if (dirs[r] == NORTH) {
			mCells[i][j].t = false;
			mCells[i][j + 1].b = false;
			RemoveWallsR(i, j + 1);
		}
		if (dirs[r] == SOUTH) {
			mCells[i][j].b = false;
			mCells[i][j - 1].t = false;
			RemoveWallsR(i, j - 1);
		}
		if (dirs[r] == EAST) {
			mCells[i][j].r = false;
			mCells[i + 1][j].l = false;
			RemoveWallsR(i + 1, j);
		}
		if (dirs[r] == WEST) {
			mCells[i][j].l = false;
			mCells[i - 1][j].r = false;
			RemoveWallsR(i - 1, j);
		}
	}
}
