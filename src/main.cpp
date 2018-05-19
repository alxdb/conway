#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include <ncurses.h>
#include <unistd.h>

#include "grid.hpp"

// std::vector<std::pair<int, int>> init = {{-1, 0}, {0, 0}, {1, 0}};
std::vector<std::pair<int, int>> init;

int main() {
	int rows, cols;
	int row = 0, col = 0;
	int delay = 50000;
	double clocks_per_us = (double)(CLOCKS_PER_SEC / 1000000);

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

	srand(std::clock());
	for (int i = rows / 4; i < (3 * rows) / 4; i++) {
		for (int j = cols / 4; j < (3 * cols) / 4; j++) {
			if (rand() > RAND_MAX / 2) {
				init.push_back({i, j});
			}
		}
	}

	Grid grid(rows, cols, init);

	std::clock_t start = std::clock();
	std::vector<std::vector<bool>> state = grid.getState();
	while (1) {

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
			state = grid.getState();
			double elapsed = (std::clock() - start) / clocks_per_us; 
			mvprintw(0, 0, "%f.0 ms update", elapsed);
			if (elapsed < delay) {
				usleep(delay - elapsed);
				mvprintw(1, 0, "%d fps", (1000000 / delay));
			}
			start = std::clock();
			refresh();
		}
		// usleep(10);
	}

	endwin();

	return 0;
}
