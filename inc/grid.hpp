#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <ctime>

class Grid {
private:
	std::vector<std::vector<bool>> grid;
	std::ofstream logStream;
public:
	Grid(int rows, int cols, std::vector<std::pair<int, int>> init) {
		for (int i = 0; i < rows; i++) {
			std::vector<bool> row;

			for (int j = 0; j < cols; j++) {
				std::pair<int, int> current {i, j};
				bool found = std::find(init.begin(), init.end(), current) != init.end();
				row.push_back(found);
			}

			grid.push_back(row);
		}
		logStream.open("log.txt");
	};

	void update() {
		std::time_t start = std::time(nullptr);
		std::vector<std::vector<bool>> buffer = grid;

		for (size_t i = 0; i < grid.size(); i++) {
			for (size_t j = 0; j < grid[0].size(); j++) {
				int neighbours = 0;

				for (int _i = -1; _i < 2; _i++) {
					for (int _j = -1; _j < 2; _j++) {
						try {
							neighbours += grid.at(i + _i).at(j + _j);
						} catch (const std::out_of_range& oor) { };
					}
				}

				// so as to not count self
				if (grid[i][j]) {
					neighbours -= 1;
				}

				if (grid[i][j] && (neighbours < 2 || neighbours > 3)) {
					buffer[i][j] = false;
					logStream << "cell : " << i << ", " << j << " killed" << std::endl;
				} else if (!grid[i][j] && neighbours == 3) {
					buffer[i][j] = true;
					logStream << "cell : " << i << ", " << j << " born" << std::endl;
				}
			}
		}

		grid = buffer;
		double elapsed = (std::time(nullptr) - start) / (double)(CLOCKS_PER_SEC / 1000);
		logStream << "Time: " << elapsed << " ms" << std::endl;
	}

	std::vector<std::vector<bool>> getState() {return grid;};

	~Grid() {
		logStream.close();
	}
};
