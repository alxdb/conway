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
	int delay = 100;

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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
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
			double elapsed = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000); 
			mvprintw(0, 0, "%f", elapsed);
			usleep(delay);
			start = std::clock();
			refresh();
		}
		// usleep(10);
	}

	endwin();

	return 0;
}
