#include <iostream>
#include <vector>
#include <algorithm>

#include <ncurses.h>
#include <unistd.h>

#include "grid.hpp"

std::vector<std::pair<int, int>> init = {{-1, 0}, {0, 0}, {1, 0}};

int main() {
	int rows, cols;
	int row = 0, col = 0;

	initscr();
	noecho();
	cbreak();
	curs_set(0);

	getmaxyx(stdscr, rows, cols);
	{
		std::pair<int, int> middle = {rows / 2, cols / 2};
		for (std::pair<int, int>& p : init) {
			p.first += middle.first;
			p.second += middle.second;
		}
	}

	Grid grid(rows, cols, init);

	while (1) {
		std::vector<std::vector<bool>> state = grid.getState();

		if (state[row][col]) {
			attron(A_REVERSE);
			mvaddch(row, col, 32);
		} else {
			attroff(A_REVERSE);
			mvaddch(row, col, 32);
		}
		

		col = (col + 1) % cols;
		if (col == 0) {
			row = (row + 1) % rows;
		}
		if (row == rows - 1 && col == cols - 1) {
			grid.update();
			refresh();
		}
		// usleep(10);
	}

	endwin();

	return 0;
}
