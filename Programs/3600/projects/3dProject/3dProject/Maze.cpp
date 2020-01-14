#include "Maze.h"
#include "graphics.h"

extern viewtype current_view;
extern bool SUPER;
extern enum DIRECTIONS;


Cell::Cell() {
	leftW = topW = rightW = bottomW = true;
}

void Cell::Draw(int i, int j) {
	if (leftW) {
		DrawLine(i, j, i, j + 1);
	}
	if (bottomW) {
		DrawLine(i + 1, j, i, j);
	}
	if (topW) {
		DrawLine(i, j + 1, i + 1, j + 1);
	}
	if (rightW) {
		DrawLine(i + 1, j + 1, i + 1, j);
	}
}

void Cell::Draw3d(int i, int j) {
	if (leftW) {
		DrawQuad(i, j, i, j + 1);
	}
	if (bottomW) {
		DrawQuad(i + 1, j, i, j);
	}
	if (topW && j == HEIGHT - 1) {
		DrawQuad(i, j + 1, i + 1, j + 1);
	}
	if (rightW && i == WIDTH - 1) {
		DrawQuad(i + 1, j + 1, i + 1, j);
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

	if (current_view == top_view)
	{
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				mCells[i][j].Draw(i, j);
			}
		}
	}
	else
	{
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				mCells[i][j].Draw3d(i, j);
			}
		}
	}
}

void Maze::WipeWall(double x, double y, int wall) {
	int i = (int)x;
	int j = (int)y;
	if (wall == WEST) {
		mCells[i][j].leftW = false;
		mCells[i - 1][j].rightW = false;
	}
	else if (wall == NORTH) {
		mCells[i][j].topW = false;
		mCells[i][j + 1].bottomW = false;
	}
	else if (wall == EAST) {
		mCells[i][j].rightW = false;
		mCells[i + 1][j].leftW = false;

	}
	else if (wall == SOUTH) {
		mCells[i][j].bottomW = false;
		mCells[i][j - 1].topW = false;

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