#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

const int row = 4;
const int col = 4;

int grid[row][col] = {
	{1,1,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{1,1,1,1}
};

void printGrid() {
	for(int i=0; i<row; ++i) {
		for(int j=0; j<col; ++j)
			std::cout << grid[i][j] << " ";
		std::cout << std::endl;
	}
}


struct Point {
	int x;
	int y;

	Point(int X, int Y)
		: x(X), y(Y) { }

	bool operator<(const Point& p) {
		return (x < p.x && y < p.y);
	}

	Point() 
		: x(-1), y(-1) { }

	friend std::ostream& operator << (std::ostream& os,const Point& p) {
		os << "(" << p.x << "," << p.y << ") ";
		return os;
	}

	bool operator==(const Point& p) {
		return (x == p.x && y == p.y);
	}
};

std::vector<Point> Path;

void printPath() {
	std::cout << "Path: ";
	for(int i=0; i<Path.size(); ++i)
		std::cout << Path[i];
	std::cout << std::endl;
}

void addPath(const Point& p) {
	Path.push_back(p);
}

void removePath(Point& p) {
	Path.erase(std::remove(Path.begin(), Path.end(), p), Path.end());
}

bool isOpen(int x, int y) {
	return (grid[x][y] == 1);
}

bool findPath(int sx, int sy, int tx, int ty) {

	Point p (sx, sy);
	addPath(p);

	if (sx == tx && sy == ty) {
		return true;
	}

	bool success = false;
	if (sx <= tx && isOpen(sx+1, sy)) {
		success = findPath(sx+1, sy, tx, ty);
	}

	if (!success && sy <= ty && isOpen(sx, sy+1)) {
		success = findPath(sx, sy+1, tx, ty);
	}

	if (!success) {
		removePath(p);
	}

	return success;
}

int main() {

	//printGrid();
	bool found = findPath(0,0, row-1, col-1);
	if (found)
		printPath();
	else
		std::cout << "No path found .. " << std::endl;


}